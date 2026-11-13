#pragma once

#include "godot_cpp/classes/resource.hpp"
#include "godot_cpp/classes/wrapped.hpp"
#include "godot_cpp/core/error_macros.hpp"
#include "util/debug.hpp"
#include <godot_cpp/classes/object.hpp>

using namespace godot;

class Command : public Resource
{
	GDCLASS(Command, Resource)

public:
	virtual bool execute() { WARN_PRINT("Command execute not implemented!"); return false; }
	virtual void undo() { WARN_PRINT("Command undo not implemented!"); };
	virtual void bind_director() {};
protected:
	static void _bind_methods() {}
};
