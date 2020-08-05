#include "Header.h"


Weapon::~Weapon(){}
Weapon::Weapon(){}


Weapon::Weapon(float _x, float _y, float _width, float _height)
{
	this->leftX = _x;
	this->bottomY = _y;
	this->rightX = _x + _width;
	this->topY = _y + _height;
	this->width = _width;
	this->height = _height;
	//this->weaponTex = tex;
}


void Weapon::draw(bool walkingLeft, float px, float py) {
	float matrix[16];
	nv::Image img2;
	if (img2.loadImageFromFile("Images/ninja/weapon/kunai.png"))
	{

		glGenTextures(1, &weaponTex);
		glBindTexture(GL_TEXTURE_2D, weaponTex);
		glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
		glTexImage2D(GL_TEXTURE_2D, 0, img2.getInternalFormat(), img2.getWidth(), img2.getHeight(), 0, img2.getFormat(), img2.getType(), img2.getLevel(0));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 16.0f);

		setTexture(weaponTex);
	}
	else
		MessageBox(NULL, "Failed to load texture", "End of the world", MB_OK | MB_ICONINFORMATION);

	goLeft = walkingLeft;
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, weaponTex);

	glEnable(GL_BLEND);	//enable blending
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);	//configure blending
	//glTranslatef(px+xPos, yPos, 0.0);
	//this->yPos += py;
	//yPos = py;
	/*glGetFloatv(GL_MODELVIEW_MATRIX, matrix);
	float xnew1 = matrix[0] * 4 + matrix[4] * -4 + matrix[12];
	float ynew1 = matrix[1] * 4 + matrix[5] * -4 + matrix[13];*/
	//cout << ynew1 << endl;
	glTranslatef(xPos + px, yPos + (py*2), 0.0);
	glPushMatrix();
	glColor3f(1.0f, 1.0f, 1.0f);
	if (walkingLeft) {
		glBegin(GL_QUADS);
			glTexCoord2f(1.0, 1.0); glVertex2d(this->leftX, this->topY);
			glTexCoord2f(1.0, 0.0); glVertex2d(this->leftX, this->bottomY);
			glTexCoord2f(0.0, 0.0); glVertex2d(this->rightX, this->bottomY);
			glTexCoord2f(0.0, 1.0); glVertex2d(this->rightX, this->topY);
		glEnd();
	}
	else {
		glBegin(GL_POLYGON);
		glTexCoord2f(0.0, 0.0); glVertex2d(this->leftX, this->bottomY);
		glTexCoord2f(0.0, 1.0); glVertex2d(this->leftX, this->topY);
		glTexCoord2f(1.0, 1.0); glVertex2d(this->rightX, this->topY);
		glTexCoord2f(1.0, 0.0); glVertex2d(this->rightX, this->bottomY);
		glEnd();
	}
	glPopMatrix();
	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
}

void Weapon::update(float delta,float eu_distance,Enemy* enemy) {
	if (goLeft) {
		if (eu_distance < 3.6) {
			enemy->setAlive(false);
			destroyKunai = true;
		}
		else if (xPos > -80) {
			destroyKunai = false;
			xPos -= (300.0 *delta);
		}
		else {
			destroyKunai = true;
		}
	}
	else {
		if (eu_distance < 3.6) {
			enemy->setAlive(false);
			destroyKunai = true;
		}
		else if (xPos < 80.0) {
			destroyKunai = false;
			xPos += (300.0 *delta);
		}
		else {
			destroyKunai = true;
		}
	}
}

void Weapon::drawWeaponCollisionLine(float x, float y, float r, float g, float b)
{
	glColor3f(r, g, b);
	glPushMatrix();
		glBegin(GL_LINES);
			glVertex2f(xPos, yPos);
			glVertex2f(x, y);
		glEnd();
	glPopMatrix();
}