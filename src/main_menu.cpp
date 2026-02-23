#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/variant/callable.hpp>
#include "main_menu.h"

MainMenu::MainMenu()
{
}

void MainMenu::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("quit_button"), &MainMenu::quit_button);
}

void MainMenu::_ready()
{
    Button* quit = get_node<Button>("CanvasLayer/HBoxContainer/ButtonManager/QuitButton");
    quit -> connect("pressed", callable_mp(this, &MainMenu::quit_button));
}

void MainMenu::quit_button()
{
    get_tree()->quit();
}
