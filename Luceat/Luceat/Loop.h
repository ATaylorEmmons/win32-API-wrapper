#pragma once
#include <iostream>

#include "Window.h"
#include "InputScheme.h"
#include "LoopCommand.h"

class Loop : public LoopCommand
{
public:
	Loop();
	~Loop();

	virtual void execute(Window* parent, InputScheme* input);
	virtual void exit();
private:
	
};

