#include "features/movie/Command.h"
#include "features/movie/Director.h"
#include "godot_cpp/classes/wrapped.hpp"
#pragma 

using namespace godot;

class CommandTest : public Command
{
	GDCLASS(CommandTest, Command)

public:
	CommandTest();
	~CommandTest() = default;
	virtual bool execute() override;
	virtual void undo() override;
	virtual void bind_director(Director* p_director);

protected:
	static void _bind_methods();

	Director* director;
};
