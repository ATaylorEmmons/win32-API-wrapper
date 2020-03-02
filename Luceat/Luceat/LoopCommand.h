#pragma once
#include "InputScheme.h"
#include "Window.h"

class LoopCommand
{
public:
	LoopCommand();
	virtual void execute(Window* parent, InputScheme* input) = 0;
	virtual void exit() = 0;
	~LoopCommand();
};
