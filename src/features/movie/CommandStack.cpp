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
		ignore_next_dialogue_line = true;
	}
	else
	{
		ignore_next_dialogue_line = false;
	}
	pprint(command_stack);
}

// this code is running on my hopes and prayers
// 1 stop at dialogue command
void CommandStack::undo_commands()
{
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
		if ( i == -1){
			return;
		}
		current_command --;
		Command* cmd =  cast_to<Command>(command_stack[current_command]);
		if (cmd->is_class("CommandDialogueLine") and !ignore_next_dialogue_line)
		{
			cmd->undo();
			break;
		}
		else {
			ignore_next_dialogue_line = false;
			continue;
		}
		cmd->undo();
	}
	print_line(vformat("command_idx: %s ", cmd_idx));
	print_line(vformat("command_pos: %s ", current_command));
}

void CommandStack::redo_commands(bool is_input_from_balloon)
{
	if ( (current_command + 1) >= command_tip)
	{
		WARN_PRINT("cant redo, already at newest");
		return;
	}
	for(int i = current_command; current_command < command_tip; i++)
	{
		current_command ++;
		Command* cmd =  cast_to<Command>(command_stack[current_command]);
		if (cmd->is_class("CommandDialogueLine"))
		{
			CommandDialogueLine* cmd_dia = cast_to<CommandDialogueLine>(cmd);
			cmd_dia->execute(is_input_from_balloon);
			break;
		}
		cmd->execute();
		if ((current_command +1) >= command_tip)
			break;
	}
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

