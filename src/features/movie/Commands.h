#pragma once

#include "features/movie/Command.h"
#include "godot_cpp/classes/wrapped.hpp"
#include "godot_cpp/variant/string.hpp"
#include "godot_cpp/variant/string_name.hpp"
#include "godot_cpp/variant/vector2.hpp"


class SceneMenu;
class Director;

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
	virtual void bind_director(Director* p_director);
	virtual void bind_parameters(StringName p_actor, Visibity p_visibilty);
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
	virtual void bind_director(Director* p_director);
	virtual void bind_parameters(StringName p_actor, Vector2 pos);
	virtual bool execute() override;
	virtual void undo() override;

protected:
	static void _bind_methods(){};

	Director* director;
	StringName actor;
	Vector2 position;
};

// also the breakpoint
class CommandDialogueLine: public Command
{
	GDCLASS(CommandDialogueLine, Command)

public:
	CommandDialogueLine() = default;
	~CommandDialogueLine() = default;
	virtual void bind_director(SceneMenu* p_scene);
	virtual void bind_parameters(String p_id);
	virtual bool execute(bool is_input_from_balloon = false);
	virtual void undo() override;

	bool is_the_first_dialogue { false };

protected:
	static void _bind_methods(){};

	SceneMenu* scene_menu;
	String dialogue_id;
};

class CommandChangeActorPose: public Command
{
	GDCLASS(CommandChangeActorPose, Command)

public:
	CommandChangeActorPose() = default;
	~CommandChangeActorPose() = default;
	virtual void bind_director(Director* p_director);
	virtual void bind_parameters(StringName p_actor, StringName p_pose);
	virtual bool execute() override;
	virtual void undo() override;


protected:
	static void _bind_methods(){};

	Director* director;
	StringName before_pose; 
	
	StringName actor;
	StringName pose; 
};

class CommandChangeActorExpression: public Command
{
	GDCLASS(CommandChangeActorExpression, Command)

public:
	CommandChangeActorExpression() = default;
	~CommandChangeActorExpression() = default;
	virtual void bind_director(Director* p_director);
	virtual void bind_parameters(StringName p_actor, StringName p_expression);
	virtual bool execute() override;
	virtual void undo() override;

protected:
	static void _bind_methods(){};

	Director* director;
	StringName before_expression; 

	StringName actor;
	StringName expression; 
};

