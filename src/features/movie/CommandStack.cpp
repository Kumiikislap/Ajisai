#include "CommandStack.h"
#include "features/movie/Command.h"
#include "features/movie/CommandResource.h"
#include "features/movie/SceneMenu.h"
#include "godot_cpp/classes/ref.hpp"
#include "godot_cpp/core/class_db.hpp"
#include "godot_cpp/core/error_macros.hpp"
#include "godot_cpp/core/memory.hpp"
#include "godot_cpp/core/print_string.hpp"
#include "godot_cpp/variant/string_name.hpp"
#include "godot_cpp/variant/variant.hpp"
#include "godot_cpp/variant/vector2.hpp"
#include "util/debug.hpp"
#include "util/bind.hpp"
#include "Commands.h"


CommandStack::CommandStack()
{
	command_resource_stack = Ref<CommandResource>(memnew(CommandResource));
	command_stack = command_resource_stack->get_command_stack();
}

void CommandStack::bind_directors(SceneMenu* p_scene_menu, Director* p_director)
{
	scene_menu = p_scene_menu;
	director = p_director;
}

void CommandStack::api_test()
{
	pprint("miao");
}

void CommandStack::execute_command(Ref<Command> cmd)
{
	if ( not cmd->execute() )
	{
		ERR_FAIL_MSG("bruh cmd");
	}
	// check if we are at the tip and append to array
	else if (current_command == (command_tip -1) ) {
		command_stack.append(cmd);
		current_command +=1;
		command_tip +=1;
	}
	if (not cmd->is_class("CommandDialogueLine") and (current_command == (command_tip -1)))
	{
		print_line("at tip exe");
		//ignore_next_dialogue_line = true;
	}
	else
	{
		//ignore_next_dialogue_line = false;
	}
	pprint(command_stack);
}

// this code is running on my hopes and prayers
// 1 stop at dialogue command
void CommandStack::undo_commands()
{
	bool is_last_command_dialogue = false;
	bool local_last_dialogue = true;
	bool local_dialogue = is_current_dialogue_command_class;
	print_line(local_last_dialogue);
	print_line(vformat("command_idx: %s ", cmd_idx));
	if ( current_command <= 0 )
	{
		WARN_PRINT("cant undo, already at oldest");
		return;
	}

	for ( int i = current_command; current_command > 0; i --)
	{
		print_line(vformat("current cmd tip %s",command_tip));
		print_line(vformat("command_pos: %s ", current_command));
		print_line(vformat("is_dia: %s ", is_current_dialogue_command_class));
		if ( i == -1){
			return;
		}
		if (local_dialogue)
		{
			current_command --;
			local_last_dialogue = false;
			local_dialogue = false;
			print_line("ok current is dia , but now changed");
			continue;
		}
		else if (not is_current_dialogue_command_class and local_last_dialogue ){
			ignore_next_dialogue_line = true;
			print_line("ur not suppose");
		}
		Command* cmd =  cast_to<Command>(command_stack[current_command]);
		if (cmd->is_class("CommandDialogueLine") and !ignore_next_dialogue_line )
		{
			cmd->undo();
			is_last_command_dialogue = true;
			print_line("ur suppose");
			break;
		}
		print_line(vformat("ignore: %s ", ignore_next_dialogue_line));
		if (cmd->is_class("CommandDialogueLine") and ignore_next_dialogue_line )
		{
			ignore_next_dialogue_line = false;
			current_command --;
			local_last_dialogue = false;
			print_line("did you even flip suppose");
			continue;
		}
		cmd->undo();
		current_command --;
		is_last_command_dialogue = false;
		print_line("undo cmds");
	}
	is_current_dialogue_command_class = is_last_command_dialogue;
	print_line(vformat("is dia current class: %s", is_current_dialogue_command_class));
	print_line(vformat("command_idx: %s ", cmd_idx));
	print_line(vformat("command_pos: %s ", current_command));
}

