#pragma once

#include <godot_cpp/classes/canvas_layer.hpp>
#include <godot_cpp/classes/resource.hpp>
#include "features/movie/Director.h"
#include "features/movie/SceneStates.h"
#include "godot_cpp/classes/global_constants.hpp"
#include "godot_cpp/classes/input.hpp"
#include "godot_cpp/classes/node.hpp"
#include "godot_cpp/classes/ref.hpp"
#include "godot_cpp/classes/input_event.hpp"
#include "godot_cpp/classes/wrapped.hpp"
#include "godot_cpp/core/binder_common.hpp"
#include "godot_cpp/variant/array.hpp"
#include "godot_cpp/variant/string.hpp"
#include "godot_cpp/variant/string_name.hpp"
#include "util/input.hpp"
#include <godot_cpp/classes/timer.hpp>

#include "CommandStack.h"
#include "SceneStates.h"
#include "SceneStateEnum.h"

using namespace godot;

class SceneStates;
class CommandStack;

class SceneMenu : public CanvasLayer
{
	GDCLASS(SceneMenu, CanvasLayer)

public:

	SceneMenu();
	~SceneMenu();

	enum DialogueBox {
		HORIZONTAL,
		VERTICAL,
	} dialogue_box;

	virtual void _ready() override;
	virtual void _process(double delta) override;
	virtual void _physics_process(double delta) override;
	virtual void _input(const Ref<InputEvent> &p_event) override;
	void _unhandled_input(const Ref<InputEvent>& p_event) override;
	void _unhandled_key_input(const Ref<InputEvent>& event) override;
	void _exit_tree() override;

	void init_from_gdscript();
	void set_scene_mode(SceneStateEnum::STATE);
	void fast_forward_await();
	void handle_state();
	void simulate_keys_for_states(SceneStateEnum::STATE go_to_state);

	void start_dialogue();
	void next_dialogue(String p_id);
	void register_api();
	void recieve_dialogue_id(StringName p_id);
	void auto_dialogue();
	void fast_forward_dialogue();

	void show_dialogue_box(DialogueBox p_box);
	void hide_dialogue_box(DialogueBox p_box);

	void set_dialogue_resource(const Ref<Resource> p_resource);
	void set_dialogue_box(CanvasLayer* const p_box);
	void set_vertical_dialogue_box(CanvasLayer* const p_box);
	void set_scene_state(SceneStates* const p_state);

	SceneStates* get_scene_state() const;
	Ref<Resource> get_dialogue_resource() const;
	CanvasLayer* get_dialogue_box()const; 
	CanvasLayer* get_vertical_dialogue_box()const; 

	Director* director { nullptr };
protected:
	static void _bind_methods();

private:
	Input* input = rl::input::get();
	//SceneStateEnum::STATE scene_mode { SceneStateEnum::STATE::NORMAL };

	SceneStates* current_state { nullptr };
	TypedDictionary<StringName, SceneStates> states;

	Array register_apis;
	CommandStack* command_stack = { nullptr };

	StringName line { "start" };
	CanvasLayer* current_dialogue_box { nullptr };
	CanvasLayer* horizontal_dialogue_box { nullptr };
	CanvasLayer* vertical_dialogue_box { nullptr };
	Ref<Resource> dialogue_resource { nullptr };
};
//VARIANT_ENUM_CAST(SceneMenu::SceneStateEnum::STATE);
