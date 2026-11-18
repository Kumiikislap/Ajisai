#include <cassert>
#include <memory>
#include "Ajisai.h"
#include "core/AjisaiConstants.h"
#include "features/movie/SceneMenu.h"
#include "features/movie/SceneStates.h"
#include "godot_cpp/classes/node.hpp"
#include "godot_cpp/classes/node2d.hpp"
#include "godot_cpp/classes/object.hpp"
#include "godot_cpp/classes/ref.hpp"
#include "godot_cpp/classes/resource.hpp"
#include "godot_cpp/classes/resource_loader.hpp"
#include "godot_cpp/core/memory.hpp"
#include "godot_cpp/core/print_string.hpp"
#include "godot_cpp/variant/packed_int64_array.hpp"
#include "godot_cpp/variant/typed_array.hpp"
#include "godot_cpp/variant/variant.hpp"
#include "util/conversions.hpp"
#include "util/debug.hpp"
#include <sys/mman.h>

#include <godot_cpp/classes/node3d.hpp>
#include <godot_cpp/classes/compressed_texture2d.hpp>
#include "util/scene.hpp"

Ajisai::Ajisai()
{
}


void Ajisai::_ready()
{
	rl::resource::preload::packed_scene<SceneMenu> scene { ajisai::path::scene::SceneMenu };
	scene_menu = scene.instantiate();
	assert(scene_menu != nullptr);
	add_child(scene_menu);

	pprint(cast);
	bind_services();

}

void Ajisai::_notification(int notification)
{
	switch (notification)
	{
		case Node::NOTIFICATION_READY:
			break;
		case Object::NOTIFICATION_PREDELETE:
			pprint("exited");
			break;
		// calls when close window is pressed
		case Node::NOTIFICATION_WM_CLOSE_REQUEST:
			pprint("exi?");
			break;
	}
}

void Ajisai::_exit_tree()
{
}

void Ajisai::build_services()
{
}

void Ajisai::bind_services()
{
	assert(cast.is_valid());
	scene_menu->director->set_cast(cast);
	scene_menu->director->load_actors();
}

void Ajisai::set_cast(const Ref<CharactersResource> p_cast)
{
	cast = p_cast;
}

Ref<CharactersResource> Ajisai::get_cast() const
{
	return cast;
}

void Ajisai::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("set_cast", "p_cast" ), &Ajisai::set_cast);
	ClassDB::bind_method(D_METHOD("get_cast"), &Ajisai::get_cast);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "cast", godot::PROPERTY_HINT_RESOURCE_TYPE, "CharactersResource"), "set_cast", "get_cast");
}

Ajisai::~Ajisai()
{
	print_line("aj gone");
}
