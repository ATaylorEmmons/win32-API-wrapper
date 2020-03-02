#include <iostream>

#define VK_USE_PLATFORM_WIN32_KHR

#include "Vulkan.hpp"

#include <windows.h>
#include <string>

#include "Window.h"
#include "Windowsx.h"

#include "InputScheme.h"
#include "LoopCommand.h"



class Win32Base : public Window {
public:

	Win32Base(std::string name, int width, int height);


	void init(LoopCommand* loop);
	void start();


	virtual int getResolutionWidth();
	virtual int getResolutionHeight();
	virtual int getWidth();
	virtual int getHeight();

	virtual void setSize(int width, int height);

	virtual Vector2 getRenderArea();

	virtual bool isFullscreen();
	virtual void setFullscreen(bool val);

	vk::SurfaceKHR* CreateSurface(vk::Instance* instance);

	~Win32Base();

private:
	Win32Base() {}


	bool surfaceCreated = false;
	vk::SurfaceKHR* m_Surface;
	
	HINSTANCE m_hInstance;
	HWND m_hwnd;

	long m_normalStyle;
	WINDOWPLACEMENT m_fsStruct;

	std::string m_Title;
	int m_Width;
	int m_Height;
	int m_Xpos;
	int m_Ypos;

	int m_ResolutionWidth;
	int m_ResolutionHeight;

	bool m_IsFullscreen;

	static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	LRESULT CALLBACK HandleMessage(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

	LoopCommand* m_Loop;
	InputScheme m_Input;

};
