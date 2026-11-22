#include <cassert>
#include "Actor.h"
#include "godot_cpp/classes/animated_sprite2d.hpp"
#include "godot_cpp/classes/ref.hpp"
#include "godot_cpp/classes/sprite_frames.hpp"
#include "godot_cpp/classes/tween.hpp"
#include "godot_cpp/core/error_macros.hpp"
#include "godot_cpp/core/print_string.hpp"
#include "godot_cpp/variant/array.hpp"
#include "godot_cpp/variant/string.hpp"
#include "godot_cpp/variant/string_name.hpp"
#include "godot_cpp/variant/typed_array.hpp"
#include "godot_cpp/variant/variant.hpp"
#include "util/debug.hpp"
#include "util/bind.hpp"


Actor::Actor()
{
}

void Actor::_ready()
{
	//  ready gets called before a resource is passed
	poseA.pose = cast_to<AnimatedSprite2D>(find_child("poseA"));
	poseA.expr1 = cast_to<AnimatedSprite2D>(find_child("exprA1"));
	poseA.expr2 = cast_to<AnimatedSprite2D>(find_child("exprA2"));

	poseA.current_expr_ptr = poseA.expr1;
	poseA.expr2->set_modulate(Color(1,1,1,0));

	poseB.pose = cast_to<AnimatedSprite2D>(find_child("poseB"));
	poseB.expr1 = cast_to<AnimatedSprite2D>(find_child("exprB1"));
	poseB.expr2 = cast_to<AnimatedSprite2D>(find_child("exprB2"));

	poseB.current_expr_ptr = poseA.expr1;
	poseB.expr2->set_modulate(Color(1,1,1,0));

	current_pose_enum = POSE_A;
	current_pose_struct = poseA;
	poseA.pose->set_z_index(0);
	poseB.pose->set_z_index(1);
	poseB.pose->set_modulate(Color(1,1,1,0));

	current_pose = default_pose;
	current_expression = default_expression;

	TypedArray<AnimatedSprite2D> children = get_children();
	for (auto child : children)
	{
		cast_to<AnimatedSprite2D>(child)->set_process_mode(Node::ProcessMode::PROCESS_MODE_DISABLED);
	}
}

void Actor::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("on_tween_finished",  "index"), &Actor::on_tween_finished);
	rl::bind_property(Actor, name, StringName);
	rl::bind_property(Actor, fade_speed, double);
	rl::bind_property(Actor, default_pose, StringName); 
	rl::bind_property(Actor, default_expression, StringName); 
}

void Actor::change_pose(StringName p_pose)
{
	Ref<SpriteFrames> sprite = current_pose_struct.pose->get_sprite_frames();
	assert(sprite->has_animation(p_pose));

	tween = create_tween()->set_trans(Tween::TRANS_CUBIC)->set_ease(Tween::EASE_IN);
	tween_next = create_tween()->set_trans(Tween::TransitionType::TRANS_CUBIC)->set_ease(Tween::EASE_OUT); 
	switch (current_pose_enum) {
		case POSE_A:
			poseB.pose->set_animation(p_pose);
			tween->tween_property(poseA.pose, "modulate:a", 0.0, fade_speed); 
			tween_next->tween_property(poseB.pose, "modulate:a", 1.0, fade_speed);
			poseA.pose->set_z_index(0);
			poseB.pose->set_z_index(1);
			current_pose_enum = POSE_B;
			current_pose_struct = poseB;
			break;
		case POSE_B:
			poseA.pose->set_animation(p_pose);
			tween->tween_property(poseB.pose, "modulate:a", 0.0, fade_speed); 
			tween_next->tween_property(poseA.pose, "modulate:a", 1.0, fade_speed); 
			poseA.pose->set_z_index(1);
			poseB.pose->set_z_index(0);
			current_pose_enum = POSE_A;
			current_pose_struct = poseA;
			break;
	}
	pprint(current_pose_enum);
}

void Actor::change_expression(StringName p_expression, bool p_is_cut = false, bool p_is_different_pose = false)
{
	p_expression.to_lower();
	Ref<SpriteFrames> sprite = current_pose_struct.current_expr_ptr->get_sprite_frames();
	StringName current_expr = current_pose_struct.current_expr_ptr->get_animation();
	StringName next_expression = StringName("_") + p_expression;
	ERR_FAIL_COND_MSG(!sprite->has_animation(current_pose + next_expression),vformat("Animation not found! %s", current_pose + next_expression));

	// NOTE:  change expr with the matching pose : pose + expr_name
	tween = create_tween()->set_trans(Tween::TRANS_CUBIC)->set_ease(Tween::EASE_IN);
	tween_next = create_tween()->set_trans(Tween::TransitionType::TRANS_CUBIC)->set_ease(Tween::EASE_OUT); 

	switch (current_pose_struct.current_expression_enum) {
		case Pose::EXPR_1:
			current_pose_struct.expr2->set_animation(current_pose + StringName("_") + p_expression);
			current_pose_struct.expr2->set_z_index(1);
			current_pose_struct.expr1->set_z_index(0);
			tween->tween_property(current_pose_struct.expr1, "modulate:a", 0.0, fade_speed); 
			tween_next->tween_property(current_pose_struct.expr2, "modulate:a", 1.0, fade_speed); 
			current_pose_struct.current_expression_enum = current_pose_struct.EXPR_2;
			current_expression = p_expression;
			break;
		case Pose::EXPR_2:
			current_pose_struct.expr1->set_animation(current_pose + StringName("_") + p_expression);
			current_pose_struct.expr1->set_z_index(1);
			current_pose_struct.expr2->set_z_index(0);
			tween->tween_property(current_pose_struct.expr2, "modulate:a", 0.0, fade_speed); 
			tween_next->tween_property(current_pose_struct.expr1, "modulate:a", 1.0, fade_speed); 
			current_expression = p_expression;
			current_pose_struct.current_expression_enum = current_pose_struct.EXPR_1;
			break;
	}
	pprint(current_pose_struct.current_expression_enum);
}

void Actor::skip_animation()
{
	if (tween.is_valid() and tween->is_running())
	{
		tween->custom_step(2.0);
		tween_next->custom_step(2.0);
	}
}

void Actor::on_tween_finished( int p_index)
{
	change_pose("turdus");
}

void Actor::set_name(const StringName p_name)
{
	this->name = p_name.to_lower();
}

void Actor::set_fade_speed(const double p_speed)
{
	fade_speed = p_speed;
}

double Actor::get_fade_speed() const
{
	return fade_speed;
}

StringName Actor::get_name() const
{
	return name;
}
StringName Actor::get_current_pose() const
{
	return current_pose;
}
StringName Actor::get_current_expression() const
{
	return current_expression;
}
void Actor::set_default_pose(const StringName p_pose)
{
	default_pose = p_pose;
}
void Actor::set_default_expression(const StringName p_expression)
{
	default_expression = p_expression;
}
StringName Actor::get_default_pose() const
{
	return default_pose;
}
StringName Actor::get_default_expression() const
{
	return default_expression;
}
