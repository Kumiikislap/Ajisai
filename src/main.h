#pragma once

#include <godot_cpp/classes/node.hpp>
#include "features/movie/CharactersResource.h"
#include "godot_cpp/classes/global_constants.hpp"
#include "godot_cpp/classes/ref.hpp"
#include "godot_cpp/classes/resource.hpp"
#include "util/bind.hpp"
#include "core/constants.hpp"

using namespace godot;

class Main : public Node
{
    GDCLASS(Main, Node);

public:
    Main();
    ~Main() = default;

	int dialogue_var{ 40000 };
	int yachiyo { 8000 };

    void _ready() override;
    // void _physics_process(double delta) override;
	void set_dialogue_resource(const Ref<Resource> p_resource);
	void set_dialogue_var(const int& p_var);
	void set_cast(const Ref<CharactersResource> p_cast);

	int get_dialogue_var() const;
	Ref<Resource> get_dialogue_resource() const;
	Ref<CharactersResource>get_cast() const;

	void print_test();

protected:
    static void _bind_methods()
	{
		rl::bind_property(Main, dialogue_resource, Ref<Resource>);
		rl::bind_property(Main, dialogue_var, int);
		ClassDB::bind_method(D_METHOD("set_cast", "p_cast" ), &Main::set_cast);
		ClassDB::bind_method(D_METHOD("get_cast"), &Main::get_cast);
		ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "cast", godot::PROPERTY_HINT_RESOURCE_TYPE, "CharactersResource"), "set_cast", "get_cast");

		rl::bind_member_function(Main,print_test);
	}


private:
    int yuri{ 39 };
	Ref<Resource> dialogue_resource { nullptr };
	Ref<CharactersResource> cast { nullptr };
};
