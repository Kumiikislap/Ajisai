#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/classes/script.hpp>

#include "DialogueManagerWrapper.h"
#include "util/scene.hpp"

DialogueManagerWrapper::DialogueManagerWrapper()
{
	Ref<Script> script = rl::resource::loader::get()->load("res://addons/dialogue_manager/dialogue_manager.gd");
	dialogue_manager_object = ClassDB::instantiate(script->get_instance_base_type());
	dialogue_manager_object->set_script(script);
	//rl::gdcast<Node>(dialogue_manager_object);
};

void DialogueManagerWrapper::_ready()
{
}

void DialogueManagerWrapper::show_dialogue_balloon(const Ref<Resource>& resource, const String title)
{
	dialogue_manager_object->call("show_dialogue_balloon", resource, title);
}

