#include "Header.h"


Enemy::Enemy(){}

Enemy::Enemy(float _x, float _y, float _width, float _height)
{
		this->leftX = _x;
		this->bottomY = _y;
		this->rightX = _x + _width;
		this->topY = _y + _height;
		this->width = _width;
		this->height = _height;
		this->col_box = CollisionBox(_x - 2, _y, width + 5, height + 2);
}

Enemy::Enemy(float _x, float _y, float _width, float _height, float _bh1, float _bh2)
{
	this->leftX = _x;
	this->bottomY = _y;
	this->rightX = _x + _width;
	this->topY = _y + _height;
	this->width = _width;
	this->height = _height;
	this->boxFloor1 = _bh1;
	this->boxFloor2 = _bh2;
	this->col_box = CollisionBox(_x - 2, _y, width + 5, height + 2);
}

void Enemy::drawEnemy()
{
	glEnable(GL_TEXTURE_2D);
	if (!attack) {
		attackTextureCounter = 0;
		
		if ((walkTimer % 100) == 0) {
			glBindTexture(GL_TEXTURE_2D, enemyRunTex[walkTextureCounter]);
			walkTextureCounter++;
		}
		else glBindTexture(GL_TEXTURE_2D, enemyRunTex[walkTextureCounter]);
		if (walkTextureCounter > 9) {
			walkTextureCounter = 0;
			walkTimer = 0;
		}
		walkTimer++;
	}
	else if (attack) {
		if ((attackTimer % 50) == 0) {
			glBindTexture(GL_TEXTURE_2D, enemyAttackTex[attackTextureCounter]);
			attackTextureCounter++;
			if (attackTextureCounter > 7) {
				attackFinished = true;
			}
			if (attackTextureCounter > 9) {
				attackTextureCounter = 0;
				attack = false;
				walking = true;
			}
			else {
				attackFinished = false;
			}
		}
		else glBindTexture(GL_TEXTURE_2D, enemyAttackTex[attackTextureCounter]);
		attackTimer++;
	}
	glEnable(GL_BLEND);	//enable blending
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);	//configure blending

	glPushMatrix();
	glTranslatef(xPos, yPos, 0.0);
	glColor3f(1.0f, 1.0f, 1.0f);
	if (walkingLeft) {
		glBegin(GL_POLYGON);
			glTexCoord2f(1.0, 0.0); glVertex2d(this->leftX, this->bottomY);
			glTexCoord2f(1.0, 1.0); glVertex2d(this->leftX, this->topY);
			glTexCoord2f(0.0, 1.0); glVertex2d(this->rightX, this->topY);
			glTexCoord2f(0.0, 0.0); glVertex2d(this->rightX, this->bottomY);
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
	glDisable(GL_BLEND);	//disable blending

	glDisable(GL_TEXTURE_2D);
}

void Enemy::drawEnemyLine(float x, float y, float r, float g, float b)
{
	glPushMatrix();
	glLineWidth(1.0);
	glColor3f(r, g, b);
	glBegin(GL_LINES);
		glVertex2d(this->leftX +(width/2) + xPos,y + height/2);
		glVertex2d(x, y + height / 2);
	glEnd();
	glPopMatrix();
}

void Enemy::drawEnemyLeftLine(float x, float y, float r, float g, float b)
{
	glPushMatrix();
	glLineWidth(1.0);
	glColor3f(r, g, b);
	glBegin(GL_LINES);
		glVertex2d(this->leftX + xPos, getYPoint());
		glVertex2d(x, y);
	glEnd();
	glPopMatrix();
}

void Enemy::drawEnemyRightLine(float x, float y, float r, float g, float b)
{
	glPushMatrix();
	glLineWidth(1.0);
	glColor3f(r, g, b);
	glBegin(GL_LINES);
	glVertex2d(this->rightX + xPos, getYPoint());
	glVertex2d(x, y);
	glEnd();
	glPopMatrix();
}

void Enemy::drawEnemyCollisionLine(float x, float y, float r, float g, float b)
{
	glPushMatrix();
	glLineWidth(1.0);
	glColor3f(r, g, b);
	glBegin(GL_LINES);
		glVertex2d(getXPoint(), getYPoint());
		glVertex2d(x, y);
	glEnd();
	glPopMatrix();
}

void Enemy::drawCollisionBox(float x,float y) {
	this->col_box.draw(x,y);
}

