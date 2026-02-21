#pragma once

#include <godot_cpp/classes/node.hpp>

class SGlobal : public godot::Node
{
    GDCLASS(SGlobal, godot::Node);

    static inline SGlobal* m_static{ nullptr };

protected:
    static void _bind_methods()
    {
    }

public:
    int data = 11;

    SGlobal()
    {
        m_static = this;
    }

    ~SGlobal()
    {
        m_static = nullptr;
    }

    static inline SGlobal* get_ins()
    {
        return m_static;
    }
};
