#pragma once
#include <godot_cpp/classes/object.hpp>
#include <godot_cpp/core/binder_common.hpp>
#include <godot_cpp/core/class_db.hpp>
#include "godot_cpp/classes/ref_counted.hpp"
#include "godot_cpp/classes/resource.hpp"

using namespace godot;

class SceneStateEnum : public RefCounted
{
	GDCLASS(SceneStateEnum, RefCounted)

public:
	enum STATE {
		NORMAL,
		FAST_FORWARD,
		AUTO,
		UNSKIPPABLE,
		IGNORE,
	};
	static void _bind_methods(){
		BIND_ENUM_CONSTANT(NORMAL);
		BIND_ENUM_CONSTANT(FAST_FORWARD);
		BIND_ENUM_CONSTANT(AUTO);
		BIND_ENUM_CONSTANT(UNSKIPPABLE);
	}
};
VARIANT_ENUM_CAST(SceneStateEnum::STATE);
