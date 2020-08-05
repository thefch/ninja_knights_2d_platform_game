#include "Header.h"

Player::~Player() {}

Player::Player() {
	posX = 0;
	posY = 0;

	this->col_box = CollisionBox(x, y, width, height);
	this->healthBar = Box(leftX, topY+2.0, width, 2.0);
	//GLuint weaponTex = loadPNG("Images/ninja/weapon/kunai.png");
	this->kunai = Weapon(x +posX, 20.0, 10.0, 3.0);
}

void Player::drawCharacter() {

	//add a method to pick textures
	glEnable(GL_TEXTURE_2D);
	if (alive) {
		if (gliding) {
			if (glideTimer % 100 == 0) {
				glBindTexture(GL_TEXTURE_2D, charGlideTex[glideTextureCounter]);
				glideTextureCounter++;
			}
			else glBindTexture(GL_TEXTURE_2D, charGlideTex[glideTextureCounter]);
			if (glideTextureCounter > 9) {
				glideTextureCounter = 0;
				glideTimer = 0;
			}
			glideTimer++;

		}
		else if (attacking) {
			dashAttackFinished = false;
			if (attackMeleeTimer % 20 == 0) {
				glBindTexture(GL_TEXTURE_2D, charAttackTex[attackTextureCounter]);
				attackTextureCounter++;
			}
			else glBindTexture(GL_TEXTURE_2D, charAttackTex[attackTextureCounter]);
			if (attackTextureCounter > 9) {
				attackTextureCounter = 0;
				attackMeleeTimer = 0;
				attacking = false;
				dashAttackFinished = true;
			}
			attackMeleeTimer++;
		}
		else if (throwing) {
			if (throwTimer % 30 == 0) {
				glBindTexture(GL_TEXTURE_2D, charThrowTex[throwTextureCounter]);
				throwTextureCounter++;
			}
			else glBindTexture(GL_TEXTURE_2D, charThrowTex[throwTextureCounter]);

			if (throwTextureCounter > 9) {
				throwing = false;
				
				throwTextureCounter = 0;
				throwTimer = 0;
			}
			throwTimer++;
		}
		else if (jumping) {
			glBindTexture(GL_TEXTURE_2D, charJumpTex[0]);
		}
		else if (falling)
		{
			glBindTexture(GL_TEXTURE_2D, charJumpTex[1]);
		}
		else if (walking) {
			//first texture to be added
			if (walkTimer == 0)
				glBindTexture(GL_TEXTURE_2D, charRunTex[0]);
			//switch textures every 50 frames
			else if ((walkTimer % 50) == 0) {
				glBindTexture(GL_TEXTURE_2D, charRunTex[walkTextureCounter]);
				walkTextureCounter++;
			}
			//keep the previoue textures on until it gets to 50 frames
			else glBindTexture(GL_TEXTURE_2D, charRunTex[walkTextureCounter]);

			//resrt the coutners
			if (walkTextureCounter > 9) {
				walkTextureCounter = 0;
				walkTimer = 0;
			}
			walkTimer++;
		}
		//if not walking, put idle texture on
		else if (!walking) {
			if (idleTimer % 100	 == 0) {
				glBindTexture(GL_TEXTURE_2D, charIdle[idleTextureCounter]);
				idleTextureCounter++;
			}
			else glBindTexture(GL_TEXTURE_2D, charIdle[idleTextureCounter]);
			if (idleTextureCounter > 9) {
				idleTextureCounter = 0;
				idleTimer = 0;
			}
			idleTimer++;
		}
	}
	else {
		dead = true;
		if (deadTimer % 200 == 0) {
			glBindTexture(GL_TEXTURE_2D, charDeadTex[deadTextureCounter]);
			deadTextureCounter++;
		}
		else 
			glBindTexture(GL_TEXTURE_2D, charDeadTex[deadTextureCounter]);
		
		if (deadTextureCounter > 9) {
			deadTextureCounter = 9;
		//	deadTimer = 0;
		}
		deadTimer++;
	}

	glPushMatrix();
	glEnable(GL_BLEND);	//enable blending
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);	//configure blending
	glColor3f(1.0f, 1.0f, 1.0f);
	float Xtemp = 0.0;
	float Ytemp = 0.0;
	if (dead) {
		Xtemp = 1.0;
		Ytemp = 5.0;
	}
	if (attacking) {
		Xtemp = 5.0;
	}
	if (walkingLeft) 
	//left walking
	{
		glBegin(GL_QUADS);
			glTexCoord2f(1.0, 1.0); glVertex2d(this->leftX-Xtemp, this->topY);
			glTexCoord2f(1.0, 0.0); glVertex2d(this->leftX-Xtemp, this->bottomY);
			glTexCoord2f(0.0, 0.0); glVertex2d(this->rightX, this->bottomY);
			glTexCoord2f(0.0, 1.0); glVertex2d(this->rightX, this->topY);
		glEnd();
	}
	else
	//right walking
	{
		glBegin(GL_QUADS);
			glTexCoord2f(0.0, 1.0); glVertex2d(this->leftX, this->topY-Ytemp);
			glTexCoord2f(0.0, 0.0); glVertex2d(this->leftX, this->bottomY-Ytemp);
			glTexCoord2f(1.0, 0.0); glVertex2d(this->rightX+Xtemp, this->bottomY-Ytemp);
			glTexCoord2f(1.0, 1.0); glVertex2d(this->rightX+Xtemp, this->topY-Ytemp);
		glEnd();
	}
	glDisable(GL_BLEND);

	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

	drawHealthBar();
}

