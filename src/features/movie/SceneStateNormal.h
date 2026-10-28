#pragma once

#include <cstddef>
#include "SceneStates.h"
#include "features/movie/SceneMenu.h"
#include "godot_cpp/classes/ref.hpp"
#include "godot_cpp/classes/wrapped.hpp"
#include "godot_cpp/core/memory.hpp"

class SceneMenu;

class SceneStateNormal : public SceneStates
{
	GDCLASS(SceneStateNormal, SceneStates)
public:
	SceneStateNormal() {}
	~SceneStateNormal() = default;

	virtual Ref<SceneStates> handleInput(SceneMenu& scene_menu, Input* input) override;
	virtual void update(SceneMenu& scene_menu) override
	{
	}

protected:
	static void _bind_methods(){}
};
