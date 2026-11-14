#include "Commands.h"
#include "features/movie/Director.h"
#include "godot_cpp/core/error_macros.hpp"
#include "godot_cpp/variant/string_name.hpp"
#include "godot_cpp/variant/vector2.hpp"
#include "util/debug.hpp"

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

void CommandActorVisibility::bind_director(Director* p_director, StringName p_actor, Visibity p_visibility)
{
	director = p_director;
	actor = p_actor;
	visibility = p_visibility;
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

void CommandActorPosition::bind_director(Director* p_director, Vector2 pos)
{
}

bool CommandActorPosition::execute()
{
	return false;
}

void CommandActorPosition::undo()
{

}

void CommandDialogueLine::bind_director(SceneMenu* p_scene, String p_id)
{
	scene_menu = p_scene;
	dialogue_id = p_id;
}

bool CommandDialogueLine::execute()
{
	// stores the redo line id
	if (scene_menu == nullptr) {
		ERR_PRINT("SceneMenu nullptr!");
		return false;
	}
	scene_menu->next_dialogue(dialogue_id);
	return true;
}

void CommandDialogueLine::undo()
{
	execute();
}