void Player::drawHealthBar() {
	healthBar.drawWithTex(healthBarTex[healthBarCounter]);
}

void Player::drawCollisionBox() {
	this->col_box.draw();
}

void Player::drawWeapon(bool kunaiDirection,float px,float py,float delta,vector<Enemy*> enemies,vector<Enemy*> enemiesAI) {

	for (int i = 0; i < magazine.size(); i++) {
		if (!throwing && (magazineCounter < maxKunai)) {
			//draw the kunai
			magazine.at(i).draw(kunaiDirection, px, py);
			bool destroyed = true;

			float tempAI = 10000.0;
			int indexAI = 100;
			if (enemiesKilled > 4) {
				for (int k = 0; k < enemiesAI.size(); k++) {
					if (enemiesAI[k]->getAlive()) {
						float eu_distanceAI = sqrt(pow((enemiesAI[k]->getXPoint() - magazine.at(i).getXPoint() - px), 2) + pow((enemiesAI[k]->getYPoint() - magazine.at(i).getYPoint() - (py * 2)), 2));
						if (tempAI > eu_distanceAI) {
							tempAI = eu_distanceAI;
							indexAI = k;
						}
					}
				}
			}
			float tempBasic = 110000.0;
			int indexBasic = 100;
			for (int j = 0; j < enemies.size(); j++) {
				if (enemies[j]->getAlive()) {
					float eu_distance = sqrt(pow((enemies[j]->getXPoint() - magazine.at(i).getXPoint() - px), 2) + pow((enemies[j]->getYPoint() - magazine.at(i).getYPoint() - (py * 2)), 2));
					if (tempBasic > eu_distance) {
						tempBasic = eu_distance;
						indexBasic = j;
					}
				}
			}
			float temp_eu = 500.0;
			int temp_index = 100;
			if (tempAI < tempBasic) {
				temp_eu = tempAI;
				magazine.at(i).update(delta, temp_eu, enemiesAI[indexAI]);
			}
			else {
				temp_eu = tempBasic;
				magazine.at(i).update(delta, temp_eu, enemies[indexBasic]);
			}


			//destroy nesecarry kunais that are out of range
			if (magazine.at(i).getDestroyWeapon()) {
				destroyed = false;
				magazine.clear();
				if (!enemies.at(i)->getAlive()) {
					//enemiesKilled++;
				}
				//break, beacuse only one enemy can die per kunai
				break;
			}

		}
	}


	/*for (int i = 0; i < magazine.size(); i++){
		if (!throwing && (magazineCounter < maxKunai)) {
			//draw the kunai
			magazine.at(i).draw(kunaiDirection, px, py);
			bool destroyed = true;

			//cout << magazine.at(i).getYPos() << endl;
			for (int j = 0; j < enemies.size(); j++) {
				//only checks the enemies that are still alive
				//to prevent any glitches with throwing kunai form he position of an already dead enemy
				if (enemies.at(j)->getAlive()) {
					//calculates the distance between kunai and enemy
					float eu_distance = sqrt(pow((enemies[j]->getXPoint() - magazine.at(i).getXPoint() - px), 2) + pow((enemies[j]->getYPoint() - magazine.at(i).getYPoint() - (py*2)), 2));

					//update kunais position and status
					magazine.at(i).update(delta, eu_distance, enemies[j]);

					//destroy nesecarry kunais that are out of range
					if (magazine.at(i).getDestroyWeapon()) {
						destroyed = false;
						magazine.clear();
						if (!enemies.at(i)->getAlive()) {
							//enemiesKilled++;
						}
						//break, beacuse only one enemy can die per kunai
						break;
					}
				}
			}
			if(!magazine.at(i).getDestroyWeapon()){
			//if (enemiesKilled> 2 &&  !magazine.at(i).getDestroyWeapon()) {
				for (int k = 0; k < enemiesAI.size(); k++) {
					//only checks the enemies that are still alive
					//to prevent any glitches with throwing kunai form he position of an already dead enemy
					if (enemiesAI.at(k)->getAlive()) {
						//calculates the distance between kunai and enemy
						float eu_distance = sqrt(pow((enemiesAI[k]->getXPoint() - magazine.at(i).getXPoint() - px), 2) + pow((enemiesAI[k]->getYPoint() - magazine.at(i).getYPoint() - (py * 2)), 2));
						//float eu_distance = 10.0;
						//update kunais position and status
						magazine.at(k).update(delta, eu_distance, enemiesAI[k]);

						//destroy nesecarry kunais that are out of range
						if (magazine.at(k).getDestroyWeapon()) {
							magazine.clear();
							if (!enemiesAI.at(k)->getAlive()) {
								//enemiesKilled++;
							}
							//break, beacuse only one enemy can die per kunai
							break;
						}
					}
				}
			}
		}
	}*/
}

