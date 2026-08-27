#pragma once

#include <godot_cpp/classes/node2d.hpp>
#include "godot_cpp/classes/compressed_texture2d.hpp"
#include "godot_cpp/classes/ref.hpp"
#include "godot_cpp/classes/wrapped.hpp"
#include <godot_cpp/classes/sprite2d.hpp>

#include "ActorResource.h"
#include "godot_cpp/core/memory.hpp"
#include "features/movie/ActorResource.h"
#include "godot_cpp/variant/string_name.hpp"
#include "godot_cpp/variant/typed_dictionary.hpp"
#include <godot_cpp/classes/tween.hpp>

using namespace godot;

class Actor : public Node2D
{
	GDCLASS(Actor, Node2D)
	
	public:

	Actor();
	~Actor() = default;


	void bind_resources(const Ref<ActorResource>& p_resource);
	virtual void _ready() override;

	void create_actor();
	void change_expression(StringName p_expression, bool p_is_cut, bool p_is_different_pose);

	void on_tween_finished(int p_index);

	void set_name(const StringName p_name);
	StringName get_name()const;
	Ref<ActorResource> get_actor_data() const;
	
	private:
	static void _bind_methods();

	Ref<ActorResource> actor_data { nullptr } ;
	StringName name;
	double fade_speed { 0.5 };

	Ref<Tween> tween;
	//double tween_speed_scale { 1.0 }; for local tween speed
	//TypedDictionary<StringName, CompressedTexture2D> actor_expression = { };

	Sprite2D* sprite_01 {memnew(Sprite2D)};
	Sprite2D* sprite_02 {memnew(Sprite2D)};


};
