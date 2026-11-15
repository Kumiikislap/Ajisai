#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/classes/script.hpp>

#include "DialogueManagerWrapper.h"
#include "core/rl_constants.hpp"
#include "godot_cpp/core/memory.hpp"
#include "godot_cpp/core/object.hpp"
#include "godot_cpp/variant/callable_method_pointer.hpp"
#include "godot_cpp/variant/dictionary.hpp"
#include "godot_cpp/variant/utility_functions.hpp"
#include "util/bind.hpp"
#include "util/scene.hpp"
#include <godot_cpp/variant/dictionary.hpp>

DialogueManagerWrapper::DialogueManagerWrapper()
{
	// you may want to delete this obj in deconstructor
	Ref<Script> script = rl::resource::loader::get()->load("res://addons/dialogue_manager/dialogue_manager.gd");
	dialogue_manager_object = ClassDB::instantiate(script->get_instance_base_type());
	dialogue_manager_object->set_script(script);
	//rl::gdcast<Node>(dialogue_manager_object);
}

DialogueManagerWrapper::~DialogueManagerWrapper()
{
	memdelete(dialogue_manager_object);
}
void DialogueManagerWrapper::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("connect_mutated", "mutation"), &DialogueManagerWrapper::connect_mutated);
    ClassDB::bind_method(D_METHOD("show_dialogue", "resouce", "title"), &DialogueManagerWrapper::show_dialogue_balloon);
	//rl::utils::signal_binding<DialogueManagerWrapper, rl::event::mutated>::add<Dictionary>();
	ADD_SIGNAL(MethodInfo("mutated",PropertyInfo(Variant::DICTIONARY, "mutation")));
}


void DialogueManagerWrapper::_ready()
{
	dialogue_manager_object->connect("mutated", callable_mp(this, &DialogueManagerWrapper::connect_mutated));
	//rl::signal<rl::event::mutated>::connect<DialogueManagerWrapper>
	//	(this) <=> signal_callback(this, connect_mutated);
}

void DialogueManagerWrapper::connect_mutated(Dictionary mutation)
{
	this->emit_signal(rl::event::mutated, mutation);
	UtilityFunctions::print(mutation);
}

void DialogueManagerWrapper::show_dialogue_balloon(const Ref<Resource>& resource, const StringName title)
{
	dialogue_manager_object->call("show_dialogue_balloon", resource, title);
}