void Player::updateWeapon() {
	
}

void Player::ThrowAttack() {

	if (magazine.size() < 1 && magazineCounter<10) {
		magazine.push_back(kunai);
		magazineCounter++;
		//cout << "magazine:"<<magazineCounter << endl;
		fire = true;
		throwing = true;
	}
	//cout<<magazine.size() << endl;

}

//make sure that these values change according to the initial value of the object, not the ortho values
bool Player::checkFloor() {

	//when the character hit the floor, can jump again
	if (posY <= 0) {
		canJump = true;
		return true;
	}
	return false;
}

void Player::jump()
{ 
	
	//checks if the chararacter is able to jump
	if (canJump)
	{
		//jumpTexture = true;
		velocity = 60.0f + posY;	//gives initial velocity
		canJump = false;	//disable the jump key
		jumping = true;
		falling = false;
		//cout << "velocity:  " << velocity << endl;
	}
}

void Player::update(float delta,float platformX,bool jumpPressed,std::vector<Box> boxes)
{
	platformsCollisionUpdate(platformX, jumpPressed, boxes);


	if (gliding) {
		this->posY -= (10.0*delta);
	}

	//time = time + 0.1;	
	float diff = velocity - this->posY;
	diff = abs(diff);

	if (falling)
	{
			this->posY -= (200.0f * delta);//0.55
	}
	else if(jumping){
		canJump = false;
		if (diff <= 5)
		{
			this->posY += (80.0 * delta);//0.2
		}
		else if (diff <= 10.0)
		{
			this->posY += (110.0f * delta);//0.4
		}
		else this->posY += (150.0f * delta);//0.6
		
		//this->posY += (20.0*delta);
		if ((posY >= velocity))
		{
			falling = true;
			jumping = false;
		}
		if (this->posY >= maxHeight)
		{
			this->posY = maxHeight;
			falling = true;
			jumping = false;
		}

	}
	
	if (checkFloor()) {
		setPosition();
		jumping = false;
		canJump = true;	//enable jump key
		falling = false;
	}

	if (!alive) {
		walking = false;
	}
}

