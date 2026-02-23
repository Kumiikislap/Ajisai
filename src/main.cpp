#include <godot_cpp/variant/utility_functions.hpp>

#include "main.h"

Main::Main()
{
}

void Main::_bind_methods()
{
}

void Main::_ready()
{
    UtilityFunctions::print(yuri);
    
}
