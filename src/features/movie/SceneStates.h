#pragma once

#include <sys/types.h>
#include <godot_cpp/classes/ref_counted.hpp>
#include "godot_cpp/classes/input.hpp"
#include "godot_cpp/classes/object.hpp"
#include "godot_cpp/classes/ref.hpp"
#include "godot_cpp/classes/wrapped.hpp"
#include "godot_cpp/variant/utility_functions.hpp"
#include "SceneMenu.h"
#include "SceneStateEnum.h"

using namespace godot;

class SceneMenu;

class SceneStates : public Object
{
	GDCLASS(SceneStates, Object)

public:
	SceneStates() = default;
	~SceneStates() {};
	virtual SceneStateEnum::STATE handleInput(SceneMenu& scene_menu, Input* input) { return SceneStateEnum::STATE::IGNORE; };
	virtual void update(SceneMenu& scene_menu){}
	virtual void physics_update(SceneMenu& scene_menu, double delta ) {}
	virtual void enter(SceneMenu& scene_menu){UtilityFunctions::print("state entered");}
	virtual void exit(SceneMenu& scene_menu){UtilityFunctions::print("state exited");}

protected:
	static void _bind_methods(){}
};

class SceneStateNormal : public SceneStates
{
	GDCLASS(SceneStateNormal, SceneStates)
public:
	SceneStateNormal() {}
	~SceneStateNormal() = default;

	virtual SceneStateEnum::STATE handleInput(SceneMenu& scene_menu, Input* input) override;
	virtual void update(SceneMenu& scene_menu) override
	{
	}

protected:
	static void _bind_methods(){}
};

class SceneStateFastForward : public SceneStates
{
	GDCLASS(SceneStateFastForward, SceneStates)
public:
	SceneStateFastForward() = default;
	~SceneStateFastForward() = default;

	virtual SceneStateEnum::STATE handleInput(SceneMenu& scene_menu, Input* input) override;

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

class SceneStateAuto : public SceneStates
{
	GDCLASS(SceneStateAuto, SceneStates)
public:
	SceneStateAuto() {}
	~SceneStateAuto() = default;

	virtual SceneStateEnum::STATE handleInput(SceneMenu& scene_menu, Input* input) override;
	void update(SceneMenu& scene_menu) override
	{
	}
	void physics_update(SceneMenu& scene_menu, double delta) override;
	void enter(SceneMenu& scene_menu) override;
	void exit(SceneMenu& scene_menu) override;


protected:
	static void _bind_methods(){}
private:
};
