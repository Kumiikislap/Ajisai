#include <cassert>
#include <cstddef>
#include "SceneMenu.h"
#include "features/movie/Director.h"
#include "features/movie/SceneStateAuto.h"
#include "features/movie/SceneStates.h"
#include "godot_cpp/classes/button.hpp"
#include "godot_cpp/classes/canvas_layer.hpp"
#include "godot_cpp/classes/global_constants.hpp"
#include "godot_cpp/classes/input.hpp"
#include "godot_cpp/classes/input_event.hpp"
#include "godot_cpp/classes/node.hpp"
#include "godot_cpp/classes/ref.hpp"
#include "godot_cpp/classes/resource.hpp"
#include "godot_cpp/classes/script.hpp"
#include "godot_cpp/core/class_db.hpp"
#include "godot_cpp/core/memory.hpp"
#include "godot_cpp/variant/array.hpp"
#include "godot_cpp/variant/callable.hpp"
#include "util/bind.hpp"
#include "util/conversions.hpp"
#include "util/input.hpp"
#include "util/scene.hpp"
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/timer.hpp>
#include <godot_cpp/variant/callable.hpp>
#include "SceneStateNormal.h"
#include <godot_cpp/classes/input_event_action.hpp>

SceneMenu::SceneMenu()
{
};

void SceneMenu::_bind_methods()
{
	rl::bind_property(SceneMenu, dialogue_resource, Ref<Resource>);
	ClassDB::bind_method(D_METHOD("set_dialogue_box", "p_box" ), &SceneMenu::set_dialogue_box);
	ClassDB::bind_method(D_METHOD("get_dialogue_box"), &SceneMenu::get_dialogue_box);
	ClassDB::bind_method(D_METHOD("set_scene_mode", "scene_mode"), &SceneMenu::set_scene_mode);
	ClassDB::bind_method(D_METHOD("set_scene_state", "p_state" ), &SceneMenu::set_scene_state);
	ClassDB::bind_method(D_METHOD("get_scene_state"), &SceneMenu::get_scene_state);
	BIND_ENUM_CONSTANT(NORMAL);
	BIND_ENUM_CONSTANT(AUTO);
	BIND_ENUM_CONSTANT(FAST_FORWARD);
	BIND_ENUM_CONSTANT(UNSKIPPABLE);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "dialogue_box", godot::PROPERTY_HINT_NODE_TYPE, "CanvasLayer"),
		"set_dialogue_box", "get_dialogue_box");
	rl::bind_property(SceneMenu, vertical_dialogue_box, CanvasLayer*);
	rl::bind_member_function(SceneMenu, init_from_gdscript);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "scene_state", godot::PROPERTY_HINT_NODE_TYPE, "SceneStates"),
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
	
	scene_state = Ref<SceneStateNormal>(memnew(SceneStateNormal));
	// for tests
	Button* button_state = get_node<Button>("Button");
    button_state->connect("pressed", callable_mp(this, &SceneMenu::simulate_keys_for_states).bind(AUTO));
}

void SceneMenu::_process(double delta)
{
}

void SceneMenu::_physics_process(double delta)
{
	scene_state->physics_update(*this, delta);
}

void SceneMenu::handle_state()
{
	Ref<SceneStates> state = scene_state->handleInput(*this, input);
	if (state != NULL)
	{
		//scene_state.unref();
		scene_state->exit(*this);
		scene_state = state;
		scene_state->enter(*this);
	}
	UtilityFunctions::print(scene_state);
}

void SceneMenu::simulate_keys_for_states(SCENE_MODE go_to_state)
{
	// simulate inputs
	switch (go_to_state) {
		case AUTO:
			input->action_press("auto_hotkey");
			handle_state();
			input->action_release("auto_hotkey");
			break;
		case FAST_FORWARD:
			break;
		case NORMAL:
			// cant check scene_state class (?) or cant read derived auto class
			if (scene_state->is_class("SceneStateAuto"))
			{
				input->action_press("auto_hotkey");
				handle_state();
				input->action_release("auto_hotkey");
			}
			input->action_press("auto_hotkey");
			handle_state();
			input->action_release("auto_hotkey");
			UtilityFunctions::print("call from balls");
			break;
		case UNSKIPPABLE:
			break;
	
	}
}

void SceneMenu::_input(const Ref<InputEvent> &p_event)
{
}

void SceneMenu::_unhandled_key_input(const Ref<InputEvent>& event)
{
	handle_state();
	if (input->is_action_just_pressed("test"))
	{
		UtilityFunctions::print("test-pressed" );
		start_dialogue();
	}
	//UtilityFunctions::print("event_test" );
}


// add parameters
void SceneMenu::start_dialogue()
{
	assert(director != nullptr and "director is null!");
	assert(dialogue_resource != nullptr and "dialogue_resource is null!");
	Array states;
	states.append(director);

	assert(dialogue_box->has_method("start"));
	dialogue_box->call("start", dialogue_resource, line, states);
}

void SceneMenu::auto_dialogue()
{
// crashes when no dialogue started
	assert(dialogue_box->has_method("auto_progress"));
	dialogue_box->call("auto_progress");
}

void SceneMenu::fast_forward_dialogue()
{
	assert(dialogue_box->has_method("fast_forward"));
	dialogue_box->call("fast_forward");
	UtilityFunctions::print("skipped");
}

void SceneMenu::set_scene_mode(SCENE_MODE p_mode)
{
	scene_mode = p_mode;
}

void SceneMenu::fast_forward_await()
{
	// TODO check if dialogue_script has ended
	assert(dialogue_box->has_method("fast_forward"));
	dialogue_box->call("fast_forward");
	UtilityFunctions::print("test-ff" );
	//scene_mode = FAST_FORWARD;
}

void SceneMenu::set_dialogue_box(CanvasLayer* p_box)
{
	dialogue_box = p_box;
}

void SceneMenu::set_vertical_dialogue_box(CanvasLayer* p_box)
{
	vertical_dialogue_box = p_box;
}

void SceneMenu::set_dialogue_resource(Ref<Resource> p_resource)
{
	dialogue_resource = p_resource;
}

Ref<Resource> SceneMenu::get_dialogue_resource() const
{
	return dialogue_resource;
}

CanvasLayer* SceneMenu::get_dialogue_box() const 
{
	return dialogue_box;
};

CanvasLayer* SceneMenu::get_vertical_dialogue_box() const 
{
	return vertical_dialogue_box;
};

void SceneMenu::set_scene_state(Ref<SceneStates> p_state)
{
	scene_state = p_state;
}
Ref<SceneStates> SceneMenu::get_scene_state() const
{
	return scene_state;
}
