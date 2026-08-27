#include <cassert>
#include "Director.h"
#include "core/assert.hpp"
#include "features/movie/Actor.h"
#include "features/movie/ActorResource.h"
#include "features/movie/CharactersResource.h"
#include "features/movie/TweenAnimations.h"
#include "godot_cpp/classes/control.hpp"
#include "godot_cpp/classes/node.hpp"
#include "godot_cpp/core/class_db.hpp"
#include "godot_cpp/core/object.hpp"
#include "godot_cpp/core/property_info.hpp"
#include "godot_cpp/templates/vector.hpp"
#include "godot_cpp/variant/string_name.hpp"
#include "godot_cpp/variant/typed_array.hpp"
#include "godot_cpp/variant/utility_functions.hpp"
#include "godot_cpp/variant/variant.hpp"
#include "util/bind.hpp"
#include "util/conversions.hpp"

Director::Director()
{
};

void Director::build_services()
{
	this->add_child(dialogue_manager);
}

void Director::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("set_cast", "p_cast" ), &Director::set_cast);
	ClassDB::bind_method(D_METHOD("get_cast"), &Director::get_cast);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "cast", godot::PROPERTY_HINT_RESOURCE_TYPE, "CharactersResource"), "set_cast", "get_cast");

	rl::bind_property(Director, dialogue_resource, Ref<Resource>);
	rl::bind_property(Director, dialogue_box, Control*);
	ClassDB::bind_method(D_METHOD("add_actor", "name"), &Director::add_actor);
	ClassDB::bind_method(D_METHOD("change_expression", "name", "expression", "is_cut", "is_different_pose"), &Director::change_expression, DEFVAL(""), DEFVAL(""), DEFVAL(false), DEFVAL(false));
	ClassDB::bind_method(D_METHOD("set_actor_position", "name", "position"), &Director::set_actor_position);
	ClassDB::bind_method(D_METHOD("hide_actor", "name"), &Director::hide_actor);
	ClassDB::bind_method(D_METHOD("show_actor", "name"), &Director::show_actor);
	ClassDB::bind_method(D_METHOD("remove_active_actor", "name"), &Director::remove_active_actor);
	rl::bind_member_function(Director, init_from_gdscript);
	rl::bind_member_function(Director, hide_actors_layer);
	rl::bind_member_function(Director, show_actors_layer);
}

// overrided in gdscript
void Director::_ready()
{
}

// called from ready in gdscipt
void Director::init_from_gdscript()
{
	//this->add_child(tween_animations);
	this->add_child(actors_layer);
	UtilityFunctions::printerr(characters_in_scene.keys());

	Node* tween_anim  = this->find_child("TweenAnimations");
	tween_animations = rl::gdcast<TweenAnimations>(tween_anim);
}

void Director::add_actor(StringName p_name)
{
	UtilityFunctions::print( this->cast->characters.get(p_name, nullptr));
	UtilityFunctions::print( this->cast->characters.has(p_name));

	// check if the cast has the character name argument
	// a condition that should be always true
	assert(cast->characters.has(p_name) and "Can't find actor name!");
	// check if actor already exist in scene
	assert(not characters_in_scene.has(p_name) and "actor already exist in scene!");

	Ref<ActorResource> chara = cast->characters.get(p_name, nullptr);

	Actor* actor { memnew(Actor) };
	actors_layer->add_actor_to_layer(actor);
	actor->bind_resources(chara);
	actor->create_actor();
	characters_in_scene.set(p_name, actor);
}

void Director::show_actor(StringName p_name)
{
	Actor* actor =  get_actor_from_scene(p_name);
	//actor->show();
	tween_animations->slide(actor, TweenAnimations::DIRECTION::RIGHT);
}

void Director::hide_actor(StringName p_name)
{
	Actor* actor =  get_actor_from_scene(p_name);
	//actor->hide();
	//tween_animations->fade_out(actor);
	//tween_animations->fade_out(actors_layer->control_layer);
	//tween_animations->fade_out(dialogue_box);
	tween_animations->slide(actor, TweenAnimations::DIRECTION::LEFT);
}

void Director::change_expression(StringName p_name, StringName p_expression, bool p_is_cut, bool p_is_different_pose)
{
	Actor* active_actor = get_actor_from_scene(p_name);
	assert(active_actor->get_actor_data()->character_expressions.has(p_expression) and "character expression not found!");
	active_actor->change_expression(p_expression, p_is_cut, p_is_different_pose);
}

void Director::set_actor_position(StringName p_name, Vector2 pos)
{
	Actor* actor = get_actor_from_scene(p_name);
	actor->set_position(pos);
}

void Director::set_actor_preset_position(StringName p_name, ActorsLayer::POSITION_PRESET p_preset )
{
	Actor* actor = get_actor_from_scene(p_name);
	actors_layer->set_actor_preset_position(actor, p_preset);
}

void Director::remove_active_actor(StringName p_name)
{
	assert(this->characters_in_scene.erase(p_name) and "Can't erase non-existing character in scene!");
}

Actor* Director::get_actor_from_scene(StringName p_name)
{
	assert(characters_in_scene.has(p_name) and "invalid actor name argument! or actor is not in scene");
	auto actor_name =  characters_in_scene.get(p_name, nullptr);
	Actor* active_actor =  cast_to<Actor>(actor_name);
	return active_actor;
}

void Director::hide_actors_layer()
{
	actors_layer->hide();
}

void Director::show_actors_layer()
{
	actors_layer->show();
}

void Director::set_cast(const Ref<CharactersResource>& p_cast)
{
	cast = p_cast;
}

Ref<CharactersResource> Director::get_cast() const
{
	return cast;
}

void Director::set_dialogue_resource(Ref<Resource> p_resource)
{
	this->dialogue_resource = p_resource;
}

Ref<Resource> Director::get_dialogue_resource() const
{
	return dialogue_resource;
}

void Director::set_dialogue_box(Control* p_box)
{
	this->dialogue_box = p_box;
}

Control* Director::get_dialogue_box() const
{
	return this->dialogue_box ;
}
