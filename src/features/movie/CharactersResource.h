#pragma once

#include <godot_cpp/classes/resource.hpp>
#include "godot_cpp/classes/global_constants.hpp"
#include "godot_cpp/classes/wrapped.hpp"
#include "godot_cpp/core/class_db.hpp"
#include "godot_cpp/core/object.hpp"
#include <godot_cpp/variant/typed_dictionary.hpp>
#include <godot_cpp/classes/compressed_texture2d.hpp>
#include <godot_cpp/variant/string_name.hpp>

#include "ActorResource.h"

using namespace godot;

class CharactersResource : public Resource
{
	GDCLASS(CharactersResource, Resource)
	
	public:
	
	CharactersResource() = default;
	~CharactersResource() = default;

	void set_characters(const TypedDictionary<StringName, ActorResource> p_characters)
	{
		characters = p_characters;
	}


	TypedDictionary<StringName, ActorResource> get_characters() const
	{
		return characters;
	}

	protected:
	static void _bind_methods()
	{
		ClassDB::bind_method(D_METHOD("set_characters", "p_character_expression" ), &CharactersResource::set_characters );
		ClassDB::bind_method(D_METHOD("get_characters"), &CharactersResource::get_characters);
		ADD_PROPERTY(PropertyInfo(Variant::DICTIONARY, "characters", godot::PROPERTY_HINT_DICTIONARY_TYPE, "StringName;ActorResource"), "set_characters", "get_characters");
	}


	public:
	TypedDictionary<StringName, ActorResource> characters;

};