void Player::platformsCollisionUpdate(float platformX, bool jumpPressed ,std::vector<Box> boxes) {
	
	if (falling) {
		//check falling collision
		if (checkBoxFalling(platformX,boxes)) {
			if (onBox1) {
				setPosY((boxes[0].getTopY() * scaler) + lround((this->bottomY / 2)*scaler));
			}
			else if (onBox2) {
				setPosY((boxes[1].getTopY() * scaler) + lround((this->bottomY / 2)*scaler) + 1.0);
			}
			else if (onBox3) {
				setPosY((boxes[2].getTopY() * scaler) + lround((this->bottomY / 2)*scaler) + 2.0);
			}
			else if (onBox4) {
				setPosY((boxes[3].getTopY() * scaler) + lround((this->bottomY / 2)*scaler) + 7.0);
			}
			else if (onBox5) {
				setPosY((((boxes[4].getTopY() + boxes[4].getYPos()) * scaler) + lround((this->bottomY / 2)*scaler) + 6.0));
			}
			setOnBox(true);
			setJump(false);	//disable jumping at that time, to prevent any accidental double jumps
			setFalling(false);
			setCanJump(true);
		}
	}
	else if (jumping) {
		//check jumping collision
		if (isOnBox) {
			setFalling(false);
			setCanJump(true);
		}
		else if (checkBoxJumping(platformX,boxes)) {
		
			setFalling(true);
		}
	}

	if (isOnBox) {
		//check on box collision
		if (checkOnBoxUpdate(platformX) && !jumpPressed) {
			setCanJump(true);
			setFalling(true);
			setOnBox(false);
			setWalking(true);
		}
	}
}

bool Player::checkBoxFalling(float platformX,std::vector<Box> boxes) {
	float highBox1 = (boxes[0].getTopY() * scaler);
	float highBox2 = (boxes[1].getTopY() * scaler);
	float highBox3 = (boxes[2].getTopY() * scaler);
	float highBox4 = (boxes[3].getTopY() * scaler);
	float highBox5 = (boxes[4].getTopY() * scaler)+5.0;

	//checks if the character jumped on the FIRST box
	if ((platformX <= -11.5) && (platformX >= -60.0) && ((posY > highBox1) && (posY < highBox1 + 4.0))) {
		setOnBox1(true);
		return true;
	}
	//checks if the character jumped on the SECOND box
	else if ((platformX <= -101.0) && (platformX >= -150.0) && (posY > highBox2) && (posY < highBox2 + 4.0)) {
		setOnBox2(true);
		return true;
	}
	//checks if the character jumped on the THIRD box
	else if ((platformX <= -240.0) && (platformX >= -340.0) && (posY > highBox3) && (posY < highBox3 + 4.0)) {
		setOnBox3(true);
		return true;
	}
	//checks if the character jumped on the FORTH box
	else if ((platformX <= -350.0) && (platformX >= -420.0) && (posY > highBox4) && (posY < highBox4 + 4.0)) {
		setOnBox4(true);
		return true;
	}
	else if ((platformX <= -160.0) && (platformX >= -230.0) && (posY > highBox5) && (posY < highBox5 + 4.0)) {
		setOnBox5(true);
		return true;
	}
	else return false;
}

