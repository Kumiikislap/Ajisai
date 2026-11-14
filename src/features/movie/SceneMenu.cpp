#include <cassert>
#include "SceneMenu.h"
#include "features/movie/CommandStack.h"
#include "features/movie/Director.h"
#include "features/movie/SceneStates.h"
#include "godot_cpp/classes/button.hpp"
#include "godot_cpp/classes/canvas_layer.hpp"
#include "godot_cpp/classes/global_constants.hpp"
#include "godot_cpp/classes/input.hpp"
#include "godot_cpp/classes/input_event.hpp"
#include "godot_cpp/classes/node.hpp"
#include "godot_cpp/classes/node2d.hpp"
#include "godot_cpp/classes/ref.hpp"
#include "godot_cpp/classes/resource.hpp"
#include "godot_cpp/classes/script.hpp"
#include "godot_cpp/core/class_db.hpp"
#include "godot_cpp/core/memory.hpp"
#include "godot_cpp/variant/array.hpp"
#include "godot_cpp/variant/callable.hpp"
#include "godot_cpp/variant/callable_method_pointer.hpp"
#include "godot_cpp/variant/string_name.hpp"
#include "godot_cpp/variant/variant.hpp"
#include "util/bind.hpp"
#include "util/conversions.hpp"
#include "util/input.hpp"
#include "util/scene.hpp"
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/timer.hpp>
#include <godot_cpp/variant/callable.hpp>
#include <godot_cpp/classes/input_event_action.hpp>
#include "util/debug.hpp"
#include "SceneStateEnum.h"
#include "CommandStack.h"

// when using memnew: always add child in constructor
SceneMenu::SceneMenu()
{
	states.set("Normal", memnew(SceneStateNormal));
	states.set("Auto", memnew(SceneStateAuto));
	states.set("FastForward", memnew(SceneStateFastForward));

	command_stack = memnew(CommandStack);
};

void SceneMenu::_bind_methods()
{
	rl::bind_property(SceneMenu, dialogue_resource, Ref<Resource>);
	rl::bind_member_function(SceneMenu, init_from_gdscript);
	ClassDB::bind_method(D_METHOD("set_dialogue_box", "p_box" ), &SceneMenu::set_dialogue_box);
	ClassDB::bind_method(D_METHOD("get_dialogue_box"), &SceneMenu::get_dialogue_box);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "dialogue_box", godot::PROPERTY_HINT_NODE_TYPE, "CanvasLayer"),
		"set_dialogue_box", "get_dialogue_box");
	ClassDB::bind_method(D_METHOD("set_vertical_dialogue_box", "p_box" ), &SceneMenu::set_vertical_dialogue_box);
	ClassDB::bind_method(D_METHOD("get_vertical_dialogue_box"), &SceneMenu::get_vertical_dialogue_box);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "vertical_dialogue_box", godot::PROPERTY_HINT_NODE_TYPE, "CanvasLayer"),
		"set_vertical_dialogue_box", "get_vertical_dialogue_box");

	ClassDB::bind_method(D_METHOD("set_scene_mode", "scene_mode"), &SceneMenu::set_scene_mode);
	ClassDB::bind_method(D_METHOD("set_scene_state", "p_state" ), &SceneMenu::set_scene_state);
	ClassDB::bind_method(D_METHOD("get_scene_state"), &SceneMenu::get_scene_state);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "current_state", godot::PROPERTY_HINT_NODE_TYPE, "SceneStates"),
		"set_scene_state", "get_scene_state");
	ClassDB::bind_method(D_METHOD("simulate_keys_for_states", "go_to_state" ), &SceneMenu::simulate_keys_for_states);
}

void SceneMenu::_ready()
{
	//start_dialogue();
}

void SceneMenu::init_from_gdscript()
{
	Node* director_node = this->find_child("Director");
	director = rl::gdcast<Director>(director_node);

	register_apis.append(command_stack);
	register_api();
	
	auto s = states.get("Normal", nullptr);
	current_state = cast_to<SceneStates>(s);
	current_dialogue_box = horizontal_dialogue_box;
	assert(current_dialogue_box->has_signal("emit_dialogue_id"));
	current_dialogue_box->connect("emit_dialogue_id", callable_mp(this, &SceneMenu::recieve_dialogue_id));

	command_stack->bind_directors(this, director);

	//// for tests
	//Button* button_state = get_node<Button>("Button");
    ////button_state->connect("pressed", callable_mp(this, &SceneMenu::simulate_keys_for_states).bind(SceneStateEnum::AUTO));
	//pprint("macro yay");

	//// memory leak nyehehehe
	//cmdstack->api_test();
	//pprint(cmdstack);
	pprint(current_state);
}

void SceneMenu::_process(double delta)
{
}

void SceneMenu::_physics_process(double delta)
{
	// only fast_forward uses physics process as of now
	if (current_state->is_class("SceneStateFastForward"))
	{
		current_state->physics_update(*this, delta);
	}
}

