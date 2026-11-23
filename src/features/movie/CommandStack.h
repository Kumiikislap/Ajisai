#pragma once

#include "features/movie/Command.h"
#include "features/movie/CommandResource.h"
#include "godot_cpp/classes/object.hpp"
#include "godot_cpp/classes/ref.hpp"
#include "godot_cpp/classes/ref_counted.hpp"
#include "godot_cpp/classes/wrapped.hpp"
#include "godot_cpp/core/defs.hpp"
#include "godot_cpp/variant/string.hpp"
#include "godot_cpp/variant/string_name.hpp"
#include "godot_cpp/variant/typed_array.hpp"
#include "godot_cpp/variant/vector2.hpp"

/* Also the Director API
 */

using namespace godot;

class SceneMenu;
class Director;

class CommandStack : public Object
{
	GDCLASS(CommandStack, Object)

public:
	CommandStack();
	~CommandStack() = default;

	enum Mode {
		READ_AND_WRITE,
	};

	void bind_directors(SceneMenu* scene_menu, Director* director);
	void _ready();

	void api_test();
	void execute_command(Ref<Command> cmd);
	void undo_commands();
	void redo_commands(bool is_input_from_balloon = false);

	void record_dialogue_line(StringName p_id);
	void record_dialogue_end();
	void show_actor(StringName p_actor);
	void hide_actor(StringName p_actor);
	void change_actor_position(StringName p_actor, Vector2 pos);
	void change_pose(StringName p_actor, StringName p_pose);
	void change_expression(StringName p_actor, StringName p_expression, bool p_is_cut = false);

	void set_command_idx(int p_idx);
	int get_command_idx();

private:
protected:
	static void _bind_methods();

public:
private:
	enum TraverseHistory {
		ONE_STEP,
		TWO_STEP,
	};

	// TODO load saved command array
	Ref<CommandResource> command_resource_stack;
	TypedArray<Command> command_stack;

	int current_command { -1 };
	int command_tip { 0 };
	const int max_command { 0 };

	TraverseHistory undo { TWO_STEP };
	TraverseHistory redo { TWO_STEP };

	StringName current_dialogue_id;
	
	bool is_the_first_dialogue_end { true };

	StringName last_command_class { "" };

	bool dont_stop_at_next_dialogue_line { false };

	void pop_above_current_cmd();

	// Directors
	SceneMenu* scene_menu { nullptr };
	Director* director { nullptr };
};

