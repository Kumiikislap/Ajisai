#include "Commands.h"
#include "features/movie/Director.h"
#include "godot_cpp/variant/string_name.hpp"
#include "godot_cpp/variant/vector2.hpp"

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
void CommandActorVisibility::bind_director(Director* p_director, StringName p_actor)
{
	director = p_director;
	actor = p_actor;
}
bool CommandActorVisibility::execute()
{
	if ( director != nullptr )
	{
		director->show_actor(actor);
		return true;
	}
	return false;
}
void CommandActorVisibility::undo()
{
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