void SceneMenu::handle_state()
{
//	// TODO state returns the next state name then process that here
	SceneStateEnum::STATE state  = current_state->handleInput(*this, input);
	if (state == SceneStateEnum::IGNORE )
	{
		return;
	}
	current_state->exit(*this);
	switch (state)
	{
		case SceneStateEnum::NORMAL:
			current_state =  cast_to<SceneStates>(states.get("Normal", nullptr));
			break;
		case SceneStateEnum::AUTO:
			current_state = cast_to<SceneStates>(states.get("Auto", nullptr)) ;;
			break;
		case SceneStateEnum::FAST_FORWARD:
			current_state = cast_to<SceneStates>(states.get("FastForward", nullptr)) ;;
			break;
		case SceneStateEnum::IGNORE:
			break;
		case SceneStateEnum::UNSKIPPABLE:
			break;
	}
	current_state->enter(*this);
	pprint(current_state);
}

void SceneMenu::simulate_keys_for_states(SceneStateEnum::STATE go_to_state)
{
	// simulate inputs
	switch (go_to_state) {
		case SceneStateEnum::AUTO:
			input->action_press("auto_hotkey");
			handle_state();
			input->action_release("auto_hotkey");
			break;
		case SceneStateEnum::FAST_FORWARD:
			break;
		case SceneStateEnum::NORMAL:
			// cant check scene_state class (?) or cant read derived auto class
			// already checked if in auto in gdscript lol
			//if (current_state->is_class("SceneStateAuto"))
			//{
			//	input->action_press("auto_hotkey");
			//	//handle_state();
			//	input->action_release("auto_hotkey");
			//	pprint("henlo");
			//}
			input->action_press("auto_hotkey");
			input->action_release("auto_hotkey");
			UtilityFunctions::print("call from balls");
			break;
	}
}

void SceneMenu::_input(const Ref<InputEvent> &p_event)
{
}

void SceneMenu::_unhandled_input(const Ref<InputEvent>& p_event)
{
	handle_state();
	if ( input->is_mouse_button_pressed(godot::MOUSE_BUTTON_WHEEL_UP))
	{
		command_stack->undo_commands();
	}
	if ( input->is_mouse_button_pressed(godot::MOUSE_BUTTON_WHEEL_DOWN))
	{
		command_stack->redo_commands();
	}
}

void SceneMenu::_unhandled_key_input(const Ref<InputEvent>& event)
{
	if (input->is_action_just_pressed("test"))
	{
		UtilityFunctions::print("test-pressed" );
		start_dialogue();
	}
}

void SceneMenu::_exit_tree()
{
	pprint("scene exit");
}

// add parameters
void SceneMenu::start_dialogue()
{
	assert(director != nullptr and "director is null!");
	assert(dialogue_resource != nullptr and "dialogue_resource is null!");

	assert(current_dialogue_box->has_method("start"));
	current_dialogue_box->call("start", dialogue_resource, line, register_apis);
}

void SceneMenu::next_dialogue(String p_id)
{
	assert(current_dialogue_box->has_method("next"));
	current_dialogue_box->call("next", p_id);
}

void SceneMenu::register_api()
{
	assert(horizontal_dialogue_box->has_method("register_api"));
	assert(vertical_dialogue_box->has_method("register_api"));
	horizontal_dialogue_box->call("register_api", register_apis);
	vertical_dialogue_box->call("register_api", register_apis);
}

void SceneMenu::auto_dialogue()
{
// crashes when no dialogue started
	assert(current_dialogue_box->has_method("auto_progress"));
	current_dialogue_box->call("auto_progress");
}

void SceneMenu::fast_forward_dialogue()
{
	assert(current_dialogue_box->has_method("fast_forward"));
	current_dialogue_box->call("fast_forward");
	UtilityFunctions::print("skipped");
}

void SceneMenu::set_scene_mode(SceneStateEnum::STATE p_mode)
{
	//scene_mode = p_mode;
}

void SceneMenu::recieve_dialogue_id(StringName p_id)
{
	command_stack->record_dialogue_line(p_id);
	pprint(p_id);
}

void SceneMenu::fast_forward_await()
{
	// TODO check if dialogue_script has ended
	assert(current_dialogue_box->has_method("fast_forward"));
	current_dialogue_box->call("fast_forward");
	UtilityFunctions::print("test-ff" );
	//scene_mode = FAST_FORWARD;
}

void SceneMenu::set_dialogue_box(CanvasLayer* const p_box)
{
	horizontal_dialogue_box = p_box;
}

void SceneMenu::set_vertical_dialogue_box(CanvasLayer* const p_box)
{
	vertical_dialogue_box = p_box;
}

void SceneMenu::set_dialogue_resource(const Ref<Resource> p_resource)
{
	dialogue_resource = p_resource;
}

Ref<Resource> SceneMenu::get_dialogue_resource() const
{
	return dialogue_resource;
}

CanvasLayer* SceneMenu::get_dialogue_box() const 
{
	return horizontal_dialogue_box;
};

CanvasLayer* SceneMenu::get_vertical_dialogue_box() const 
{
	return vertical_dialogue_box;
};

void SceneMenu::set_scene_state(SceneStates* const p_state)
{
	current_state = p_state;
}
SceneStates* SceneMenu::get_scene_state() const
{
	return current_state;
}

SceneMenu::~SceneMenu()
{
	Array states_ = states.values();
	for ( auto state : states_ )
	{
		SceneStates* stat = cast_to<SceneStates>(state);
		memdelete(stat);
	}
	states.clear();
	memdelete(command_stack);
}

void SceneMenu::show_dialogue_box(DialogueBox p_box)
{
}

void SceneMenu::hide_dialogue_box(DialogueBox p_box)
{
}
