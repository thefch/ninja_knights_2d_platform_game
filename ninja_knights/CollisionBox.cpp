#include "Header.h"

CollisionBox::CollisionBox() {}

CollisionBox::CollisionBox(float _x, float _y, float _width, float _height)
{
	this->leftX = _x;
	this->bottomY = _y;
	this->rightX = _x + _width;
	this->topY = _y + _height;
	this->width = _width;
	this->height = _height;
}

void CollisionBox::draw()
{
	glPushMatrix();
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_LINE_LOOP);
		glVertex2d(this->leftX, this->bottomY);
		glVertex2d(this->leftX, this->topY);
		glVertex2d(this->rightX, this->topY);
		glVertex2d(this->rightX, this->bottomY);
	glEnd();
	glPopMatrix();
}

void CollisionBox::draw(float x, float y)
{
	glPushMatrix();
	glTranslatef(x, y, 0.0);
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_LINE_LOOP);
		glVertex2d(this->leftX, this->bottomY);
		glVertex2d(this->leftX, this->topY);
		glVertex2d(this->rightX, this->topY);
		glVertex2d(this->rightX, this->bottomY);
	glEnd();

	glPopMatrix();

}


void CollisionBox::drawCollisionLine(float x, float y, float r, float g, float b)
{
	glPushMatrix();
	glLineWidth(1.0);
	glColor3f(r, g, b);
	glBegin(GL_LINES);
		glVertex2d(this->leftX + (width / 2) + x, y + height / 2);
		glVertex2d(x, y + height / 2);
	glEnd();
	glPopMatrix();
}