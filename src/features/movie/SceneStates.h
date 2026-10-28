#pragma once

#include <godot_cpp/classes/ref_counted.hpp>
#include "godot_cpp/classes/input.hpp"
#include "godot_cpp/classes/ref.hpp"
#include "godot_cpp/classes/wrapped.hpp"
#include "SceneMenu.h"
#include "godot_cpp/variant/utility_functions.hpp"

using namespace godot;

class SceneMenu;

class SceneStates : public RefCounted
{
	GDCLASS(SceneStates, RefCounted)

public:
	SceneStates() = default;
	virtual ~SceneStates() {};
	virtual Ref<SceneStates> handleInput(SceneMenu& scene_menu, Input* input) {return this;};
	virtual void update(SceneMenu& scene_menu){}
	virtual void physics_update(SceneMenu& scene_menu, double delta ) {}
	virtual void enter(SceneMenu& scene_menu){UtilityFunctions::print("state entered");}
	virtual void exit(SceneMenu& scene_menu){UtilityFunctions::print("state exited");}

protected:
	static void _bind_methods(){}
};
