#include "InputState.h"



InputState::InputState()
{
	m_State = false;
}


InputState::~InputState()
{
}

bool InputState::isPressed()
{
	return this->m_State;
}

void InputState::setState(bool state) {	
	this->m_State = state;
}