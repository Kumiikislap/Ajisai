#pragma once


#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/object.hpp>
#include "godot_cpp/classes/ref.hpp"
#include "godot_cpp/classes/resource.hpp"
#include "godot_cpp/variant/dictionary.hpp"

#include "godot_cpp/variant/string_name.hpp"
#include "util/bind.hpp"


using namespace godot;

class DialogueManagerWrapper : public  Node
{
	GDCLASS(DialogueManagerWrapper, Node);

	public:
		DialogueManagerWrapper();
		~DialogueManagerWrapper(); 

		virtual void _ready() override;
		static void _bind_methods();

		void show_dialogue_balloon(const Ref<Resource>& resource, const StringName title);
		void connect_mutated(Dictionary mutation);

	private:
		Object* dialogue_manager_object { nullptr };

};


