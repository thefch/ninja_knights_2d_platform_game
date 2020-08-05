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
	float x = 0.0, y = 0.0;
	float width = 700.0, height = 8.0;
	float leftX = x, bottomY = y, rightX = x+width, topY = y+height;
	float rightSpeed = 300.0f;
	float leftSpeed = 300.0f;
	float downSpeed = 50.0f;
	float upSpeed = 50.0f;
	int cooldownRight = 0.0;
	bool direction = false;

public:
	bool dashFinished = false;

	GLuint platform_texture = 0;
	void drawPlatform();
	void updateMeleeLeft(Player p,float delta);
	void updateMeleeRight(Player p, float delta);

	void moveLeft(float delta);
	void moveRight(float delta);
	void moveDown(float delta);
	void moveUp(float delta);
	void setX(float x);
	void setY(float y);

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

inline void Platform::moveDown(float delta) {
	screenY = screenY - (downSpeed * delta);
}

inline void Platform::moveUp(float delta) {
	screenY = screenY + (upSpeed * delta);
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