#pragma once
class CollisionBox
{
private:
	float leftX, rightX, topY, bottomY, width, height;
	float xPos, yPos;
	bool walkingLeft = false;
public:
	CollisionBox();
	CollisionBox(float _x, float _y, float _width, float _height);

	void draw();
	void draw(float x, float y);
	void drawCollisionLine(float x, float y, float r, float g, float b);
	void setWalkingLeft(bool walk);

	float getLeftX();
	float getRightX();
	float getTopY();
	float getBotY();


	bool getWalkingLeft();
};

inline void CollisionBox::setWalkingLeft(bool left) {
	this->walkingLeft = left;
}




inline bool CollisionBox::getWalkingLeft() {
	return this->walkingLeft;
}

inline float CollisionBox::getLeftX() {
	return this->leftX;
}

inline float CollisionBox::getRightX() {
	return this->rightX;
}

inline float CollisionBox::getTopY() {
	return this->topY;
}

inline float CollisionBox::getBotY() {
	return this->bottomY;
}