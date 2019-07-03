#include "Header.h"
#pragma once
class Box
{
private:
	float leftX, bottomY, rightX, topY, width,height;
	int landscapeCounter = 0;
	int texTimer = 0;
	int counter = 0;
	bool showTex = false;
	//float onPlatformX;
public:
	Box() {};
	Box(float _x, float _y, float _width, float _height);
	//Box::Box(float _x, float _y, float _width, float _height, GLuint texture);

	GLuint platformTexture = 0;
	GLuint landscapeTex[24];
	float getRightX();
	float getBottomY();
	float getLeftX();
	float getTopY();
	float getHeight();
	float getWidth();
	//float getOnPlatformX();

	//void setOnPlatformX(float x);
	void draw();
	void draw(float texMap);
	void drawWithTex(GLuint healthBar);
	void drawLandscape();
};

inline float Box::getHeight() {
	return this->height;
}

inline float Box::getWidth() {
	return this->width;
}

inline float Box::getRightX()
{
	return rightX;
}

inline float Box::getBottomY()
{
	return bottomY;
}

inline float Box::getLeftX()
{
	return leftX;
}

inline float Box::getTopY()
{
	return topY;
}
