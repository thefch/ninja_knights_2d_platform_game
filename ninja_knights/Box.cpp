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

void Box::draw(float texMapX, float texMapY,float xtranslate,float ytranslate)
{
	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, platformTexture);
	glEnable(GL_BLEND);	//enable blending
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);	//configure blending
	glColor3f(1.0f, 1.0f, 1.0f);
	glTranslatef(xtranslate, ytranslate, 0.0);
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 0.0); glVertex2d(this->leftX, this->bottomY);
	glTexCoord2f(0.0, texMapY); glVertex2d(this->leftX, this->topY);
	glTexCoord2f(texMapX, texMapY); glVertex2d(this->rightX, this->topY);
	glTexCoord2f(texMapX, 0.0); glVertex2d(this->rightX, this->bottomY);
	glEnd();
	glDisable(GL_BLEND);	//disable blending

	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

//draws the healthBar
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


void Box::drawTrain(float delta)
{
	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D,this->platformTexture);

	if (showTex) {
		glTranslatef(xPos, 0.0, 0.0);
		xPos -= (400.0*delta);
	}
	
	glEnable(GL_BLEND);	//enable blending
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);	//configure blending
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_POLYGON);
		glTexCoord2f(0.0, 0.0); glVertex2d(this->leftX, this->bottomY);
		glTexCoord2f(0.0, 1.0); glVertex2d(this->leftX, this->topY);
		glTexCoord2f(1.0, 1.0); glVertex2d(this->rightX, this->topY);
		glTexCoord2f(1.0, 0.0); glVertex2d(this->rightX, this->bottomY);
	glEnd();
	glDisable(GL_BLEND);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

	//control tex
	if (xPos < -700.0 - width) {
		xPos = 0.0;
		texTimer = 0;
		showTex = false;
	}
	if(!showTex)
		texTimer++;
	
	if (!showTex && (texTimer > 8000)) 
		showTex = true;
	
	//cout << "x: " << xPos << "  timer: " << texTimer << endl;
}


void Box::drawMovingBox() {
	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, platformTexture);
	glEnable(GL_BLEND);	//enable blending
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);	//configure blending
	glTranslatef(xPos,yPos,0.0);
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_POLYGON);
		glTexCoord2f(0.0, 0.0); glVertex2d(this->leftX, this->bottomY);
		glTexCoord2f(0.0, 1.0); glVertex2d(this->leftX, this->topY);
		glTexCoord2f(1.0, 1.0); glVertex2d(this->rightX, this->topY);
		glTexCoord2f(1.0, 0.0); glVertex2d(this->rightX, this->bottomY);
	glEnd();

	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

}

/*
void Box::updateMovingBox(float delta) {

	if (yPos >= 65.0) {
		goDown = true;
	}
	if (goDown) {
		yPos -= (ySpeed*delta);
		if (yPos <= 0) {
			goDown = false;
		}
	}else
		yPos += (ySpeed*delta);
}*/