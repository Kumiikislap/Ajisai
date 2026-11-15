#pragma once

#include "godot_cpp/classes/animated_sprite2d.hpp"
#include "godot_cpp/classes/node2d.hpp"
#include "godot_cpp/variant/string_name.hpp"
#include <godot_cpp/classes/tween.hpp>
#include <godot_cpp/classes/property_tweener.hpp>

using namespace godot;

class Actor : public Node2D
{
	GDCLASS(Actor, Node2D)
	
	public:

	Actor();
	~Actor() = default;

	enum CurrentPose {
		POSE_A = 1,
		POSE_B = 2,
	} current_pose_enum;

	struct Pose
	{
		enum CurrentExpression {
			EXPR_1,
			EXPR_2,
		} current_expression_enum { EXPR_1  };
		AnimatedSprite2D* pose { nullptr };
		AnimatedSprite2D* expr1 { nullptr };
		AnimatedSprite2D* expr2 { nullptr };
		AnimatedSprite2D* current_expr_ptr { expr1 };
	};

	virtual void _ready() override;

	void change_pose(StringName p_pose);
	void change_expression(StringName p_expression, bool p_is_cut, bool p_is_different_pose);
	void skip_animation();
	void on_tween_finished(int p_index);

	void set_name(const StringName p_name);
	void set_fade_speed(const double p_speed);

	StringName get_name() const;
	double get_fade_speed() const;
	
	private:
	static void _bind_methods();

	Pose poseA;
	Pose poseB;
	Pose current_pose_struct;

	StringName name;
	double fade_speed { 0.5 }; 

	Ref<Tween> tween;
	Ref<Tween> tween_next;

	
};
