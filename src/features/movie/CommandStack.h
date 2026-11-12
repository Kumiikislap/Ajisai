#pragma once

#include "features/movie/CommandResource.h"
#include "godot_cpp/classes/object.hpp"
#include "godot_cpp/classes/ref.hpp"
#include "godot_cpp/classes/wrapped.hpp"

/* Also the Director API
 */

using namespace godot;

class CommandStack : public Object
{
	GDCLASS(CommandStack, Object)

public:
	CommandStack();
	~CommandStack() = default;

	void api_test();

protected:
	static void _bind_methods();

private:
	Ref<CommandResource> m_command_resource_stack;

	// Directors
};

