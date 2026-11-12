#pragma once

#include "godot_cpp/classes/resource.hpp"
#include "godot_cpp/classes/wrapped.hpp"
#include <godot_cpp/classes/object.hpp>

using namespace godot;

class Command : public Resource
{
	GDCLASS(Command, Resource)

public:
	virtual bool execute() { return false; }
	virtual void undo() {};
	virtual void bind_director() {};
protected:
	static void _bind_methods() {}
};
