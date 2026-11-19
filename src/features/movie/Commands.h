#pragma once

#include "features/movie/Command.h"
#include "features/movie/Director.h"
#include "features/movie/SceneMenu.h"
#include "godot_cpp/classes/wrapped.hpp"
#include "godot_cpp/variant/string_name.hpp"

using namespace godot;

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
		SHOW,
		HIDE,
	} visibility;
	CommandActorVisibility() = default;
	~CommandActorVisibility() = default;
	virtual void bind_director(Director* p_director, StringName p_actor, Visibity p_visibilty);
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

// also the breakpoint
class CommandDialogueLine: public Command
{
	GDCLASS(CommandDialogueLine, Command)

public:
	CommandDialogueLine() = default;
	~CommandDialogueLine() = default;
	void bind_director(SceneMenu* p_scene, String p_id);
	virtual bool execute(bool is_input_from_balloon = false);
	virtual void undo() override;

	bool is_the_first_dialogue { false };

protected:
	static void _bind_methods(){};

	SceneMenu* scene_menu;
	String dialogue_id;
};
