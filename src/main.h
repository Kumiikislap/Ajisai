#pragma once

#include <godot_cpp/classes/node.hpp>

using namespace godot;

class Main : public Node
{
    GDCLASS(Main, Node);

public:
    Main();
    ~Main() = default;

    void _ready() override;
    // void _physics_process(double delta) override;

protected:
    static void _bind_methods();

private:
    int yuri{ 39 };
};
