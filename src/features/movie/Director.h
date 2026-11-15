#pragma once

#include <godot_cpp/classes/node.hpp>

#include "features/movie/CharactersResource.h"
#include "godot_cpp/classes/ref.hpp"
#include "godot_cpp/classes/resource.hpp"
#include "godot_cpp/classes/wrapped.hpp"
#include "godot_cpp/variant/array.hpp"
#include "godot_cpp/variant/string.hpp"
#include "godot_cpp/variant/string_name.hpp"
#include "godot_cpp/variant/typed_dictionary.hpp"
#include <godot_cpp/variant/vector2.hpp>
#include <godot_cpp/classes/control.hpp>
#include "Actor.h"
#include "ActorsLayer.h"
#include "features/services/TweenAnimations.h"

#include "ActorAnimations.h"

using namespace godot;

class Director : public Node
{
	GDCLASS(Director, Node)
	
	public:
	Director();
	~Director(); 
	
	void build_services(); 
	virtual void _ready() override;
	void init_from_gdscript();   // called from main.gd _ready()
	

	// public APIs
	void load_actors();
	void create_actors();
	void add_actor(StringName p_name);
	void remove_active_actor(StringName p_name);
	void change_pose(StringName p_actor, StringName p_pose);
	void change_expression(StringName p_actor, StringName p_expression, bool p_is_cut = false, bool p_is_different_pose = false);

	void hide_actor(StringName p_name);
	void show_actor(StringName p_name);

	void set_actor_position(StringName p_name, Vector2 p_pos);
	void set_actor_preset_position(StringName p_name, ActorsLayer::POSITION_PRESET p_preset );

	void hide_actors_layer();
	void show_actors_layer();

	//Actor* get_actor_from_scene(StringName p_name);

	void set_cast(const Ref<CharactersResource>& p_cast);

	//Ref<CharactersResource> get_cast() const;

	private:
	Ref<CharactersResource> cast_resource;
	TypedDictionary<StringName, Actor> actors;

	ActorsLayer* actors_layer { nullptr  } ;
	ActorAnimations* actor_animations { nullptr };
	TweenAnimations* tween_animations { nullptr };

	protected:
	static void _bind_methods();
};
