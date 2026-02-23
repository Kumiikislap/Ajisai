#pragma once

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/button.hpp>
#include <godot_cpp/classes/scene_tree.hpp>

using namespace godot;

class MainMenu : public Node
{
    GDCLASS(MainMenu, Node);

public:
    MainMenu();
    ~MainMenu() = default;

    void _ready() override;
    // void _physics_process(double delta) override;
    void quit_button();

protected:
    static void _bind_methods();

private:

};
