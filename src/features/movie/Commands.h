#pragma once

#include "features/movie/Command.h"
#include "features/movie/Director.h"
#include "godot_cpp/classes/wrapped.hpp"
#include "godot_cpp/variant/string_name.hpp"

using namespace godot;

// TODO CommandBreakpoint
class CommandTest : public Command
{
	GDCLASS(CommandTest, Command)

public:
	CommandTest();
	~CommandTest() = default;
	virtual void bind_director(Director* p_director);
	virtual bool execute() override;
	virtual void undo() override;

protected:
	static void _bind_methods();

	Director* director;
};

class CommandActorVisibility : public Command
{
	GDCLASS(CommandActorVisibility, Command)

public:
	enum Visibity {
		VISIBLE,
		HIDDEN,
	};
	CommandActorVisibility() = default;
	~CommandActorVisibility() = default;
	virtual void bind_director(Director* p_director, StringName p_actor);
	virtual bool execute() override;
	virtual void undo() override;

protected:
	static void _bind_methods(){};

	Director* director;
	StringName actor;
};

class CommandActorPosition: public Command
{
	GDCLASS(CommandActorPosition, Command)

public:
	CommandActorPosition() = default;
	~CommandActorPosition() = default;
	virtual void bind_director(Director* p_director, Vector2 pos);
	virtual bool execute() override;
	virtual void undo() override;

protected:
	static void _bind_methods(){};

	Director* director;
};
