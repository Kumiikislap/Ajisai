#include "SceneStateFastForward.h"
#include "features/movie/SceneMenu.h"
#include "features/movie/SceneStateAuto.h"
#include "features/movie/SceneStates.h"
#include "godot_cpp/classes/input.hpp"
#include "godot_cpp/classes/ref.hpp"
#include "godot_cpp/core/memory.hpp"


Ref<SceneStates> SceneStateFastForward::handleInput(SceneMenu& scene_menu, Input* input)
{
	if (input->is_action_just_released("fast_forward_dialogue")) {
		return Ref<SceneStateNormal>(memnew(SceneStateNormal));
	}
	if (input->is_action_just_pressed("auto_hotkey"))
	{
		return Ref<SceneStateAuto>(memnew(SceneStateAuto));
	}
	return NULL;
}

void SceneStateFastForward::physics_update(SceneMenu& scene_menu, double delta)
{
	timer += delta;
	if (timer > delay_time)
	{
		// add signal or process scene_menu
		timer -= delay_time;
		scene_menu.fast_forward_dialogue();
	}
}
