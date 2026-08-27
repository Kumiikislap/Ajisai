#include <cassert>
#include "Actor.h"
#include "core/assert.hpp"
#include "features/movie/ActorResource.h"
#include "godot_cpp/classes/node.hpp"
#include "godot_cpp/classes/ref.hpp"
#include "godot_cpp/classes/sprite2d.hpp"
#include "godot_cpp/classes/tween.hpp"
#include "godot_cpp/core/memory.hpp"
#include "godot_cpp/variant/callable.hpp"
#include "godot_cpp/variant/color.hpp"
#include "godot_cpp/variant/string_name.hpp"
#include "godot_cpp/variant/utility_functions.hpp"
#include "godot_cpp/variant/variant.hpp"
#include "util/scene.hpp"
#include <godot_cpp/variant/vector2.hpp>
#include <godot_cpp/classes/property_tweener.hpp>
#include <godot_cpp/variant/color.hpp>
#include <godot_cpp/classes/tween.hpp>
#include <godot_cpp/classes/callback_tweener.hpp>


Actor::Actor()
{
}

void Actor::bind_resources(const Ref<ActorResource>& p_resource)
{
	actor_data = p_resource;
	assert(actor_data != nullptr and "actor data is null!");
	//create_actor();
	//change_expression("smile");
}

void Actor::_ready()
{           
	// avoid using ready, it gets called before a resource is passed
	// sprite 2 is above the layer of sprite 1
	this->add_child(sprite_02);
	this->add_child(sprite_01);
	//this->set_global_position(Vector2(900, 700));
	sprite_01->set_z_index(1); // sprite to fade
	sprite_02->set_z_index(0);
}

void Actor::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("on_tween_finished",  "index"), &Actor::on_tween_finished);
}


void Actor::create_actor()
{
	this->name = actor_data->character_name;
	sprite_01->set_texture(actor_data->character_expressions.get("happy", nullptr));
}

void Actor::change_expression(StringName p_expression, bool p_is_cut = false, bool p_is_different_pose = false)
{
	// TODO add cut anim for different poses -- if different pose
	if (tween.is_valid() and  tween->is_running())
	{
		//tween->set_speed_scale(100);
		tween->custom_step(2);
	}

	// case 0 if sprite 2 is the next sprite to new expression to store
	switch (sprite_02->get_z_index())
	{
		case 0:
			sprite_02->set_modulate(Color(1,1,1,1)) ;
			sprite_02->set_texture(actor_data->character_expressions.get(p_expression, "shocked")) ;
			if (p_is_cut){
				sprite_02->set_z_index(2);
				return;
			}
			if (p_is_different_pose){
				sprite_01->set_modulate(Color(1,1,1,0));
				return;
			}
			tween = create_tween();
			tween->tween_property(sprite_01, "modulate:a", 0.0, fade_speed);
			tween->tween_callback(Callable(this, "on_tween_finished").bind(2));

			//tween->connect("finished", Callable(this, "on_tween_finished").bind(2));
			break;
		case 2:
			sprite_01->set_modulate(Color(1,1,1,1)) ;
			sprite_01->set_texture(actor_data->character_expressions.get(p_expression, "shocked")) ;

			if (p_is_cut){
				sprite_02->set_z_index(0);
				return;
			}
			if (p_is_different_pose){
				sprite_02->set_modulate(Color(1,1,1,0));
				return;
			}
			tween = create_tween();
			tween->tween_property(sprite_02, "modulate:a", 0.0, fade_speed);
			tween->tween_callback(Callable(this, "on_tween_finished").bind(0));
			//tween->connect("finished", Callable(this, "on_tween_finished").bind(0));
			break;
	}
	UtilityFunctions::print("reached actor method expr");
}

void Actor::on_tween_finished( int p_index)
{
	sprite_02->set_z_index(p_index);
	UtilityFunctions::print(sprite_02->get_z_index());
}

void Actor::set_name(const StringName p_name)
{
	this->name = p_name;
}

StringName Actor::get_name() const
{
	return name;
}

Ref<ActorResource> Actor::get_actor_data() const
{
	return actor_data;
}
