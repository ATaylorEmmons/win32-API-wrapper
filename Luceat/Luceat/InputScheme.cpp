#include "InputScheme.h"



InputScheme::InputScheme()
{
	

}


InputScheme::~InputScheme()
{

}

void InputScheme::SetMousePos(int x, int y)
{
	CommandMouse = true;
	MouseX = x;
	MouseY = y;
}

InputState* InputScheme::LeftMouse()
{
	return &m_LeftMouse;
}

InputState* InputScheme::RightMouse()
{
	return &m_RightMouse;
}

InputState* InputScheme::MiddleMouse()
{
	return &m_MiddleMouse;
}

InputState* InputScheme::BackSpace()
{
	return &m_BackSpace;
}

InputState* InputScheme::Tab()
{
	return &m_Tab;
}

InputState* InputScheme::Enter()
{
	return &m_Enter;
}

InputState* InputScheme::CapsLock()
{
	return &m_CapsLock;
}

InputState* InputScheme::Esc()
{
	return &m_Esc;
}

InputState* InputScheme::Space()
{
	return &m_Space;
}

InputState* InputScheme::Left()
{
	return &m_Left;
}

InputState* InputScheme::Up()
{
	return &m_Up;
}

InputState* InputScheme::Right()
{
	return &m_Right;
}

InputState* InputScheme::Down()
{
	return &m_Down;
}

InputState* InputScheme::N0()
{
	return &m_N0;
}

InputState* InputScheme::N1()
{
	return &m_N1;
}

InputState* InputScheme::N2()
{
	return &m_N2;
}

InputState* InputScheme::N3()
{
	return &m_N3;
}

InputState* InputScheme::N4()
{
	return &m_N4;
}

InputState* InputScheme::N5()
{
	return &m_N5;
}

InputState* InputScheme::N6()
{
	return &m_N6;
}

InputState* InputScheme::N7()
{
	return &m_N7;
}

InputState* InputScheme::N8()
{
	return &m_N8;
}

InputState* InputScheme::N9()
{
	return &m_N9;
}

InputState* InputScheme::A()
{
	return &m_A;
}

InputState* InputScheme::B()
{
	return &m_B;
}

InputState* InputScheme::C()
{
	return &m_C;
}

InputState* InputScheme::D()
{
	return &m_D;
}

InputState* InputScheme::E()
{
	return &m_E;
}

InputState* InputScheme::F()
{
	return &m_F;
}

InputState* InputScheme::G()
{
	return &m_G;
}

InputState* InputScheme::H()
{
	return &m_H;
}

InputState* InputScheme::I()
{
	return &m_I;
}

InputState* InputScheme::J()
{
	return &m_J;
}

InputState* InputScheme::K()
{
	return &m_K;
}

InputState* InputScheme::L()
{
	return &m_L;
}

InputState* InputScheme::M()
{
	return &m_M;
}

InputState* InputScheme::N()
{
	return &m_N;
}

InputState* InputScheme::O()
{
	return &m_O;
}

InputState* InputScheme::P()
{
	return &m_P;
}

InputState* InputScheme::Q()
{
	return &m_Q;
}

InputState* InputScheme::R()
{
	return &m_R;
}

InputState* InputScheme::S()
{
	return &m_S;
}

InputState* InputScheme::T()
{
	return &m_T;
}

InputState* InputScheme::U()
{
	return &m_U;
}

InputState* InputScheme::V()
{
	return &m_V;
}

InputState* InputScheme::W()
{
	return &m_W;
}

InputState* InputScheme::X()
{
	return &m_X;
}

InputState* InputScheme::Y()
{
	return &m_Y;
}

InputState* InputScheme::Z()
{
	return &m_Z;
}

InputState* InputScheme::Num0()
{
	return &m_Num0;
}

InputState* InputScheme::Num1()
{
	return &m_Num1;
}

InputState* InputScheme::Num2()
{
	return &m_Num2;
}

InputState* InputScheme::Num3()
{
	return &m_Num3;
}

InputState* InputScheme::Num4()
{
	return &m_Num4;
}

InputState* InputScheme::Num5()
{
	return &m_Num5;
}

InputState* InputScheme::Num6()
{
	return &m_Num6;
}

InputState* InputScheme::Num7()
{
	return &m_Num7;
}

InputState* InputScheme::Num8()
{
	return &m_Num8;
}

InputState* InputScheme::Num9()
{
	return &m_Num9;
}

InputState* InputScheme::MultiplyKey()
{
	return &m_MultiplyKey;
}

InputState* InputScheme::AddKey()
{
	return &m_AddKey;
}

InputState* InputScheme::SubtractKey()
{
	return &m_SubtractKey;
}

InputState* InputScheme::DecimalKey()
{
	return &m_DecimalKey;
}

InputState* InputScheme::DivideKey()
{
	return &m_DivideKey;
}

InputState* InputScheme::F1()
{
	return &m_F1;
}

InputState* InputScheme::F2()
{
	return &m_F2;
}

InputState* InputScheme::F3()
{
	return &m_F3;
}

InputState* InputScheme::F4()
{
	return &m_F4;
}

InputState* InputScheme::F5()
{
	return &m_F5;
}

InputState* InputScheme::F6()
{
	return &m_F6;
}

InputState* InputScheme::F7()
{
	return &m_F7;
}

InputState* InputScheme::F8()
{
	return &m_F8;
}

InputState* InputScheme::F9()
{
	return &m_F9;
}

InputState* InputScheme::F10()
{
	return &m_F10;
}

InputState* InputScheme::F11()
{
	return &m_F11;
}

InputState* InputScheme::F12()
{
	return &m_F12;
}

InputState* InputScheme::F13()
{
	return &m_F13;
}

InputState* InputScheme::F14()
{
	return &m_F14;
}

InputState* InputScheme::F15()
{
	return &m_F15;
}

InputState* InputScheme::F16()
{
	return &m_F16;
}

InputState* InputScheme::F17()
{
	return &m_F17;
}

InputState* InputScheme::F18()
{
	return &m_F18;
}

InputState* InputScheme::F19()
{
	return &m_F19;
}

InputState* InputScheme::F20()
{
	return &m_F20;
}

InputState* InputScheme::F21()
{
	return &m_F21;
}

InputState* InputScheme::F22()
{
	return &m_F22;
}

InputState* InputScheme::F23()
{
	return &m_F23;
}

InputState* InputScheme::F24()
{
	return &m_F24;
}

InputState* InputScheme::LeftShift()
{
	return &m_LeftShift;
}

InputState* InputScheme::RightShift()
{
	return &m_RightShift;
}

InputState* InputScheme::LeftControl()
{
	return &m_LeftControl;
}

InputState* InputScheme::RightControl()
{
	return &m_RightControl;
}