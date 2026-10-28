#pragma once

#include <godot_cpp/classes/canvas_layer.hpp>
#include <godot_cpp/classes/resource.hpp>
#include "features/movie/Director.h"
#include "godot_cpp/classes/input.hpp"
#include "godot_cpp/classes/node.hpp"
#include "godot_cpp/classes/ref.hpp"
#include "godot_cpp/classes/input_event.hpp"
#include "godot_cpp/core/binder_common.hpp"
#include "godot_cpp/core/memory.hpp"
#include "godot_cpp/variant/string_name.hpp"
#include "util/input.hpp"
#include <godot_cpp/classes/timer.hpp>

//#include "SceneStateNormal.h"
using namespace godot;

class SceneStates;

class SceneMenu : public CanvasLayer
{
	GDCLASS(SceneMenu, CanvasLayer)

public:

	SceneMenu();
	~SceneMenu() = default;

	enum SCENE_MODE {
		NORMAL,
		FAST_FORWARD,
		AUTO,
		UNSKIPPABLE,
	};
	virtual void _ready() override;
	virtual void _process(double delta) override;
	virtual void _physics_process(double delta) override;
	virtual void _input(const Ref<InputEvent> &p_event) override;
	void _unhandled_key_input(const Ref<InputEvent>& event) override;
	//void _unhandled_key_input(InputEvent event);

	void init_from_gdscript();
	void start_dialogue();
	void set_scene_mode(SCENE_MODE p_mode);
	void fast_forward_await();
	void handle_state();
	void simulate_keys_for_states(SCENE_MODE go_to_state);

	void auto_dialogue();
	void fast_forward_dialogue();

	void set_dialogue_resource(const Ref<Resource> p_resource);
	void set_dialogue_box(CanvasLayer* p_box);
	void set_vertical_dialogue_box(CanvasLayer* p_box);
	void set_scene_state(Ref<SceneStates> p_state);
	Ref<SceneStates> get_scene_state() const;

	Ref<Resource> get_dialogue_resource() const;
	CanvasLayer* get_dialogue_box()const; 
	CanvasLayer* get_vertical_dialogue_box()const; 

protected:
	static void _bind_methods();

private:
	Input* input = rl::input::get();
	SCENE_MODE scene_mode { SCENE_MODE::NORMAL };

	Ref<SceneStates> scene_state { nullptr };

	Director* director { nullptr };

	StringName line { "start" };
	CanvasLayer* dialogue_box { nullptr };
	CanvasLayer* vertical_dialogue_box { nullptr };
	Ref<Resource> dialogue_resource { nullptr };

	bool is_fast_forwading = false;
	double fast_forward_delay { 0.2 };
};
VARIANT_ENUM_CAST(SceneMenu::SCENE_MODE);
