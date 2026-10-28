#include "SceneStateNormal.h"
#include "features/movie/SceneMenu.h"
#include "features/movie/SceneStateAuto.h"
#include "godot_cpp/classes/input.hpp"
#include "SceneStateFastForward.h"

Ref<SceneStates> SceneStateNormal::handleInput(SceneMenu& scene_menu, Input* input)
{
	if (input->is_action_just_pressed("fast_forward_dialogue")) {
		return Ref<SceneStateFastForward>(memnew(SceneStateFastForward));
	}
	else if (input->is_action_just_pressed("auto_hotkey")) {
		return Ref<SceneStateAuto>(memnew(SceneStateAuto));
	}
	return NULL;
}
