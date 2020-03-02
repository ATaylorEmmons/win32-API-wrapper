#include "Win32Base.h"

Win32Base::Win32Base(std::string title, int width, int height)
{
	this->m_Title = title;
	this->m_Width = width;
	this->m_Height = height;
	this->m_IsFullscreen = false;

}

void Win32Base::init(LoopCommand* loop)
{
	const char g_szClassName[] = "LuceatWin32WindowClass";
	m_hInstance = GetModuleHandle(NULL);
	WNDCLASSEX wc;


	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = 0;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = m_hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = g_szClassName;
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, "Window Registration Failed!", "Error!",
			MB_ICONEXCLAMATION | MB_OK);

	}

	m_hwnd = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		g_szClassName,
		m_Title.c_str(),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, m_Width, m_Height,
		NULL, NULL, m_hInstance, NULL);

	if (m_hwnd == NULL)
	{
		MessageBox(NULL, "Window Creation Failed!", "Error!",
			MB_ICONEXCLAMATION | MB_OK);

	}

	HMONITOR monitor = MonitorFromWindow(m_hwnd, MONITOR_DEFAULTTONEAREST);
	MONITORINFO info;
	info.cbSize = sizeof(MONITORINFO);
	GetMonitorInfo(monitor, &info);
	m_ResolutionWidth = info.rcMonitor.right - info.rcMonitor.left;
	m_ResolutionHeight = info.rcMonitor.bottom - info.rcMonitor.top;

	SetWindowLongPtr(m_hwnd, GWLP_USERDATA, (long)this);
	
	
	this->m_Loop = loop;


}

void Win32Base::start()
{
	MSG msg;
	bool running = true;
	ShowWindow(m_hwnd, SW_SHOW);
	

	while(running)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) //Or use an if statement
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if (msg.message == WM_QUIT) {
			this->m_Loop->exit();
			running = false;
		}
		else {
			this->m_Loop->execute(this, &m_Input);
		}
	}
}

int Win32Base::getResolutionWidth()
{
	return m_ResolutionWidth;
}

int Win32Base::getResolutionHeight()
{
	return m_ResolutionHeight;
}

int Win32Base::getWidth()
{
	if (m_IsFullscreen) {
		return m_ResolutionWidth;
	}
	else {
		return m_Width;
	}
}


int Win32Base::getHeight()
{
	if (m_IsFullscreen) {
		return m_ResolutionHeight;
	}
	else
	{
		return m_Height;
	}
}

void Win32Base::setSize(int width, int height)
{
	m_Width = width;
	m_Height = height;
	SetWindowPos(m_hwnd, 0, 0, 0, width, height, SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER);

}

Vector2 Win32Base::getRenderArea()
{
	RECT temp;
	GetClientRect(m_hwnd, &temp);

	Vector2 ret;
	ret.x = (float)(temp.right - temp.left);
	ret.y = (float)(temp.bottom - temp.top);

	return ret;
}

bool Win32Base::isFullscreen()
{
	return m_IsFullscreen;
}

void Win32Base::setFullscreen(bool val)
{
	DWORD dwStyle = GetWindowLong(m_hwnd, GWL_STYLE);
	if (!m_IsFullscreen) {
		MONITORINFO mi = { sizeof(mi) };
		if (GetWindowPlacement(m_hwnd, &m_fsStruct) && GetMonitorInfo(MonitorFromWindow(m_hwnd, MONITOR_DEFAULTTOPRIMARY), &mi)) {
			SetWindowLong(m_hwnd, GWL_STYLE, dwStyle & ~WS_OVERLAPPEDWINDOW);
			// Dispite sizing the "Client" area of the window to that of the monitor
			//	there is still a 2px border that appears 
			//	this affects the mousing input because it is relative
			//	to the client area but also just looks bad
			// To fix this one sizes the window 4px bigger in either direction and offsets the position by 2
			SetWindowPos(m_hwnd, HWND_TOP, mi.rcMonitor.left - 2, mi.rcMonitor.top - 2, m_ResolutionWidth + 4, m_ResolutionHeight + 4, SWP_NOOWNERZORDER | SWP_FRAMECHANGED);
		}
	}
	else {
		SetWindowLong(m_hwnd, GWL_STYLE, dwStyle | WS_OVERLAPPEDWINDOW);
		SetWindowPlacement(m_hwnd, &m_fsStruct);
		SetWindowPos(m_hwnd, NULL, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_FRAMECHANGED);
	}


	m_IsFullscreen = val;
}

