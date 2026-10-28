#pragma once

#include <cstddef>
#include "SceneStates.h"
#include "features/movie/SceneMenu.h"
#include "godot_cpp/classes/ref.hpp"
#include "godot_cpp/classes/wrapped.hpp"
#include "godot_cpp/core/memory.hpp"

class SceneMenu;

class SceneStateAuto : public SceneStates
{
	GDCLASS(SceneStateAuto, SceneStates)
public:
	SceneStateAuto() {}
	~SceneStateAuto() = default;

	virtual Ref<SceneStates> handleInput(SceneMenu& scene_menu, Input* input) override;
	void update(SceneMenu& scene_menu) override
	{
	}
	void physics_update(SceneMenu& scene_menu, double delta) override;
	void enter(SceneMenu& scene_menu) override;
	void exit(SceneMenu& scene_menu) override;


protected:
	static void _bind_methods(){}
private:
	bool is_auto = false;
	double auto_timer { 0.0 };
	double auto_duration { 2.0 };
};
