//#pragma once
#include "Header.h"

class Weapon
{
private:
	float leftX, bottomY, rightX, topY, width, height;
	float xPos = 0.0, yPos = 0.0;
	int currentKunaiPos;
	bool goLeft = false;
	bool destroyKunai = false;
	bool throwing = false;
	bool alive = true;
	
	
public:
	bool canThrow = true;
	Weapon(float _x, float _y, float _width, float _height);
	~Weapon();
	Weapon();

	GLuint weaponTex = 0;
	void draw(bool walkingLeft, float px,float py);
	void drawWeaponCollisionLine(float x, float y, float r, float g, float b);
	void update(float delta, float eu_distance,Enemy *enemy);
	void setTexture(GLuint tex);
	void setThrowing(bool x);
	void setAlive(bool x);

	float getXPoint();
	float getYPoint();
	float getYPos();
	float getXPos();
	bool getDestroyWeapon();
	bool getThrowing();
	bool getAlive();
	int getKunaiPosition();
	
};

inline float Weapon::getYPoint() {
	return bottomY + yPos + height / 2;
}

inline float Weapon::getXPoint() {
	return rightX + xPos;
}

inline bool Weapon::getDestroyWeapon() {
	return this->destroyKunai;
}

inline int Weapon::getKunaiPosition() {
	return this->currentKunaiPos;
}

inline bool Weapon::getThrowing() {
	return this->throwing;
}

inline bool Weapon::getAlive() {
	return this->alive;
}

inline float Weapon::getXPos() {
	return this->xPos;
}

inline float Weapon::getYPos() {
	return this->yPos;
}

inline void Weapon::setTexture(GLuint tex) {
	this->weaponTex = tex;
}

inline void Weapon::setThrowing(bool x) {
	this->throwing = x;
}

inline void Weapon::setAlive(bool x) {
	this->alive = x;
}