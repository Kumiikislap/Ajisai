#pragma once

#include <godot_cpp/classes/resource.hpp>
#include "godot_cpp/classes/global_constants.hpp"
#include "godot_cpp/classes/wrapped.hpp"
#include "godot_cpp/core/class_db.hpp"
#include "godot_cpp/core/object.hpp"
#include "util/bind.hpp"
#include <godot_cpp/variant/typed_dictionary.hpp>
#include <godot_cpp/classes/compressed_texture2d.hpp>
#include <godot_cpp/variant/string_name.hpp>

using namespace godot;

class ActorResource : public Resource
{
	GDCLASS(ActorResource, Resource)
	
	ActorResource() = default;
	~ActorResource() = default;

	protected:
	static void _bind_methods()
	{
		rl::bind_property(ActorResource, character_name, StringName);

		ClassDB::bind_method(D_METHOD("set_character_expressions", "p_character_expression" ), &ActorResource::set_character_expressions );
		ClassDB::bind_method(D_METHOD("get_character_expressions"), &ActorResource::get_character_expressions);
		ADD_PROPERTY(PropertyInfo(Variant::DICTIONARY, "character_expressions", godot::PROPERTY_HINT_DICTIONARY_TYPE, "StringName;CompressedTexture2D"), "set_character_expressions", "get_character_expressions");

	}

	void set_character_name(const StringName p_character_name)
	{ 
		character_name = p_character_name;
	}

	void set_character_expressions(const TypedDictionary<StringName, CompressedTexture2D> p_character_expression)
	{
		character_expressions = p_character_expression;
	}

	StringName get_character_name() const
	{
		return character_name;
	}

	TypedDictionary<StringName, CompressedTexture2D> get_character_expressions() const
	{
		return character_expressions;
	}

	public:
	StringName character_name;
	TypedDictionary<StringName, CompressedTexture2D> character_expressions;

};
