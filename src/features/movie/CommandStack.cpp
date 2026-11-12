#include "CommandStack.h"
#include "util/debug.hpp"
#include "util/bind.hpp"


CommandStack::CommandStack()
{
}

void CommandStack::_bind_methods()
{
	rl::bind_member_function(CommandStack, api_test);
}

void CommandStack::api_test()
{
	pprint("miao");
}