bool Player::checkBoxJumping(float platformX, std::vector<Box> boxes) {
	//if it jumps and is on a box, dont let it fall
	float lowBox1 = llround((boxes[0].getBottomY() - height) * scaler);
	float lowBox2 = llround((boxes[1].getBottomY() - height) * scaler);
	float lowBox3 = llround((boxes[2].getBottomY() - height) * scaler);
	float lowBox4 = llround((boxes[3].getBottomY() - height) * scaler);
	float lowBox5 = llround((boxes[4].getBottomY() - height) * scaler);

	//character collides with the FIRST box from underneath
	if ((posY >= lowBox1) && (posY <= lowBox1 + 2.0)
		&& (platformX <= -11.5) && (platformX >= -60))
	{
		return true;
	}
	//character collides with the SECOND box from underneath
	else if ((posY >= lowBox2) && (posY <= lowBox2 +2.0)
		&& (platformX < -101.0) && (platformX > -150.0))
	{
		return true;
	}
	//character collides with the THIRD box from underneath
	else if ((posY >= lowBox3) && (posY <= lowBox3 + 2.0)
		&& (platformX < -240.0) && (platformX > -340.0))
	{
		return true;
	}
	//character collides with the THIRD box from underneath
	else if ((posY >= lowBox4 + 5.0) && (posY <= lowBox4 + 7.0)
		&& (platformX < -350.0) && (platformX > -419.0))
	{
		return true;
	}
	else if ((posY >= lowBox5 + 5.0) && (posY <= lowBox5 + 7.0)
		&& (platformX < -160.0) && (platformX > -230.0))
	{
		return true;
	}
	//otherwise it does not collide with any box
	else return false;
}

bool Player::checkOnBoxUpdate(float platformX) {
	if (((platformX >= -11.5) || (platformX <= -60.0)) && onBox1) {
		setOnBox1(false);
		return true;
		//platform.setSlowness(0.1);
	}
	//check when it LEAVES the SECOND without jumping
	else if (((platformX >= -101.0) || (platformX <= -150.0)) && onBox2) {
		setOnBox2(false);
		return true;
		//platform.setSlowness(0.1);
	}
	//check when it LEAVES the THIRD without jumping
	else if (((platformX >= -240.0) || (platformX <= -340.0)) && onBox3) {
		setOnBox3(false);
		return true;
		//platform.setSlowness(0.1);
	}
	else if (((platformX >= -350.0) || (platformX <= -420.0)) && onBox4) {
		setOnBox4(false);
		return true;
	}
	else if (((platformX > -160.0)|| (platformX < -230.0)) && onBox5) {
		setOnBox5(false);
		return true;
	}
	return false;
}

void Player::updateMeleeLeft(float delta) {
	if(this->attacking) {
		this->posX -= (700.0f * delta);
	}

	if (posX < -42.0) {
		posX = -42.0;
	}
}

void Player::updateMeleeRight(float delta) {
	if (this->attacking) {
		this->posX += (700.0f * delta);
	}

	if (posX > 185.0) {
		posX = 185.0;
	}
}

void Player::updateMeleeAttack(bool playerLeftDirection,float pX,float pY,float delta, std::vector<Enemy*> enemies) {
	for (int i = 0; i < enemies.size(); i++) {
		if (attacking) {
			//calculate the distance between the character and the enemy
			float eu_distance = getEU_distance(enemies[i]->getXPoint(), enemies[i]->getYPoint(), pX, pY);
			//cout << eu_distance << endl;
			if (eu_distance < 8.0) {
				enemies.at(i)->setAlive(false);
				//enables the player to dash directly one more time if they want
				oneMoreDash = true;
			}
		}
	}
}

void Player::updateMeleeAttackAI(bool playerLeftDirection, float px, float py, float delta, std::vector<Enemy*> enemiesAI) {
	for (int i = 0; i < enemiesAI.size(); i++) {
		if (attacking) {
			//calculate the distance between the character and the enemy
			float eu_distance = getEU_distance(enemiesAI[i]->getXPoint(), enemiesAI[i]->getYPoint(), px, py);
			//cout << eu_distance << endl;
			if (eu_distance < 8.0) {
				enemiesAI.at(i)->setAlive(false);
				
				//enables the player to dash directly one more time if they want
				oneMoreDash = true;
			}
		}
	}
}