void CommandStack::redo_commands(bool is_input_from_balloon)
{
	bool is_last_command_dialogue = false;
	bool trigger_ignore = true;
	if ( (current_command + 1) >= command_tip)
	{
		WARN_PRINT("cant redo, already at newest");
		return;
	}
	for(int i = current_command; current_command < command_tip; i++)
	{
		if (not is_current_dialogue_command_class and trigger_ignore)
		{
			// skip next dia
			ignore_next_dialogue_line = true;
			print_line("ignored next dia" );
		}
		current_command ++;
		Command* cmd =  cast_to<Command>(command_stack[current_command]);
		if (cmd->is_class("CommandDialogueLine") and !ignore_next_dialogue_line)
		{
			CommandDialogueLine* cmd_dia = cast_to<CommandDialogueLine>(cmd);
			cmd_dia->execute(is_input_from_balloon);
			is_last_command_dialogue = true;
			print_line("dia redoed");
			break;
		}
		if (cmd->is_class("CommandDialogueLine") and ignore_next_dialogue_line )
		{
			ignore_next_dialogue_line = false;
			trigger_ignore = false;
			print_line("did you even flip suppose redo " );
			continue;
		}
		if (!cmd->is_class("CommandDialogueLine") and (current_command +1))
		{
		}
		if ((current_command +1) >= command_tip)
			break;
		cmd->execute();
		is_last_command_dialogue = false;
	}
	is_current_dialogue_command_class = is_last_command_dialogue;
	print_line(vformat("is dia current class: %s", is_current_dialogue_command_class));
}

void CommandStack::record_dialogue_line(StringName p_id)
{
	if ( current_dialogue_id == p_id and ( current_command == (command_tip -1)))
	{
		return;
	}
	Ref<CommandDialogueLine> cmd = Ref<CommandDialogueLine>(memnew(CommandDialogueLine));
	cmd->bind_director(scene_menu, p_id);
	if (current_command == (command_tip -1 ) ) {
		command_stack.append(cmd);
		current_command +=1;
		command_tip +=1;
		current_dialogue_id = p_id;
		pprint(command_stack);
		print_line(vformat("current cmd %s",current_command));
		print_line(vformat("current cmd tip %s",command_tip));
		return;
	}
	// update current_command when clicking to balloon
	if (current_command < command_stack.size())
	{
		redo_commands(true);
	}
	pprint(command_stack);
}

void CommandStack::show_actor(StringName p_actor)
{
	Ref<CommandActorVisibility> cmd = Ref<CommandActorVisibility>(memnew(CommandActorVisibility));
	cmd->bind_director(director, p_actor, CommandActorVisibility::SHOW);
	execute_command(cmd);
}
void CommandStack::hide_actor(StringName p_actor)
{
	Ref<CommandActorVisibility> cmd = Ref<CommandActorVisibility>(memnew(CommandActorVisibility));
	cmd->bind_director(director, p_actor, CommandActorVisibility::HIDE);
	execute_command(cmd);
}

void CommandStack::change_actor_position(StringName p_actor, Vector2 pos)
{
}

void CommandStack::change_pose(StringName p_actor, StringName p_pose)
{
}

void CommandStack::change_expression(StringName p_actor, StringName p_expression, bool p_is_cut)
{
}

void CommandStack::set_command_idx(int p_idx)
{
	current_command = p_idx;
}
int CommandStack::get_command_idx()
{
	return current_command;
}
void CommandStack::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("show_actor", "actor"), &CommandStack::show_actor);
	ClassDB::bind_method(D_METHOD("hide_actor", "actor"), &CommandStack::hide_actor);
	ClassDB::bind_method(D_METHOD("change_actor_position", "actor", "position"), &CommandStack::change_actor_position);
	ClassDB::bind_method(D_METHOD("change_expression", "name", "expression", "is_cut"), &CommandStack::change_expression, DEFVAL(""), DEFVAL(""), DEFVAL(false));

	rl::bind_member_function(CommandStack, api_test);
}

