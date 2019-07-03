#pragma once

//#include <windows.h>		// Header file for Windows
////#include <iostream>
//#include <gl\glu.h>			// Header file for the GLu32 Library
//#include <gl\gl.h>			// Header file for the OpenGL32 Library
//#include "Header.h"


class Platform {
private:
	float screenX;
	float screenY;
	float floorX = 100;
	float floorY = 85;
	float slowness = 0.0;
	float x = 0.0, y = 0.0;
	float width = 700.0, height = 8.0;
	float leftX = x, bottomY = y, rightX = x+width, topY = y+height;
	float rightSpeed = 220.0f;
	float leftSpeed = 220.0f;

public:
	GLuint platform_texture = 0;
	void drawPlatform();
	void moveLeft(float delta);
	void moveRight(float delta);
	void setX(float x);
	void setY(float y);
	void setSlowness(float slow);
	float getX(void);
	float getY(void);
};

inline void Platform::moveRight(float delta)
{
	screenX = screenX - (rightSpeed * delta);
}

inline void Platform::moveLeft(float delta)
{
	screenX = screenX + (leftSpeed * delta);
}

inline float Platform::getX()
{
	return screenX;
}

inline float Platform::getY()
{
	return screenY;
}

inline void Platform::setX(float x)
{
	screenX = x;
}

inline void Platform::setY(float y)
{
	screenY = y;
}

inline void Platform::setSlowness(float slow) {
	this->slowness = slow;
}