vk::SurfaceKHR* Win32Base::CreateSurface(vk::Instance * instance)
{

	vk::Win32SurfaceCreateInfoKHR info;
	info.hinstance = m_hInstance;
	info.hwnd = m_hwnd;

	m_Surface = &instance->createWin32SurfaceKHR(info, nullptr);
	surfaceCreated = true;

	return m_Surface;
}

Win32Base::~Win32Base()
{
}

LRESULT Win32Base::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	//Get self if it was set "on" the window
	Win32Base* self = reinterpret_cast<Win32Base*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
	if (self) return self->HandleMessage(hwnd, msg, wParam, lParam);
	//Direct the window procedure to the correct window
	return DefWindowProc(hwnd, msg, wParam, lParam);
}

LRESULT Win32Base::HandleMessage(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (m_Input.HideMouse) {
		ShowCursor(false);
	}
	switch (msg)
	{
	case WM_SIZE:
		if (wParam != SIZE_MINIMIZED) {
			m_Width = LOWORD(lParam);
			m_Height = HIWORD(lParam);
		}
		break;
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_BACK:
			m_Input.BackSpace()->setState(true);
			return 0;
		case VK_TAB:
			m_Input.Tab()->setState(true);
			return 0;
		case VK_RETURN:
			m_Input.Enter()->setState(true);
			return 0;
		case VK_CAPITAL:
			m_Input.CapsLock()->setState(true);
			return 0;
		case VK_ESCAPE:
			m_Input.Esc()->setState(true);
			return 0;
		case VK_SPACE:
			m_Input.Space()->setState(true);
			return 0;
		case VK_LEFT:
			m_Input.Left()->setState(true);
			return 0;
		case VK_UP:
			m_Input.Up()->setState(true);
			return 0;
		case VK_RIGHT:
			m_Input.Right()->setState(true);
			return 0;
		case VK_DOWN:
			m_Input.Down()->setState(true);
			return 0;
		case 0x30:
			m_Input.N0()->setState(true);
			return 0;
		case 0x31:
			m_Input.N1()->setState(true);
			return 0;
		case 0x32:
			m_Input.N2()->setState(true);
			return 0;
		case 0x33:
			m_Input.N3()->setState(true);
			return 0;
		case 0x34:
			m_Input.N4()->setState(true);
			return 0;
		case 0x35:
			m_Input.N5()->setState(true);
			return 0;
		case 0x36:
			m_Input.N6()->setState(true);
			return 0;
		case 0x37:
			m_Input.N7()->setState(true);
			return 0;
		case 0x38:
			m_Input.N8()->setState(true);
			return 0;
		case 0x39:
			m_Input.N9()->setState(true);
			return 0;
		case 0x41:
			m_Input.A()->setState(true);
			return 0;
		case 0x42:
			m_Input.B()->setState(true);
			return 0;
		case 0x43:
			m_Input.C()->setState(true);
			return 0;
		case 0x44:
			m_Input.D()->setState(true);
			return 0;
		case 0x45:
			m_Input.E()->setState(true);
			return 0;
		case 0x46:
			m_Input.F()->setState(true);
			return 0;
		case 0x47:
			m_Input.G()->setState(true);
			return 0;
		case 0x48:
			m_Input.H()->setState(true);
			return 0;
		case 0x49:
			m_Input.I()->setState(true);
			return 0;
		case 0x4A:
			m_Input.J()->setState(true);
			return 0;
		case 0x4B:
			m_Input.K()->setState(true);
			return 0;
		case 0x4C:
			m_Input.L()->setState(true);
			return 0;
		case 0x4D:
			m_Input.M()->setState(true);
			return 0;
		case 0x4E:
			m_Input.N()->setState(true);
			return 0;
		case 0x4F:
			m_Input.O()->setState(true);
			return 0;
		case 0x50:
			m_Input.P()->setState(true);
			return 0;
		case 0x51:
			m_Input.Q()->setState(true);
			return 0;
		case 0x52:
			m_Input.R()->setState(true);
			return 0;
		case 0x53:
			m_Input.S()->setState(true);
			return 0;
		case 0x54:
			m_Input.T()->setState(true);
			return 0;
		case 0x55:
			m_Input.U()->setState(true);
			return 0;
		case 0x56:
			m_Input.V()->setState(true);
			return 0;
		case 0x57:
			m_Input.W()->setState(true);
			return 0;
		case 0x58:
			m_Input.X()->setState(true);
			return 0;
		case 0x59:
			m_Input.Y()->setState(true);
			return 0;
		case 0x5A:
			m_Input.Z()->setState(true);
			return 0;
		case VK_NUMPAD0:
			m_Input.Num0()->setState(true);
			return 0;
		case VK_NUMPAD1:
			m_Input.Num1()->setState(true);
			return 0;
		case VK_NUMPAD2:
			m_Input.Num2()->setState(true);
			return 0;
		case VK_NUMPAD3:
			m_Input.Num3()->setState(true);
			return 0;
		case VK_NUMPAD4:
			m_Input.Num4()->setState(true);
			return 0;
		case VK_NUMPAD5:
			m_Input.Num5()->setState(true);
			return 0;
		case VK_NUMPAD6:
			m_Input.Num6()->setState(true);
			return 0;
		case VK_NUMPAD7:
			m_Input.Num7()->setState(true);
			return 0;
		case VK_NUMPAD8:
			m_Input.Num8()->setState(true);
			return 0;
		case VK_NUMPAD9:
			m_Input.Num9()->setState(true);
			return 0;
		case VK_MULTIPLY:
			m_Input.MultiplyKey()->setState(true);
			return 0;
		case VK_ADD:
			m_Input.AddKey()->setState(true);
			return 0;
		case VK_SUBTRACT:
			m_Input.SubtractKey()->setState(true);
			return 0;
		case VK_DECIMAL:
			m_Input.DecimalKey()->setState(true);
			return 0;
		case VK_DIVIDE:
			m_Input.DivideKey()->setState(true);
			return 0;
		case VK_F1:
			m_Input.F1()->setState(true);
			return 0;
		case VK_F2:
			m_Input.F2()->setState(true);
			return 0;
		case VK_F3:
			m_Input.F3()->setState(true);
			return 0;
		case VK_F4:
			m_Input.F4()->setState(true);
			return 0;
		case VK_F5:
			m_Input.F5()->setState(true);
			return 0;
		case VK_F6:
			m_Input.F6()->setState(true);
			return 0;
		case VK_F7:
			m_Input.F7()->setState(true);
			return 0;
		case VK_F8:
			m_Input.F8()->setState(true);
			return 0;
		case VK_F9:
			m_Input.F9()->setState(true);
			return 0;
		case VK_F10:
			m_Input.F10()->setState(true);
			return 0;
		case VK_F11:
			m_Input.F11()->setState(true);
			return 0;
		case VK_F12:
			m_Input.F12()->setState(true);
			return 0;
		case VK_F13:
			m_Input.F13()->setState(true);
			return 0;
		case VK_F14:
			m_Input.F14()->setState(true);
			return 0;
		case VK_F15:
			m_Input.F15()->setState(true);
			return 0;
		case VK_F16:
			m_Input.F16()->setState(true);
			return 0;
		case VK_F17:
			m_Input.F17()->setState(true);
			return 0;
		case VK_F18:
			m_Input.F18()->setState(true);
			return 0;
		case VK_F19:
			m_Input.F19()->setState(true);
			return 0;
		case VK_F20:
			m_Input.F20()->setState(true);
			return 0;
		case VK_F21:
			m_Input.F21()->setState(true);
			return 0;
		case VK_F22:
			m_Input.F22()->setState(true);
			return 0;
		case VK_F23:
			m_Input.F23()->setState(true);
			return 0;
		case VK_F24:
			m_Input.F24()->setState(true);
			return 0;
		case VK_LSHIFT:
			m_Input.LeftShift()->setState(true);
			return 0;
		case VK_RSHIFT:
			m_Input.RightShift()->setState(true);
			return 0;
		case VK_LCONTROL:
			m_Input.LeftControl()->setState(true);
			return 0;
		case VK_RCONTROL:
			m_Input.RightControl()->setState(true);
			return 0;

		}
		break;
	case WM_KEYUP:
		switch (wParam)
		{
		case VK_BACK:
			m_Input.BackSpace()->setState(false);
			return 0;
		case VK_TAB:
			m_Input.Tab()->setState(false);
			return 0;
		case VK_RETURN:
			m_Input.Enter()->setState(false);
			return 0;
		case VK_CAPITAL:
			m_Input.CapsLock()->setState(false);
			return 0;
		case VK_ESCAPE:
			m_Input.Esc()->setState(false);
			return 0;
		case VK_SPACE:
			m_Input.Space()->setState(false);
			return 0;
		case VK_LEFT:
			m_Input.Left()->setState(false);
			return 0;
		case VK_UP:
			m_Input.Up()->setState(false);
			return 0;
		case VK_RIGHT:
			m_Input.Right()->setState(false);
			return 0;
		case VK_DOWN:
			m_Input.Down()->setState(false);
			return 0;
		case 0x30:
			m_Input.N0()->setState(false);
			return 0;
		case 0x31:
			m_Input.N1()->setState(false);
			return 0;
		case 0x32:
			m_Input.N2()->setState(false);
			return 0;
		case 0x33:
			m_Input.N3()->setState(false);
			return 0;
		case 0x34:
			m_Input.N4()->setState(false);
			return 0;
		case 0x35:
			m_Input.N5()->setState(false);
			return 0;
		case 0x36:
			m_Input.N6()->setState(false);
			return 0;
		case 0x37:
			m_Input.N7()->setState(false);
			return 0;
		case 0x38:
			m_Input.N8()->setState(false);
			return 0;
		case 0x39:
			m_Input.N9()->setState(false);
			return 0;
		case 0x41:
			m_Input.A()->setState(false);
			return 0;
		case 0x42:
			m_Input.B()->setState(false);
			return 0;
		case 0x43:
			m_Input.C()->setState(false);
			return 0;
		case 0x44:
			m_Input.D()->setState(false);
			return 0;
		case 0x45:
			m_Input.E()->setState(false);
			return 0;
		case 0x46:
			m_Input.F()->setState(false);
			return 0;
		case 0x47:
			m_Input.G()->setState(false);
			return 0;
		case 0x48:
			m_Input.H()->setState(false);
			return 0;
		case 0x49:
			m_Input.I()->setState(false);
			return 0;
		case 0x4A:
			m_Input.J()->setState(false);
			return 0;
		case 0x4B:
			m_Input.K()->setState(false);
			return 0;
		case 0x4C:
			m_Input.L()->setState(false);
			return 0;
		case 0x4D:
			m_Input.M()->setState(false);
			return 0;
		case 0x4E:
			m_Input.N()->setState(false);
			return 0;
		case 0x4F:
			m_Input.O()->setState(false);
			return 0;
		case 0x50:
			m_Input.P()->setState(false);
			return 0;
		case 0x51:
			m_Input.Q()->setState(false);
			return 0;
		case 0x52:
			m_Input.R()->setState(false);
			return 0;
		case 0x53:
			m_Input.S()->setState(false);
			return 0;
		case 0x54:
			m_Input.T()->setState(false);
			return 0;
		case 0x55:
			m_Input.U()->setState(false);
			return 0;
		case 0x56:
			m_Input.V()->setState(false);
			return 0;
		case 0x57:
			m_Input.W()->setState(false);
			return 0;
		case 0x58:
			m_Input.X()->setState(false);
			return 0;
		case 0x59:
			m_Input.Y()->setState(false);
			return 0;
		case 0x5A:
			m_Input.Z()->setState(false);
			return 0;
		case VK_NUMPAD0:
			m_Input.Num0()->setState(false);
			return 0;
		case VK_NUMPAD1:
			m_Input.Num1()->setState(false);
			return 0;
		case VK_NUMPAD2:
			m_Input.Num2()->setState(false);
			return 0;
		case VK_NUMPAD3:
			m_Input.Num3()->setState(false);
			return 0;
		case VK_NUMPAD4:
			m_Input.Num4()->setState(false);
			return 0;
		case VK_NUMPAD5:
			m_Input.Num5()->setState(false);
			return 0;
		case VK_NUMPAD6:
			m_Input.Num6()->setState(false);
			return 0;
		case VK_NUMPAD7:
			m_Input.Num7()->setState(false);
			return 0;
		case VK_NUMPAD8:
			m_Input.Num8()->setState(false);
			return 0;
		case VK_NUMPAD9:
			m_Input.Num9()->setState(false);
			return 0;
		case VK_MULTIPLY:
			m_Input.MultiplyKey()->setState(false);
			return 0;
		case VK_ADD:
			m_Input.AddKey()->setState(false);
			return 0;
		case VK_SUBTRACT:
			m_Input.SubtractKey()->setState(false);
			return 0;
		case VK_DECIMAL:
			m_Input.DecimalKey()->setState(false);
			return 0;
		case VK_DIVIDE:
			m_Input.DivideKey()->setState(false);
			return 0;
		case VK_F1:
			m_Input.F1()->setState(false);
			return 0;
		case VK_F2:
			m_Input.F2()->setState(false);
			return 0;
		case VK_F3:
			m_Input.F3()->setState(false);
			return 0;
		case VK_F4:
			m_Input.F4()->setState(false);
			return 0;
		case VK_F5:
			m_Input.F5()->setState(false);
			return 0;
		case VK_F6:
			m_Input.F6()->setState(false);
			return 0;
		case VK_F7:
			m_Input.F7()->setState(false);
			return 0;
		case VK_F8:
			m_Input.F8()->setState(false);
			return 0;
		case VK_F9:
			m_Input.F9()->setState(false);
			return 0;
		case VK_F10:
			m_Input.F10()->setState(false);
			return 0;
		case VK_F11:
			m_Input.F11()->setState(false);
			return 0;
		case VK_F12:
			m_Input.F12()->setState(false);
			return 0;
		case VK_F13:
			m_Input.F13()->setState(false);
			return 0;
		case VK_F14:
			m_Input.F14()->setState(false);
			return 0;
		case VK_F15:
			m_Input.F15()->setState(false);
			return 0;
		case VK_F16:
			m_Input.F16()->setState(false);
			return 0;
		case VK_F17:
			m_Input.F17()->setState(false);
			return 0;
		case VK_F18:
			m_Input.F18()->setState(false);
			return 0;
		case VK_F19:
			m_Input.F19()->setState(false);
			return 0;
		case VK_F20:
			m_Input.F20()->setState(false);
			return 0;
		case VK_F21:
			m_Input.F21()->setState(false);
			return 0;
		case VK_F22:
			m_Input.F22()->setState(false);
			return 0;
		case VK_F23:
			m_Input.F23()->setState(false);
			return 0;
		case VK_F24:
			m_Input.F24()->setState(false);
			return 0;
		case VK_LSHIFT:
			m_Input.LeftShift()->setState(false);
			return 0;
		case VK_RSHIFT:
			m_Input.RightShift()->setState(false);
			return 0;
		case VK_LCONTROL:
			m_Input.LeftControl()->setState(false);
			return 0;
		case VK_RCONTROL:
			m_Input.RightControl()->setState(false);
			return 0;

		}
		break;
	case WM_MOUSEMOVE:
	{ //To give this case scope so that the offsetX and Y can be local
		/*

			For some reason the GET_N_LPARAM
			returns values that are incorrect(short of being in fullscreen)
			so I adjust them by the values of 10 and 33.

			The values work in fullscreen however, so the need to be set back
			(minus the +2 to the client area to remove that border)

		*/
		int offsetX = (GET_X_LPARAM(lParam) + 10);
		int offsetY = (GET_Y_LPARAM(lParam) + 33);

		if (m_IsFullscreen) {
			offsetX -= 8;
			offsetY -= 31;
		}

		m_Input.DelMouseX = offsetX - m_Input.MouseX;
		m_Input.DelMouseY = offsetY - m_Input.MouseY;

		if (m_Input.CommandMouse) {
			SetCursorPos(m_Input.MouseX + m_Xpos, m_Input.MouseY + m_Ypos);
		}
		

		m_Input.MouseX = offsetX;
		m_Input.MouseY = offsetY;

		break;
	}
	case WM_LBUTTONDOWN:
		m_Input.LeftMouse()->setState(true);
		break;
	case WM_LBUTTONUP:
		m_Input.LeftMouse()->setState(false);
		break;
	case WM_MBUTTONDOWN:
		m_Input.MiddleMouse()->setState(true);
		break;
	case WM_MBUTTONUP:
		m_Input.MiddleMouse()->setState(false);
		break;
	case WM_RBUTTONDOWN:
		m_Input.RightMouse()->setState(true);
		break;
	case WM_RBUTTONUP:
		m_Input.RightMouse()->setState(false);
		break;
	case WM_MOUSEWHEEL:
		m_Input.MouseWheelDelta = GET_WHEEL_DELTA_WPARAM(wParam);
		break;
	case WM_MOVE:
		RECT hold;
		GetWindowRect(m_hwnd, &hold);
		m_Xpos = hold.left;
		m_Ypos = hold.top;
		break;
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}


