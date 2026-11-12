#pragma once

#include "godot_cpp/classes/packed_scene.hpp"
#include "godot_cpp/core/class_db.hpp"
#include <godot_cpp/variant/typed_dictionary.hpp>
#include <godot_cpp/variant/string_name.hpp>


using namespace godot;

class CharactersResource : public Resource
{
	GDCLASS(CharactersResource, Resource)
	
	public:
	
	CharactersResource() = default;
	~CharactersResource() = default;

	void set_characters(const TypedDictionary<StringName, PackedScene> p_characters)
	{
		characters = p_characters;
	}

	TypedDictionary<StringName, PackedScene> get_characters() const
	{
		return characters;
	}

	protected:
	static void _bind_methods()
	{
		ClassDB::bind_method(D_METHOD("set_characters", "p_character_expression" ), &CharactersResource::set_characters );
		ClassDB::bind_method(D_METHOD("get_characters"), &CharactersResource::get_characters);
		ADD_PROPERTY(PropertyInfo(Variant::DICTIONARY, "characters", godot::PROPERTY_HINT_DICTIONARY_TYPE, "StringName;PackedScene"), "set_characters", "get_characters");
	}

	private:
	TypedDictionary<StringName, PackedScene> characters;

};
