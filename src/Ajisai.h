#pragma once

#include <godot_cpp/classes/node.hpp>
#include "features/movie/CharactersResource.h"
#include "features/movie/SceneMenu.h"
#include "godot_cpp/classes/ref.hpp"
#include "godot_cpp/classes/wrapped.hpp"



/* The root context
 *
 * I know it's a confusing name
 *
 */
class SceneMenu;

using namespace godot;

class Ajisai : public Node
{
	GDCLASS(Ajisai, Node)

	Ajisai();
	~Ajisai() = default;

	static void _bind_methods();

public:
	void _ready() override;

	void _exit_tree() override;
	void _notification(int notification);
	void build_services();

	void bind_services();

	void set_cast(const Ref<CharactersResource> p_cast);
	Ref<CharactersResource> get_cast() const;

private:
	// services: sfx, music, vfx , 
	// contexts: title, scene, settings , 
	// game states: saves, settings saves, 
	SceneMenu* scene_menu { nullptr };

	// Resources - bgs, audio, characters, sprite items
	Ref<CharactersResource> cast;

};
