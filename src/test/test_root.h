#pragma once

#include <godot_cpp/classes/node.hpp>
#include "godot_cpp/classes/wrapped.hpp"
#include "features/movie/Director.h"


using namespace godot;

class TestRoot : public Node
{
	GDCLASS(TestRoot, Node);

public:
	TestRoot();
	~TestRoot() = default;

	void build_services();
	virtual void _ready() override;
	static void _bind_methods(){}
	

private:
	Director* director { nullptr };
	// game_state var
};
