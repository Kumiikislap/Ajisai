#include "Commands.h"
#include "features/movie/Director.h"

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
