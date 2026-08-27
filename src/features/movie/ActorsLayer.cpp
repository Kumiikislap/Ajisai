#include "ActorsLayer.h"
#include "features/movie/Actor.h"
#include "godot_cpp/classes/control.hpp"
#include "godot_cpp/core/memory.hpp"
#include "godot_cpp/variant/utility_functions.hpp"
#include "util/scene.hpp"

ActorsLayer::ActorsLayer()
{
	add_child(left_preset_control);
	add_child(middle_preset_control);
	add_child(right_preset_control);

	add_child(control_layer);
	rl::scene::node::set_unique_name(control_layer, "ControlLayer");
	//control_layer->set_anchors_preset(Control::LayoutPreset::PRESET_CENTER);

	left_preset_control->set_position(left_preset);
	middle_preset_control->set_anchors_and_offsets_preset(Control::LayoutPreset::PRESET_CENTER);
	right_preset_control->set_position(right_preset);
}

void ActorsLayer::_ready()
{
}

void ActorsLayer::add_actor_to_layer(Actor* p_actor)
{
	control_layer->add_child(p_actor);
}

void ActorsLayer::add_actor_control(Actor* p_actor)
{
	Control* control_node = memnew(Control);
	control_node->add_child(p_actor);
}

void ActorsLayer::set_actor_preset_position(Actor* p_actor, POSITION_PRESET p_preset)
{ 
	Vector2 preset { 0.0 , 0.0 };
	switch (p_preset) {
		case LEFT:
			preset = left_preset;
			break;

		case MIDDLE:
			preset = middle_preset;
			break;

		case RIGHT:
			preset = right_preset;
			break;

		default:
			UtilityFunctions::printerr("Unknown preset argument!");
			break;
	}
	p_actor->set_position(preset);
}

