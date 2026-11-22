#include <cassert>
#include "Commands.h"
#include "godot_cpp/core/error_macros.hpp"
#include "godot_cpp/core/print_string.hpp"
#include "godot_cpp/variant/string_name.hpp"
#include "godot_cpp/variant/vector2.hpp"
#include "util/debug.hpp"
#include "features/movie/Director.h"
#include "features/movie/SceneMenu.h"

CommandTest::CommandTest()
{
}

bool CommandTest::execute()
{
	return false;
}
void CommandTest::_bind_methods()
{
}

void CommandTest::undo()
{
}

void CommandTest::bind_director(Director* p_director)
{
	director = p_director;
}

void CommandActorVisibility::bind_director(Director* p_director)
{
	director = p_director;
}

void CommandActorVisibility::bind_parameters(StringName p_actor, Visibity p_visibilty)
{
	actor = p_actor;
	visibility = p_visibilty;
}

bool CommandActorVisibility::execute()
{
	if (director == nullptr )
	{
		ERR_PRINT("Director nullptr!");
		return false;
	}
	switch (visibility) {
		case SHOW:
			director->show_actor(actor);
			break;
		case HIDE:
			director->hide_actor(actor);
			break;
	}
	return true;
}

void CommandActorVisibility::undo()
{
	switch (visibility) {
		case SHOW:
			director->hide_actor(actor);
			break;
		case HIDE:
			director->show_actor(actor);
			break;
	}
}

void CommandActorPosition::bind_director(Director* p_director)
{
	director = p_director;
}

void CommandActorPosition::bind_parameters(StringName p_actor, Vector2 pos)
{
	actor = p_actor;
	position = pos;
}
bool CommandActorPosition::execute()
{
	return false;
}

void CommandActorPosition::undo()
{
}

void CommandDialogueLine::bind_director(SceneMenu* p_scene)
{
	scene_menu = p_scene;
}

void CommandDialogueLine::bind_parameters(String p_id)
{
	dialogue_id = p_id;
}

bool CommandDialogueLine::execute(bool is_input_from_balloon)
{
	// stores the redo line id
	if (scene_menu == nullptr) {
		ERR_PRINT("SceneMenu nullptr!");
		return false;
	}
	scene_menu->next_dialogue(dialogue_id, is_input_from_balloon);
	return true;
}

void CommandDialogueLine::undo()
{
	execute();
}

void CommandChangeActorPose::bind_director(Director* p_director)
{
	director = p_director;
}

void CommandChangeActorPose::bind_parameters(StringName p_actor, StringName p_pose)
{
	actor = p_actor;
	pose = p_pose;
}
bool CommandChangeActorPose::execute()
{
	if (director == nullptr){
		ERR_PRINT("Command Director nullptr"); 
		return false;
	}
	before_pose = cast_to<Actor>(director->get_actors().get("p_actor", nullptr))->get_current_pose();
	director->change_pose(actor, pose);
	return true;
}

void CommandChangeActorPose::undo()
{
	director->change_pose(actor, before_pose);
}

void CommandChangeActorExpression::bind_director(Director* p_director)
{
	director = p_director;
}

void CommandChangeActorExpression::bind_parameters(StringName p_actor, StringName p_expression)
{
	actor = p_actor;
	expression = p_expression;
}
bool CommandChangeActorExpression::execute()
{
	if (director == nullptr){
		ERR_PRINT("Command Director nullptr"); 
		return false;
	}
	before_expression = cast_to<Actor>(director->get_actors().get(actor, nullptr))->get_current_expression();
	director->change_expression(actor, expression);
	return true;
}

void CommandChangeActorExpression::undo()
{
	WARN_PRINT(vformat("Actor: %s, before_expr: %s", actor, before_expression));
	director->change_expression(actor, before_expression);
}
