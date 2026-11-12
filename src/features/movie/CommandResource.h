#pragma once

#include <godot_cpp/classes/resource.hpp>
#include "features/movie/Command.h"
#include "godot_cpp/classes/global_constants.hpp"
#include "godot_cpp/classes/wrapped.hpp"
#include "godot_cpp/core/class_db.hpp"
#include <godot_cpp/variant/typed_array.hpp>

using namespace godot;

// Store the command stacks

class CommandResource  : public Resource
{
	GDCLASS(CommandResource, Resource)

protected:
	static void _bind_methods()
	{
		ClassDB::bind_method(D_METHOD("set_command_stack", "p_stack"), &CommandResource::set_command_stack);
		ClassDB::bind_method(D_METHOD("get_command_stack" ), &CommandResource::get_command_stack);
		ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "command_stack", godot::PROPERTY_HINT_ARRAY_TYPE, "Array"), "set_command_stack", "get_command_stack");
	}

	void set_command_stack(TypedArray<Command> p_stack)
	{
		command_stack = p_stack;
	}

	TypedArray<Command> get_command_stack() const
	{
		return command_stack;
	}

private:
	TypedArray<Command> command_stack;
};
