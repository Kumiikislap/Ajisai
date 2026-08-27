#pragma once

#include <godot_cpp/classes/node.hpp>

#include "features/movie/ActorResource.h"
#include "features/movie/CharactersResource.h"
#include "godot_cpp/classes/ref.hpp"
#include "godot_cpp/classes/wrapped.hpp"
#include "godot_cpp/core/memory.hpp"
#include "godot_cpp/variant/array.hpp"
#include "godot_cpp/variant/string.hpp"
#include "godot_cpp/variant/string_name.hpp"
#include "godot_cpp/variant/typed_array.hpp"
#include "godot_cpp/variant/typed_dictionary.hpp"
#include "services/DialogueManagerWrapper.h"
#include <godot_cpp/variant/vector2.hpp>
#include <godot_cpp/classes/control.hpp>
#include "Actor.h"
#include "ActorsLayer.h"
#include "TweenAnimations.h"

using namespace godot;

class Director : public Node
{
	GDCLASS(Director, Node)
	
	public:
	Director();
	~Director() = default;
	
	void build_services(); 
	virtual void _ready() override;
	void init_from_gdscript();   // called from main.gd _ready()

	// public APIs
	void add_actor(StringName p_name);
	void remove_active_actor(StringName p_name);
	void change_expression(StringName p_actor, StringName p_expression, bool p_is_cut = false, bool p_is_different_pose = false);

	void hide_actor(StringName p_name);
	void show_actor(StringName p_name);

	void set_actor_position(StringName p_name, Vector2 p_pos);
	void set_actor_preset_position(StringName p_name, ActorsLayer::POSITION_PRESET p_preset );

	void hide_actors_layer();
	void show_actors_layer();

	Actor* get_actor_from_scene(StringName p_name);

	void set_dialogue_resource(const Ref<Resource> p_resource);
	void set_cast(const Ref<CharactersResource>& p_cast);
	void set_dialogue_box(Control* p_box);

	Ref<CharactersResource> get_cast() const;

	Ref<Resource> get_dialogue_resource() const;
	Control* get_dialogue_box()const; 

	private:
	static void _bind_methods();
	DialogueManagerWrapper* dialogue_manager { memnew(DialogueManagerWrapper)};
	Control* dialogue_box { nullptr };

	Ref<Resource> dialogue_resource { nullptr };
	Ref<CharactersResource> cast { nullptr };
	Ref<ActorResource> character;

	//TypedArray<Actor> characters_in_scene;
	TypedDictionary<StringName, Actor> characters_in_scene;

	ActorsLayer* actors_layer { memnew(ActorsLayer) };
	TweenAnimations* tween_animations { nullptr };

};
