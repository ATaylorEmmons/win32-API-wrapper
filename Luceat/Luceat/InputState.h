#pragma once

class InputState
{
public:
	InputState();
	~InputState();

	bool isPressed();
	void setState(bool state);
protected:
	bool m_State;
};