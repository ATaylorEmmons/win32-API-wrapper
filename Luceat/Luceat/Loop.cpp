#include "Loop.h"

Loop::Loop(){}
Loop::~Loop(){}


void Loop::execute(Window* parent, InputScheme* input)
{
	
	if (input->Esc()->isPressed()) {
		if (!parent->isFullscreen()) {
			parent->setFullscreen(true);
		}
	}

	
}

void Loop::exit()
{
	std::cout << "Window has closed" << std::endl;
}

