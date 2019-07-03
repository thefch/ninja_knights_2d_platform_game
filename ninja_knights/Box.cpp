#include "Header.h"

//Box::Box() {}

Box::Box(float _x, float _y, float _width, float _height)
{
		this->leftX = _x;
		this->bottomY = _y;
		this->rightX = _x + _width;
		this->topY = _y + _height;
		this->width = _width;
		this->height = _height;
}

void Box::draw()
{
	glEnable(GL_TEXTURE_2D);
	glPushMatrix();	
	glBindTexture(GL_TEXTURE_2D, platformTexture);
	glEnable(GL_BLEND);	//enable blending
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);	//configure blending
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_POLYGON);
		glTexCoord2f(0.0, 0.0);glVertex2d(this->leftX, this->bottomY);
		glTexCoord2f(0.0, 1.0);glVertex2d(this->leftX, this->topY);
		glTexCoord2f(1.0, 1.0); glVertex2d(this->rightX, this->topY);
		glTexCoord2f(1.0, 0.0); glVertex2d(this->rightX, this->bottomY);
	glEnd();
	
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

void Box::draw(float texMap)
{
	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, platformTexture);
	glEnable(GL_BLEND);	//enable blending
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);	//configure blending
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 0.0); glVertex2d(this->leftX, this->bottomY);
	glTexCoord2f(0.0, 1.0); glVertex2d(this->leftX, this->topY);
	glTexCoord2f(texMap, 1.0); glVertex2d(this->rightX, this->topY);
	glTexCoord2f(texMap, 0.0); glVertex2d(this->rightX, this->bottomY);
	glEnd();
	glDisable(GL_BLEND);	//disable blending

	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

void Box::drawWithTex(GLuint healthBar)
{

	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, healthBar);
	glEnable(GL_BLEND);	//enable blending
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);	//configure blending
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 0.0); glVertex2d(this->leftX, this->bottomY);
	glTexCoord2f(0.0, 1.0); glVertex2d(this->leftX, this->topY);
	glTexCoord2f(1.0, 1.0); glVertex2d(this->rightX, this->topY);
	glTexCoord2f(1.0, 0.0); glVertex2d(this->rightX, this->bottomY);
	glEnd();
	glDisable(GL_BLEND);	//disable blending

	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}


void Box::drawLandscape()
{
	glEnable(GL_TEXTURE_2D);
	glPushMatrix();

	if (texTimer % 1000 == 0) {
		showTex = true;
	}else glBindTexture(GL_TEXTURE_2D, landscapeTex[0]);
	if (showTex){
		if (counter % 100==0) {
			glBindTexture(GL_TEXTURE_2D, landscapeTex[0]);
			landscapeCounter++;
			cout << landscapeCounter << endl;
			if (landscapeCounter > 22) {
				landscapeCounter = 0;
				counter = 0;
				showTex = false;
				texTimer = 0;
			}
		}
		counter++;
	}
	texTimer++;
	glEnable(GL_BLEND);	//enable blending
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);	//configure blending
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_POLYGON);
		glTexCoord2f(0.0, 0.0); glVertex2d(this->leftX, this->bottomY);
		glTexCoord2f(0.0, 1.0); glVertex2d(this->leftX, this->topY);
		glTexCoord2f(5.0, 1.0); glVertex2d(this->rightX, this->topY);
		glTexCoord2f(5.0, 0.0); glVertex2d(this->rightX, this->bottomY);
	glEnd();
	glDisable(GL_BLEND);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

}