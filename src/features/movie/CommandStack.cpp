#include "CommandStack.h"
#include "features/movie/Command.h"
#include "features/movie/Director.h"
#include "features/movie/SceneMenu.h"
#include "godot_cpp/classes/ref.hpp"
#include "godot_cpp/core/error_macros.hpp"
#include "godot_cpp/core/memory.hpp"
#include "godot_cpp/variant/string_name.hpp"
#include "godot_cpp/variant/vector2.hpp"
#include "util/debug.hpp"
#include "util/bind.hpp"
#include "Commands.h"


CommandStack::CommandStack()
{
}


void CommandStack::api_test()
{
	pprint("miao");
}

void CommandStack::execute_command(Ref<Command> cmd)
{
	if ( cmd->execute() )
	{
		command_resource_stack->get_command_stack().append(cmd);
		current_command +1;
		command_tip +1;
	}
	else {
		ERR_FAIL_MSG("bruh cmd");
	}
}
void CommandStack::undo_commands()
{
}

void CommandStack::redo_commands()
{
}

void CommandStack::show_actor(StringName p_actor)
{
	Ref<CommandActorVisibility> cmd = Ref<CommandActorVisibility>(memnew(CommandActorVisibility));
	cmd->bind_director(director, p_actor);
	execute_command(cmd);
}
void CommandStack::hide_actor(StringName p_actor)
{
}
void CommandStack::change_actor_position(StringName p_actor, Vector2 pos)
{
}
void CommandStack::change_pose(StringName p_actor, StringName p_pose)
{
}
void CommandStack::change_expression(StringName p_actor, StringName p_expression, bool p_is_cut, bool p_is_different_pose)
{
}

void CommandStack::_bind_methods()
{
	rl::bind_member_function(CommandStack, api_test);
}
