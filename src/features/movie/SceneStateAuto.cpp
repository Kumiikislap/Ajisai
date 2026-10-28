#include <cassert>
#include <cstddef>
#include "SceneStateAuto.h"
#include "features/movie/SceneMenu.h"
#include "features/movie/SceneStateNormal.h"
#include "features/movie/SceneStateFastForward.h"
#include "features/movie/SceneStates.h"
#include "godot_cpp/classes/ref.hpp"


Ref<SceneStates> SceneStateAuto::handleInput(SceneMenu& scene_menu, Input* input)
{
	if (input->is_action_just_pressed("auto_hotkey"))
	{
		return Ref<SceneStateNormal>(memnew(SceneStateNormal));
	}
	if (input->is_action_just_pressed("fast_forward_dialogue")) {
		return Ref<SceneStateFastForward>(memnew(SceneStateFastForward));
	}

	return NULL;
}

void SceneStateAuto::physics_update(SceneMenu& scene_menu, double delta)
{
}

void SceneStateAuto::enter(SceneMenu& scene_menu)
{
	scene_menu.auto_dialogue();
}

void SceneStateAuto::exit(SceneMenu& scene_menu)
{
}
