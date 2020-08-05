#include "Header.h"



void Platform::drawPlatform() {
	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, platform_texture);

	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_POLYGON);
		glTexCoord2f(0.0, 0.0); glVertex2d(this->leftX, this->bottomY);
		glTexCoord2f(0.0, 1.0); glVertex2d(this->leftX, this->topY);
		glTexCoord2f(15.0, 1.0); glVertex2d(this->rightX, this->topY);
		glTexCoord2f(15.0, 0.0); glVertex2d(this->rightX, this->bottomY);
	glEnd();

	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}



void Platform::updateMeleeLeft(Player player,float delta) {
	if (player.getAttacking()) {
		screenX += (1000.0f * delta);
	}
	if (screenX >=0.0) {
		screenX = 0;
	}
}

void Platform::updateMeleeRight(Player player, float delta) {
	if (player.getAttacking()) {
		screenX -= (1000.0f*delta);
	}
	if (screenX < -450.0) {
		screenX = -450.0;
	}
}