void Enemy::jump(float delta) {
	if (onBox1) {
		jumping = true;
		jumpRight(delta);
	}
	if (onBox2) {
		jumping = true;
		jumpLeft(delta);
	}
	if (onBox3) {
		jumping = true;
		jumpRight(delta);
	}
	if (onBox4) {
		jumping = true;
		jumpLeft(delta);
	}
}

void Enemy::jumpLeft(float delta) {
	float diff = velocity - this->yPos;
	diff = abs(diff);

	if (falling)
	{
		this->yPos -= (280.0f * delta);
		//xPos -= ((xspeed+70.0) * delta);
		xPos -= ((xspeed + fallingSpeed) * delta);
		if (yPos < boxFloor1) {
			falling = false;
			canJump = false;
			finishedJump = true; 
			yPos = boxFloor1;
		}
	}
	else if (jumping) {
		finishedJump = false;
		if (diff <= 5)
		{
			this->yPos += (100.0f*delta);
		}
		else if (diff <= 15.0)
		{
			this->yPos += (250.0f*delta);
		}
		//else this->yPos += 0.5f;
		else this->yPos += (300.0*delta);
		//xPos -= (jumpSpeed * delta);
		xPos -= ((xspeed + jumpSpeed)* delta);

		if ((yPos >= velocity))
		{
			falling = true;
			jumping = false;
		}
		if (this->yPos >= maxHeight)
		{
			this->yPos = maxHeight;
			falling = true;
			jumping = false;
		}
	}
}

void Enemy::jumpRight(float delta) {
	float diff = velocity - this->yPos;
	diff = abs(diff);

	if (falling){
		this->yPos -= (280.0f * delta);
		//xPos +=((xspeed+80.0) * delta);
		xPos += ((xspeed+fallingSpeed) * delta);
		if (yPos < boxFloor2) {
			falling = false;
			canJump = false;
			finishedJump = true;
			yPos = boxFloor2;
		}
	}
	else if (jumping) {
		finishedJump = false;

		if (diff <= 5)
		{
			this->yPos += (100.0f * delta);
		}
		else if (diff <= 15.0)
		{
			this->yPos += (250.0f * delta);
		}
		//else this->yPos += (0.5f * delta);//0.5;
		else this->yPos += 300.0*delta;

		xPos += ((xspeed + jumpSpeed )* delta);
		
		//check for maximum velocity
		if ((yPos >= velocity))
		{
			falling = true;
			jumping = false;
		}

		//check in case of maxHeight
		if (this->yPos >= maxHeight)
		{
			this->yPos = maxHeight;
			falling = true;
			jumping = false;
		}
	}
}


void Enemy::updateEnemyOnPlatform(float distance,float delta) {
	if (alive) {
		//if it reaches the end of the platform , it need to jump
		if (needJump) {
			if (canJump) {
				jump(delta);
			}
		}
		//if it's walking on the platform, check if it reaches the edge of it
		if (walking) {
			if (edgeHit) {
				//check if it will go left or right
				if (goLeft) {
					walkingLeft = true;
					this->col_box.setWalkingLeft(true);
					this->xPos -= (xspeed * delta);
				}
				else if (goRight) {
					walkingLeft = false;
					this->col_box.setWalkingLeft(false);
					this->xPos += (xspeed * delta);
				}
			}
			else this->xPos += (xspeed * delta);
		}
	}

	updateAttack(distance,delta);
}

void Enemy::updateGroundEnemy(float distance,float delta)
{
	//+ right
	//- left
	if (alive) {
		if (this->walking) {
			if (this->leftWallHit) {
				walkingLeft = false;
				this->col_box.setWalkingLeft(false);
				this->xPos += (this->xspeed * delta);
			}
			else if (this->rightWallHit) {
				walkingLeft = true;
				this->xPos -= (this->xspeed * delta);
				this->col_box.setWalkingLeft(true);
			}
			else this->xPos -= (this->xspeed * delta);
		}
	}

	updateAttack(distance,delta);
}

void Enemy::updateAttack(float distance,float delta) {
	if(walkingLeft && distance <= 4.2){
		attack = true;
		walking = false;
		temp_eu = 4.2;
	//	cout << "ATTACK" << endl;
	}
	else if (!walkingLeft && distance < 5.0) {
		attack = true;
		walking = false;
		temp_eu = 5.0;
	}
	else{
		attack = false;
		walking = true;
	}

	if (attackFinished && distance < 5.0) {
		playerAttacked = true;
	}
	else playerAttacked = false; 
}