#pragma once

#include "features/movie/Actor.h"
#include "godot_cpp/classes/canvas_layer.hpp"
#include "godot_cpp/classes/control.hpp"
#include "godot_cpp/classes/wrapped.hpp"
#include "godot_cpp/core/memory.hpp"
#include "godot_cpp/variant/vector2.hpp"

using namespace godot;

class ActorsLayer : public CanvasLayer
{
	GDCLASS(ActorsLayer, CanvasLayer);

	public:
	ActorsLayer();
	~ActorsLayer() = default;

	Control* control_layer { memnew(Control) };

	enum POSITION_PRESET {
		LEFT = 0,
		MIDDLE = 1,
		RIGHT = 2,
	};
	const float y_preset { 540 };
	const Vector2 left_preset { 640 , y_preset };
	const Vector2 middle_preset { 960 , y_preset };
	const Vector2 right_preset { 1280 , y_preset };

	virtual void _ready() override;
	static void _bind_methods() {};

	void add_actor_to_layer(Actor* p_actor);
	void add_actor_control(Actor* p_actor);
	void set_actor_preset_position(Actor* p_actor, POSITION_PRESET p_preset);
	//void set_actor_position();
	
	private:

	Control* left_preset_control { memnew(Control)};
	Control* middle_preset_control { memnew(Control)};
	Control* right_preset_control { memnew(Control)};
};
