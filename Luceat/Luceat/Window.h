#pragma once
#include "Vector2.h"
class Window {
public:

	virtual int getWidth() = 0;
	virtual int getHeight() = 0;
	virtual int getResolutionWidth() = 0;
	virtual int getResolutionHeight() = 0;

	virtual void setSize(int width, int height) = 0;
	virtual Vector2 getRenderArea() = 0;
	virtual bool isFullscreen() = 0;
	virtual void setFullscreen(bool val) = 0;
};
