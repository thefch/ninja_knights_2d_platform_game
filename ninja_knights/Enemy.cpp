#include "Header.h"


Enemy::Enemy(){}

Enemy::Enemy(float _x, float _y, float _width, float _height)
{
	this->initX = _x;
	this->leftX = _x;
	this->bottomY = _y;
	this->rightX = _x + _width;
	this->topY = _y + _height;
	this->width = _width;
	this->height = _height;
	this->col_box = CollisionBox(_x - 2, _y, width + 5, height + 2);
	//this->healthBar = Box(20.0, 10.0 + 2.0, width, 2.0);
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
	if (alive) {
		if (!attack) {
			attackTextureCounter = 0;

			if ((walkTimer % 80) == 0) {
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
	}
	else {
		if ((deadTimer % 50)== 0) {
			glBindTexture(GL_TEXTURE_2D, enemyDeadTex[deadTextureCounter]);
			deadTextureCounter++;
			if (deadTextureCounter > 9) {
				deadEffect = true;
				deadTextureCounter = 9;
			}
		}else glBindTexture(GL_TEXTURE_2D, enemyDeadTex[deadTextureCounter]);
		deadTimer++;
	}
	glEnable(GL_BLEND);	//enable blending
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);	//configure blending

	glPushMatrix();
	glTranslatef(xPos, yPos, 0.0);
	if (!alive) {
		//rotate the objectwhen die to it show th etexture better
		if(spin%100==0)
			glRotatef(180, spin,0, 0.0	);
		spin += 1;
	}
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

	/*if (xPos > 20.0) {
		spawned = true;
	}*/
}

void Enemy::drawEnemyAI()
{
	glEnable(GL_TEXTURE_2D);
	if (alive) {
		if (!attack) {
			attackTextureCounter = 0;

			if ((walkTimer % 80) == 0) {
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
	}
	else {
		if ((deadTimer % 50) == 0) {
			glBindTexture(GL_TEXTURE_2D, enemyDeadTex[deadTextureCounter]);
			deadTextureCounter++;
			if (deadTextureCounter > 9) {
				deadEffect = true;
				deadTextureCounter = 9;
			}
		}
		else glBindTexture(GL_TEXTURE_2D, enemyDeadTex[deadTextureCounter]);
		deadTimer++;
	}
	glEnable(GL_BLEND);	//enable blending
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);	//configure blending

	glPushMatrix();
	glTranslatef(xPos, yPos, 0.0);
	float tempx = 0.0;
	if (!alive) {
		tempx = 2.0;
		//rotate the objectwhen die to it show th etexture better
		if (spin % 100 == 0)
			glRotatef(180, spin, 0, 0.0);
		spin += 1;
	}
	glColor3f(1.0f, 1.0f, 1.0f);
	if (walkingLeft) {
		glBegin(GL_POLYGON);
		glTexCoord2f(1.0, 0.0); glVertex2d(this->leftX-tempx, this->bottomY);
		glTexCoord2f(1.0, 1.0); glVertex2d(this->leftX-tempx, this->topY);
		glTexCoord2f(0.0, 1.0); glVertex2d(this->rightX, this->topY);
		glTexCoord2f(0.0, 0.0); glVertex2d(this->rightX, this->bottomY);
		glEnd();
	}
	else {
		glBegin(GL_POLYGON);
		glTexCoord2f(0.0, 0.0); glVertex2d(this->leftX, this->bottomY);
		glTexCoord2f(0.0, 1.0); glVertex2d(this->leftX, this->topY);
		glTexCoord2f(1.0, 1.0); glVertex2d(this->rightX+tempx, this->topY);
		glTexCoord2f(1.0, 0.0); glVertex2d(this->rightX+tempx, this->bottomY);
		glEnd();
	}
	glPopMatrix();
	glDisable(GL_BLEND);	//disable blending

	glDisable(GL_TEXTURE_2D);

	if (xPos > 20.0) {
		spawned = true;
	}
	
	//drawHealthBar();
}

void Enemy::drawHealthBar() {
	healthBar.drawWithTex(healthBarTex[healthBarCounter]);
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


void Enemy::updateEnemyOnPlatform(float distance,bool pLeftDirection,float delta) {
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

	updateAttack(distance,pLeftDirection,delta);
}

void Enemy::updateGroundEnemy(float distance,bool pLeftDirection,float delta)
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

	updateAttack(distance,pLeftDirection,delta);
}

void Enemy::updateAttack(float distance,bool pLeftDirection,float delta) {
	//enemy facing left, character facing right
	if(walkingLeft && !pLeftDirection && distance <= 10.0){
		attack = true;
		walking = false;
	}
	//enemy facing right, character facing right
	else if (!walkingLeft && !pLeftDirection && distance < 6.0) {
		attack = true;
		walking = false;
		//temp_eu = 5.0;
	}
	//enemy facing left, character facing left
	else if (walkingLeft && pLeftDirection && distance <= 10.0) {
		attack = true;
		walking = false;
	}
	//enemy facing right, character facing left
	else if (!walkingLeft && pLeftDirection && distance < 6.0) {
		attack = true;
		walking = false;
	}
	else{
		attack = false;
		walking = true;
	}

	//check if the character is within range when the attack finishes
	if (attackFinished && distance <= 12.0) {
		playerAttacked = true;
	}
	else playerAttacked = false; 
}

/*****************************************************************************************/

void Enemy::jumpAILeft(float delta) {
	float diff = velocity - this->yPos;
	diff = abs(diff);

	if (falling){
		this->yPos -= (280.0f * delta);
		//xPos -= ((xspeed+70.0) * delta);
		xPos -= ((xspeed + 40.0) * delta);
		if (yPos < 0.0) {
			jumpPressed = false;
			falling = false;
			canJump = false;
			finishedJump = true;
			yPos = 0.0;
		}
	}
	else if (jumping) {
		finishedJump = false;
		if (diff <= 5)
			this->yPos += (100.0f*delta);
		else if (diff <= 15.0)
			this->yPos += (250.0f*delta);
		else this->yPos += (300.0*delta);

		xPos -= ((xspeed + jumpSpeed)* delta);

		if ((yPos >= velocityAI)){
			falling = true;
			jumping = false;
		}
		if (this->yPos >= maxHeightAI){
			this->yPos = maxHeightAI;
			falling = true;
			jumping = false;
		}
	}
}

void Enemy::jumpAIRight(float delta) {
	float diff = velocity - this->yPos;
	diff = abs(diff);

	if (falling) {
		this->yPos -= (280.0f * delta);
		//xPos +=((xspeed+80.0) * delta);
		xPos += ((xspeed + 40.0) * delta);
		jumpPressed = false;
		if (yPos < 0.0) {
			jumpPressed = false;
			falling = false;
			canJump = false;
			finishedJump = true;
			yPos = 0.0;
		}
	}
	else if (jumping) {
		finishedJump = false;

		if (diff <= 5)
			this->yPos += (100.0f * delta);
		else if (diff <= 15.0)
			this->yPos += (250.0f * delta);
		else this->yPos += 300.0*delta;

		xPos += ((xspeed + 40.0)* delta);

		//check for maximum velocity
		if ((yPos >= velocityAI)){
			falling = true;
			jumping = false;
		}

		//check in case of maxHeight
		if (this->yPos >= maxHeightAI){
			this->yPos = maxHeightAI;
			falling = true;
			jumping = false;
		}
	}
}


void Enemy::jumpAI(float delta) {
	//velocityAI = 60.0+ yPos;
	if (goRight) {
		jumpAIRight(delta);
	}
	else if (goLeft) {
		jumpAILeft(delta);
	}
}

void Enemy::jumpOnPlatformsAI(float jumpPoints[]) {
	//when walking right
	if (getGoRight()) {
		//jump from the gorund to the platform 1 2 3 from right
		if (getXPos() >= jumpPoints[0] - 1 && getXPos() <= jumpPoints[0] + 1.0) {
			setCanJump(true);
			setJump(true);
			setVelocityAI(getYPos() + 80.0);
		}
		else if (getXPos() >= jumpPoints[1] - 1 && getXPos() <= jumpPoints[1] + 1.0) {
			setCanJump(true);
			setJump(true);
			setVelocityAI(getYPos() + 80.0);
		}
		else if (getXPos() >= jumpPoints[3] - 1 && getXPos() <= jumpPoints[3] + 1.0) {
			setCanJump(true);
			setJump(true);
			setVelocityAI(getYPos() + 100.0);
		}
	}
	//jump from the gorund to the platform 1 2 3 from left
	else if (getGoLeft()) {
		if (getXPos() >= jumpPoints[1] - 1 && getXPos() <= jumpPoints[1] + 1.0) {
			setCanJump(true);
			setJump(true);
			setVelocityAI(getYPos() + 80.0);
		}
		else if (getXPos() >= jumpPoints[2] - 1 && getXPos() <= jumpPoints[2] + 1.0) {
			setCanJump(true);
			setJump(true);
			setVelocityAI(getYPos() + 80.0);
		}
		else if (getXPos() >= jumpPoints[4] - 1 && getXPos() <= jumpPoints[4] + 1.0) {
			setCanJump(true);
			setJump(true);
			setVelocityAI(getYPos() + 80.0);
		}
	}
}

void Enemy::jumpOnPlatforms2AI(float jump2Points[], std::vector<Box> boxes,bool pOnBox1,bool pOnBox2,bool pOnBox3,bool pOnBox4,bool pOnBox5) {
	//when going right, jump on platforms
	if (getGoRight()) {
		//when player is on platform 5 and enemy on 2
		if (pOnBox5 && getOnBox2()) {
			if (getXPos() >= jump2Points[0] - 1 && getXPos() <= jump2Points[0] + 1) {
				setCanJump(true);
				setJump(true);
				setJumpPressed(true);
				setVelocityAI(getYPos() + 100.0);
			}
		}
		if (pOnBox3 && getOnBox5()) {
			if (getXPoint() > jump2Points[2] - 1 && getXPos() < boxes[4].getRightX()) {
				setJump(true);
				setCanJump(true);
				setJumpPressed(true);
				setVelocityAI(getYPos() + 60.0);
			}
		}
		if (pOnBox4 && getOnBox3()) {
			if (getXPoint() > jump2Points[4] - 1 && getXPos() < boxes[2].getRightX()) {
				setJump(true);
				setCanJump(true);
				setJumpPressed(true);
				setVelocityAI(getYPos() + 100.0);
			}
		}
	}
	//when going left, jump on platforms
	else if (getGoLeft()) {
		if (pOnBox2 && getOnBox5()) {
			if (getXPoint() > jump2Points[1] - 1 && getXPos() < boxes[4].getLeftX()) {
				setJump(true);
				setCanJump(true);
				setJumpPressed(true);
				setVelocityAI(getYPos() + 80.0);
			}
		}
		if (pOnBox3 && getOnBox4()) {
			if (getXPoint() > jump2Points[5] - 1 && getXPos() < boxes[3].getLeftX()) {
				setJump(true);
				setCanJump(true);
				setJumpPressed(true);
				setVelocityAI(getYPos() + 80.0);
			}
		}
		if (pOnBox5 && getOnBox3()) {
			if (getXPoint() < jump2Points[3] - 1 && getXPos() > boxes[2].getLeftX()) {
				setJump(true);
				setCanJump(true);
				setJumpPressed(true);
				setVelocityAI(getYPos() + 80.0);
			}
		}
	}

}

void Enemy::updateAIEnemy(float distance,float delta,std::vector<Box> boxes,bool pOnBox) {
	if (alive) {
		//if it reaches the end of the platform , it need to jump
		if (canJump || jumpPressed) {
			jumpAI(delta);
		}

		if (walking) {
			if (goRight)
				xPos += (100.0*delta);
			else if (goLeft) xPos -= (100.0*delta);
		}
		if (needJump) {
			if (canJump)
				jumpAI(delta);
		}


		//if within distance attack
		if (distance < 6.0) {
			attack = true;
			walking = false;
		}
		//check if the character is within range when the attack finishes
		if (attackFinished && distance < 6.0) {
			playerAttacked = true;
		}
		else playerAttacked = false;
	}

	platformsCollisionUpdate(boxes,pOnBox);
}

void Enemy::platformsCollisionUpdate(std::vector<Box> boxes,bool pOnBox) {
	if (falling) {
		//checks collision between player player and enemy underneath platforms
		if (checkBoxFalling(boxes)) {
			setOnBox(true);
			setJump(false);	//disable jumping at that time, to prevent any accidental double jumps
			setFalling(false);
			setCanJump(true);
			setJumpPressed(false);
		}
	}
	else if (jumping) {
		if (isOnBox) {
			setFalling(false);
			setCanJump(true);
		}
		else if (checkBoxJumping(boxes)) {
			falling = true;
		}
	}

	if (isOnBox) {
		if (checkOnBoxUpdate(boxes) && !jumpPressed) {
			setCanJump(true);
			setFalling(true);
			setOnBox(false);
			setWalking(true);
		}
	}
	
	if (sideCollisionTimer % 4 == 0)
		previousX = xPos;

	//checks for any collision on the sides of the platforms
	if (jumping || falling) 
		sideCollisionAI(boxes);
	

	sideCollisionTimer++;
}

bool Enemy::checkBoxFalling(std::vector<Box> boxes) {
	float highBox1 = llround(boxes[0].getTopY() - height / 2) + 2.0;
	float highBox2 = llround(boxes[1].getTopY() - height / 2) + 2.0;
	float highBox3 = llround(boxes[2].getTopY() - height / 2) + 2.0;
	float highBox4 = llround(boxes[3].getTopY() - height / 2) + 2.0;
	float highBox5 = llround(boxes[4].getTopY() - height / 2) + 2.0;
	
	//checks if the character jumped on the FIRST box
	if ((xPos >= boxes[0].getLeftX() + width / 2) && (xPos <= boxes[0].getRightX() + width / 2)
		&&((yPos > highBox1) && (yPos < highBox1 + 4.0))) {
		setYPos(highBox1 + 2.0);
		setOnBox1(true);
		return true;
	}
	//checks if the character jumped on the SECOND box
	else if ((xPos >= boxes[1].getLeftX() + width / 2) && (xPos <= boxes[1].getRightX() + width / 2)
		&& (yPos > highBox2) && (yPos < highBox2 + 4.0)) {
		setYPos(highBox2 + 2.0);
		setOnBox2(true);
		return true;
	}
	//checks if the character jumped on the THIRD box
	else if ((xPos >= boxes[2].getLeftX() + width / 2) && (xPos <= boxes[2].getRightX() + width / 2)
		&& (yPos > highBox3) && (yPos < highBox3 + 4.0)) {
		setYPos(highBox3 + 1.0);
		setOnBox3(true);
		return true;
	}
	//checks if the character jumped on the FORTH box
	else if ((xPos >= boxes[3].getLeftX() + width / 2) && (xPos <= boxes[3].getRightX() + width / 2)
		&& (yPos > highBox4) && (yPos < highBox4 + 4.0)) {
		setYPos(highBox4 + 2.0);
		setOnBox4(true);
		return true;
	}
	else if ((xPos >= boxes[4].getLeftX() + width / 2) && (xPos <= boxes[4].getRightX() + width / 2)
		&& (yPos > highBox5) && (yPos < highBox5 + 4.0)) {
		setYPos(highBox5 + 2.0);
		setOnBox5(true);
		return true;
	}
	else return false;
}

bool Enemy::checkBoxJumping(std::vector<Box> boxes) {
	//if it jumps and is on a box, dont let it fall
	float lowBox1 = ((boxes[0].getBottomY())*scaler) - 2;
	float lowBox2 = llround((boxes[1].getBottomY()) * scaler);
	float lowBox3 = llround((boxes[2].getBottomY() + height) * scaler) + 2;
	float lowBox4 = llround((boxes[3].getBottomY() - height)) - 6.0;
	float lowBox5 = llround((boxes[4].getBottomY() ) * scaler);

	//collides with the FIRST box from underneath
	if ((yPos >= lowBox1) && (yPos <= lowBox1 + 2.0)
		&& (xPos >= boxes[0].getLeftX() + width / 2) && (xPos <= boxes[0].getRightX() + width / 2))
	{
		return true;
	}
	//collides with the SECOND box from underneath
	else if ((yPos >= lowBox2) && (yPos <= lowBox2 + 2.0)
		&& (xPos >= boxes[1].getLeftX() + width / 2) && (xPos <= boxes[1].getRightX() + width / 2))
	{
		return true;
	}
	//collides with the THIRD box from underneath
	else if ((yPos >= lowBox3) && (yPos <= lowBox3 + 2.0)
		&& (xPos >= boxes[2].getLeftX() + width / 2) && (xPos <= boxes[2].getRightX() + width / 2))
	{
		return true;
	}
	//collides with the THIRD box from underneath
	else if ((yPos >= lowBox4) && (yPos <= lowBox4 + 2.0)
		&& (xPos >= boxes[3].getLeftX() + width / 2) && (xPos <= boxes[3].getRightX() + width / 2))
	{
		return true;
	}
	//collides with middle = 5th box
	else if ((yPos >= lowBox4) && (yPos <= lowBox4 + 2.0)
		&& (xPos >= boxes[4].getLeftX() + width / 2) && (xPos <= boxes[4].getRightX() + width / 2))
	{
		return true;
	}
	//otherwise it does not collide with any box
	else return false;
}


//checks wheter the enemy elaves the platform
bool Enemy::checkOnBoxUpdate(std::vector<Box> boxes) {
	if (((xPos < boxes[0].getLeftX()) || (xPos > boxes[0].getRightX())) && onBox1) {
		setOnBox1(false);
		return true;
	}
	//check when it LEAVES the SECOND without jumping
	else if (((xPos < boxes[1].getLeftX()) || (xPos > boxes[1].getRightX())) && onBox2) {
		setOnBox2(false);
		return true;
	}
	//check when it LEAVES the THIRD without jumping
	else if (((xPos <boxes[2].getLeftX()) || (xPos > boxes[2].getRightX())) && onBox3) {
		setOnBox3(false);
		return true;
	}
	else if (((xPos < boxes[3].getLeftX()) || (xPos > boxes[3].getRightX())) && onBox4) {
		setOnBox4(false);
		return true;
	}
	else if (((xPos < boxes[4].getLeftX()) || (xPos > boxes[4].getRightX())) && onBox5) {
		setOnBox5(false);
		return true;
	}
	return false;
}


//checks the sides of the platforms for any collision 
void Enemy::sideCollisionAI(std::vector<Box> boxes) {
	//cout << boxes[0].getBottomY() << endl;
	//platform 1
	if (
		yPos > 20.0 &&
		yPos < 45.0 &&
		xPos > boxes[0].getLeftX() + width / 2 &&
		xPos < boxes[0].getRightX() + (width / 2) + 2) {

		setXPos(previousX);
		setFalling(true);
	}

	//platform 2
	if (
		yPos > 30.0 &&
		yPos < 45.0 &&
		xPos > boxes[1].getLeftX() + width / 2 &&
		xPos < boxes[1].getRightX() + width / 2) {

		setXPos(previousX);
		setFalling(true);
	}

	//platform 3
	if (
		yPos > 40.0 &&
		yPos < 65.0 &&
		xPos > boxes[2].getLeftX() + width / 2 &&
		xPos < boxes[2].getRightX() + width / 2) {

		setXPos(previousX);
		setFalling(true);
	}

	//platform 4
	if (
		yPos > 90.0 &&
		yPos < 115.0 &&
		xPos > boxes[3].getLeftX() + width / 2 &&
		xPos < boxes[3].getRightX() + width / 2) {

		setXPos(previousX);
		setFalling(true);
	}

	//platform 5
	if (
		yPos > 80.0 &&
		yPos < 105.0 &&
		xPos > boxes[4].getLeftX() + width / 2 &&
		xPos < boxes[4].getRightX() + width / 2) {

		setXPos(previousX);
		setFalling(true);
	}
}
