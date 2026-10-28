#pragma once

#include <cstddef>
#include "SceneStates.h"
#include "features/movie/SceneMenu.h"
#include "features/movie/SceneStateNormal.h"
#include "godot_cpp/classes/ref.hpp"
#include "godot_cpp/classes/wrapped.hpp"
#include "godot_cpp/core/memory.hpp"
#include "godot_cpp/variant/utility_functions.hpp"

class SceneStateFastForward : public SceneStates
{
	GDCLASS(SceneStateFastForward, SceneStates)
public:
	SceneStateFastForward() = default;
	~SceneStateFastForward() = default;

	virtual Ref<SceneStates> handleInput(SceneMenu& scene_menu, Input* input) override;

	virtual void update(SceneMenu& scene_menu) override
	{
		return;
	}
	void physics_update(SceneMenu& scene_menu, double delta) override;

	void set_delay(double p_delay)
	{
		delay_time = p_delay;
	}

protected:
	static void _bind_methods(){}
private:
	double timer { 0.0 };
	double delay_time { 0.2 };
};
