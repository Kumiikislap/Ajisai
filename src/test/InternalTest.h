#pragma once


#include "godot_cpp/core/print_string.hpp"
#include "godot_cpp/variant/color.hpp"
namespace godot {
	class Color;
};

using namespace godot;

namespace ajisai 
{
	class InternalTest
	{
		public:
		InternalTest() {
			godot::print_line("From Internal!");
		}
		~InternalTest() = default;
		godot::Color a;
	};
};
