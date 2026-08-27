#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/classes/window.hpp>
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/script.hpp>

#include "features/movie/CharactersResource.h"
#include "godot_cpp/classes/node.hpp"
#include "godot_cpp/classes/ref.hpp"
#include "godot_cpp/classes/resource.hpp"
#include "util/conversions.hpp"
#include "godot_cpp/classes/ref.hpp"
#include <godot_cpp/classes/tween.hpp>
#include <godot_cpp/variant/node_path.hpp>
#include <godot_cpp/variant/vector2.hpp>
#include <godot_cpp/classes/property_tweener.hpp>

#include "main.h"

Main::Main()
{
}

//void Main::_bind_methods()
//{
//}

void Main::_ready()
{
	
	//MainLoop *main_loop = Engine::get_singleton()->get_main_loop();
	//SceneTree *scene_tree = rl::gdcast<SceneTree>(main_loop);

	//Window* root = scene_tree->get_root();
	//Node* dialogue = root->get_node<Node>("DialogueManager");
    UtilityFunctions::print(yuri);
	
	// call a function in gdscript
	Ref<Script> script = ResourceLoader::get_singleton()->load("res://addons/dialogue_manager/dialogue_manager.gd");
	Object *obj = ClassDB::instantiate(script->get_instance_base_type());
	obj->set_script(script);
	obj->call("show_dialogue_balloon", this->dialogue_resource, "start");
	//Variant ret = obj->call("show_dialogue_balloon", this->dialogue_resource, "start");
	//GDExtensionInt ret_int = ret;

    UtilityFunctions::print(dialogue_resource);

	
	//tween->play();
}
void Main::print_test()
{
	UtilityFunctions::print("works");
}

void Main::set_dialogue_resource(Ref<Resource> p_resource)
{
	this->dialogue_resource = p_resource;
}

Ref<Resource> Main::get_dialogue_resource() const
{
	return dialogue_resource;
}

void Main::set_dialogue_var(const int& p_var)
{
	this->dialogue_var;
}

int Main::get_dialogue_var() const
{
	return dialogue_var;
}

void Main::set_cast(const Ref<CharactersResource> p_cast)
{
	cast = p_cast;
}

Ref<CharactersResource> Main::get_cast() const
{
	return cast;
}
