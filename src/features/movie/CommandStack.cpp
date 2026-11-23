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

void CommandStack::_ready()
{
}

void CommandStack::api_test()
{
	pprint("miao");
}

/* NOTE: DISGUSTING CODE AHEAD */
/* DO NOT PROCEED */

void CommandStack::execute_command(Ref<Command> p_cmd)
{
	if ( not p_cmd->execute() )
	{
		ERR_FAIL_MSG("bruh cmd");
	}
	// check if we are at the tip and append to array
	else if (current_command == (command_tip -1) ) {
		command_stack.append(p_cmd);
		current_command +=1;
		command_tip +=1;

		// add commands that go here are not dialogue commands anyway
		//print_line(vformat("is_current_dialogue_command: %s", is_current_dialogue_command_class));
		print_line(vformat("command_pos: %s ", current_command));
		print_line(vformat("tip class: %s ", command_stack[current_command]));
	}
	pprint(command_stack);
}

// TODO Document this monstrosity
// skip the animation when undo redoing

// this code is running on my hopes and prayers
// I should've made this a state machine :skull: -- its now cleaner yay

void CommandStack::undo_commands()
{
	if ( current_command <= 0 )
	{
		WARN_PRINT("cant undo, already at oldest"); return;
	}

	for ( int i = current_command; current_command > 0; i --)
	{
		if ( i == -1){
			return;
		}
		redo = TWO_STEP;
		Command* cmd =  cast_to<Command>(command_stack[current_command]);
		current_command --;
		cmd =  cast_to<Command>(command_stack[current_command]);
		if (cmd->is_class("CommandDialogueEnd"))
		{
			CommandDialogueEnd* cmd_dia_end = cast_to<CommandDialogueEnd>(cmd);
			if (cmd_dia_end->is_the_first_dialogue_end){
				WARN_PRINT("cant undo, already at oldest");
				break;
			}
		}
		if (cmd->is_class("CommandDialogueEnd"))
		{
			if (undo == TWO_STEP) {
				print_line(vformat("ignore at end: %s ", current_command));
				undo = ONE_STEP;
				continue;
			}
			if (undo == ONE_STEP) {
				print_line(vformat("Stopped at dia end: %s ", current_command));
				break;
			}
		}
		cmd->undo();
	}
	print_line(vformat("command_pos: %s ", current_command));
	print_line(vformat("tip class: %s ", command_stack[current_command]));
}

void CommandStack::redo_commands(bool is_input_from_balloon)
{
	if ( (current_command + 1) >= command_tip)
	{
		WARN_PRINT("cant redo, already at newest");
		return;
	}
	undo = TWO_STEP;
	for(int i = current_command; current_command < command_tip; i++)
	{
		if ((current_command +1) < command_tip){
			current_command ++;
		}
		Command* cmd =  cast_to<Command>(command_stack[current_command]);
		if (cmd->is_class("CommandDialogueEnd"))
		{
			if (redo == TWO_STEP) {
				print_line(vformat("ignore at end: %s ", current_command));
				redo = ONE_STEP;
				continue;
			}
			if (redo == ONE_STEP) {
				print_line(vformat("Stopped at dia end: %s ", current_command));
				break;
			}
		}
		if (cmd->is_class("CommandDialogueLine"))
		{
			CommandDialogueLine* cmd_dia = cast_to<CommandDialogueLine>(cmd);
			cmd_dia->execute(is_input_from_balloon);
			print_line("dia redoed");
			continue;
		}
		if ((current_command +1) >= command_tip)
			break;
		cmd->execute();
	}
	print_line(vformat("command_pos: %s ", current_command));
	print_line(vformat("tip class: %s ", command_stack[current_command]));
}

void CommandStack::record_dialogue_line(StringName p_id)
{
	if ( current_dialogue_id == p_id and ( current_command == (command_tip -1)))
	{
		return;
	}
	Ref<CommandDialogueLine> cmd = Ref<CommandDialogueLine>(memnew(CommandDialogueLine));
	cmd->bind_director(scene_menu);
	cmd->bind_parameters(p_id);
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

void CommandStack::record_dialogue_end()
{
	//if (current_command < command_tip)
	//	return;
	Ref<CommandDialogueEnd> cmd = Ref<CommandDialogueEnd>(memnew(CommandDialogueEnd));
	if (current_command == (command_tip -1) ) {
		command_stack.append(cmd);
		current_command +=1;
		command_tip +=1;

		if(is_the_first_dialogue_end){
			cmd->is_the_first_dialogue_end = true;
			is_the_first_dialogue_end = false;
		}

		// add commands that go here are not dialogue commands anyway
		//is_current_dialogue_command_class = false;
		//print_line(vformat("is_current_dialogue_command: %s", is_current_dialogue_command_class));
	}
	print_line(vformat("command_pos: %s ", current_command));
	print_line(vformat("tip class: %s ", command_stack[current_command]));
	pprint(command_stack);
}

void CommandStack::show_actor(StringName p_actor)
{
	Ref<CommandActorVisibility> cmd = Ref<CommandActorVisibility>(memnew(CommandActorVisibility));
	cmd->bind_director(director);
	cmd->bind_parameters(p_actor, CommandActorVisibility::SHOW);
	execute_command(cmd);
}
void CommandStack::hide_actor(StringName p_actor)
{
	Ref<CommandActorVisibility> cmd = Ref<CommandActorVisibility>(memnew(CommandActorVisibility));
	cmd->bind_director(director);
	cmd->bind_parameters(p_actor, CommandActorVisibility::HIDE);
	execute_command(cmd);
}

void CommandStack::change_actor_position(StringName p_actor, Vector2 pos)
{
}

void CommandStack::change_pose(StringName p_actor, StringName p_pose)
{
	Ref<CommandChangeActorPose> cmd = Ref<CommandChangeActorPose>(memnew(CommandChangeActorPose));
	cmd->bind_director(director);
	cmd->bind_parameters(p_actor, p_pose);
	execute_command(cmd);
}

void CommandStack::change_expression(StringName p_actor, StringName p_expression, bool p_is_cut)
{
	Ref<CommandChangeActorExpression> cmd = Ref<CommandChangeActorExpression>(memnew(CommandChangeActorExpression));
	cmd->bind_director(director);
	cmd->bind_parameters(p_actor, p_expression);
	execute_command(cmd);
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

