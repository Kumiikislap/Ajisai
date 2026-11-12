#include "SceneStates.h"
#include "SceneMenu.h"
#include "SceneStateEnum.h"

SceneStateEnum::STATE SceneStateNormal::handleInput(SceneMenu& scene_menu, Input* input)
{
	if (input->is_action_just_pressed("fast_forward_dialogue")) {
		return SceneStateEnum::STATE::FAST_FORWARD;
	}
	else if (input->is_action_just_pressed("auto_hotkey")) {
		return SceneStateEnum::STATE::AUTO;
	}
	return SceneStateEnum::STATE::IGNORE;
}

SceneStateEnum::STATE SceneStateFastForward::handleInput(SceneMenu& scene_menu, Input* input)
{
	if (input->is_action_just_released("fast_forward_dialogue")) {
		return SceneStateEnum::STATE::NORMAL;
	}
	if (input->is_action_just_pressed("auto_hotkey"))
	{
		return SceneStateEnum::STATE::AUTO;
	}
	return SceneStateEnum::STATE::IGNORE;
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

SceneStateEnum::STATE SceneStateAuto::handleInput(SceneMenu& scene_menu, Input* input)
{
	if (input->is_action_just_pressed("auto_hotkey"))
	{
		return SceneStateEnum::STATE::NORMAL;
	}
	if (input->is_action_just_pressed("fast_forward_dialogue")) {
		return SceneStateEnum::STATE::FAST_FORWARD;
	}

	return SceneStateEnum::STATE::IGNORE;
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

