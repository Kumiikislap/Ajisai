#include <cassert>
#include "Director.h"
#include "core/assert.hpp"
#include "features/movie/Actor.h"
#include "features/movie/ActorResource.h"
#include "features/movie/ActorsLayer.h"
#include "features/movie/CharactersResource.h"
#include "features/services/TweenAnimations.h"
#include "godot_cpp/classes/canvas_layer.hpp"
#include "godot_cpp/classes/control.hpp"
#include "godot_cpp/classes/node.hpp"
#include "godot_cpp/classes/packed_scene.hpp"
#include "godot_cpp/classes/ref.hpp"
#include "godot_cpp/classes/script.hpp"
#include "godot_cpp/core/class_db.hpp"
#include "godot_cpp/core/error_macros.hpp"
#include "godot_cpp/core/memory.hpp"
#include "godot_cpp/core/object.hpp"
#include "godot_cpp/core/property_info.hpp"
#include "godot_cpp/templates/vector.hpp"
#include "godot_cpp/variant/string_name.hpp"
#include "godot_cpp/variant/typed_array.hpp"
#include "godot_cpp/variant/utility_functions.hpp"
#include "godot_cpp/variant/variant.hpp"
#include "util/bind.hpp"
#include "util/conversions.hpp"
#include "util/debug.hpp"


Director::Director()
{
	actors_layer = memnew(ActorsLayer);
	tween_animations = memnew(TweenAnimations);
	//actor_animations = memnew(ActorAnimations);
	add_child(actors_layer);
	add_child(tween_animations);
	assert(actors_layer != nullptr);
	assert(tween_animations != nullptr);
};

void Director::build_services()
{
}

// overrided in gdscript
void Director::_ready()
{
	//init_from_gdscript();
}

// called from ready in gdscipt
void Director::init_from_gdscript()
{
}

// resources are passed after ready
void Director::load_actors()
{
	assert(cast_resource.is_valid());
	Array charas = cast_resource->get_characters().values();
	for (auto chara : charas)
	{
		Node* actor_node = cast_to<PackedScene>(chara)->instantiate();
		Actor* actor = cast_to<Actor>(actor_node);
		actors.set(actor->get_name(), actor);
		actors_layer->add_child(actor);
		actor->hide();
	}
	pprint(actors);
}

// build the actors and store to arena - lmao godot
void Director::create_actors()
{
}

void Director::add_actor(StringName p_name)
{
}

// TODO add animation to show and hide
void Director::show_actor(StringName p_name)
{
	StringName name = p_name.to_lower();
	assert(actors.has(name));
	Actor* a = cast_to<Actor>(actors.get(name, nullptr));
	a->show();
}

void Director::hide_actor(StringName p_name)
{
	StringName name = p_name.to_lower();
	assert(actors.has(name));
	Actor* a = cast_to<Actor>(actors.get(name, nullptr));
	a->hide();
}

void Director::change_expression(StringName p_name, StringName p_expression, bool p_is_cut , bool p_is_different_pose)
{
	cast_to<Actor>(actors.get(p_name, nullptr))->change_expression(p_expression, p_is_cut, p_is_different_pose);
}

void Director::change_pose(StringName p_actor, StringName p_pose)
{
	cast_to<Actor>(actors.get(p_actor, nullptr))->change_pose(p_pose);
}

void Director::set_actor_position(StringName p_name, Vector2 pos)
{
	cast_to<Actor>(actors.get(p_name, nullptr))->set_position(pos);
}

void Director::set_actor_preset_position(StringName p_name, ActorsLayer::POSITION_PRESET p_preset )
{
//	Actor* actor = get_actor_from_scene(p_name);
//	//actors_layer->set_actor_preset_position(actor, p_preset);
}

void Director::remove_active_actor(StringName p_name)
{
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
	cast_resource = p_cast;
}

TypedDictionary<StringName, Actor> Director::get_actors() const
{
	return actors;
}

void Director::_bind_methods()
{

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

Director::~Director()
{
}
