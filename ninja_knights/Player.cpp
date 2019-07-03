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
		if (jumping) {
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
	float x = 0.0;
	float y = 0.0;
	if (dead) {
		x = 1.0;
		y = 5.0;
	}
	if (walkingLeft) 
	//left walking
	{
		
		glBegin(GL_QUADS);
			glTexCoord2f(1.0, 1.0); glVertex2d(this->leftX+x, this->topY);
			glTexCoord2f(1.0, 0.0); glVertex2d(this->leftX+x, this->bottomY);
			glTexCoord2f(0.0, 0.0); glVertex2d(this->rightX, this->bottomY);
			glTexCoord2f(0.0, 1.0); glVertex2d(this->rightX, this->topY);
		glEnd();
	}
	else
	//right walking
	{
		glBegin(GL_QUADS);
			glTexCoord2f(0.0, 1.0); glVertex2d(this->leftX, this->topY-y);
			glTexCoord2f(0.0, 0.0); glVertex2d(this->leftX, this->bottomY-y);
			glTexCoord2f(1.0, 0.0); glVertex2d(this->rightX+x, this->bottomY-y);
			glTexCoord2f(1.0, 1.0); glVertex2d(this->rightX+x, this->topY-y);
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

void Player::drawWeapon(bool kunaiDirection,float px,float py,float delta,vector<Enemy> enemies) {
	
	for (int i = 0; i < magazine.size(); i++){
		if (magazine.at(i).canThrow) {

			//calculate distance between kunai and enemy
			//cout << eu_distance << endl;
			//set the state of the kunai to throwing
			magazine.at(i).setThrowing(true);
			isThrowing = magazine.at(i).getThrowing();

			//draw the kunai
			magazine.at(i).draw(kunaiDirection, px, py);

			for (int j = 0; j < enemies.size(); j++) {
				//float eu_distance = sqrt(pow((enemies[0].getXPoint() - magazine.at(i).getXPoint() - px), 2) + pow((enemies[0].getYPoint() - magazine.at(i).getYPoint() - py), 2));

				float eu_distance = sqrt(pow((enemies[0].getXPoint() - magazine.at(i).getXPoint() - px), 2) + pow((enemies[0].getYPoint() - magazine.at(i).getYPoint() - py), 2));
				//float eu_distance = sqrt(pow((enemies[j].getXPoint() - magazine.at(i).getXPoint() - px), 2) + pow((enemies[j].getYPoint() - magazine.at(i).getYPoint() - py), 2));
				float eu_distance2 = sqrt(pow((enemies[1].getXPoint() - magazine.at(i).getXPoint() - px), 2) + pow((enemies[1].getYPoint() - magazine.at(i).getYPoint() - py), 2));

				cout <<"distance1: "<< eu_distance << endl;
				//cout << "distance2: " << eu_distance2 << endl;

				//update kuais position and status
				magazine.at(i).update(delta, eu_distance, enemies[j]);

				//if the kunai kills the enemy
				//set the state of the enemy to dead
				if (!magazine.at(i).getAlive()) {
					enemies[j].setAlive(false);

				}
			}
		}
		
		//magazine.at(i).drawWeaponCollisionLine(px, py, enemies[0].getXPoint(), enemies[0].getYPoint(), 1, 1, 0);

		//destroy nesecarry kunais that are out of range
		if (magazine.at(i).getDestroyWeapon()) {
			magazineCounter++;
			//isThrowing = magazine.at(i).getThrowing();
			//magazine.erase(magazine.begin() + i);
			magazine.at(i).canThrow = false;
			canThrow = true;
		}
		else canThrow = false;
	}
}

void Player::updateWeapon() {
	
}

void Player::ThrowAttack() {
	//fire cooldown
	//if (attackTimer % 200 == 0) {
	posInfo = true;
	if (magazine.size() < 20) {
		if (firstThrow) {
			magazine.push_back(kunai);
			fire = true;
			firstThrow = false;
		}
		else {
			magazine.push_back(kunai);
			fire = true;
		}
	}
	cout<<magazine.size() << endl;

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
		velocity = 120.0f + posY;	//gives initial velocity
		canJump = false;	//disable the jump key
		jumping = true;
		falling = false;
		//cout << "velocity:  " << velocity << endl;
	}
}

void Player::update(float delta)
{
	updateWeapon();


	//time = time + 0.1;	
	float diff = velocity - this->posY;
	diff = abs(diff);

	if (falling)
	{
		this->posY -= (310.0f * delta);//0.55
	}
	else if(jumping){
		canJump = false;
		if (diff <= 5)
		{
			this->posY += (200.0 * delta);//0.2
		}
		else if (diff <= 10.0)
		{
			this->posY += (250.0f * delta);//0.4
		}
		else this->posY += (300.0f * delta);//0.6
		
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
		if (checkBoxFalling(platformX)) {
			if (onBox1) {
				setPosY(boxes[0].getBottomY() + 2.0);
			}
			else if (onBox2) {
				setPosY(boxes[1].getBottomY() + 2.0);
			}
			else if (onBox3) {
				setPosY(boxes[2].getBottomY() + 2.0);
			}
			else if (onBox4) {
				setPosY(boxes[3].getBottomY() + 2.0);//+2.0
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


bool Player::checkOnBoxUpdate(float platformX) {
	if (((platformX >= -11.5) || (platformX <= -60.0)) && onBox1){
		setOnBox1(false);
		return true;
		//platform.setSlowness(0.1);
	}
	//check when it LEAVES the SECOND without jumping
	else if (((platformX >= -101.0) || (platformX <= -150.0)) && onBox2){
		setOnBox2(false);
		return true;
		//platform.setSlowness(0.1);
	}
	//check when it LEAVES the THIRD without jumping
	else if (((platformX >= -240.0) || (platformX <= -340.0)) && onBox3){
		setOnBox3(false);
		return true;
		//platform.setSlowness(0.1);
	}
	else if (((platformX >= -350.0) || (platformX <= -420.0)) && onBox4){
		setOnBox4(false);
		return true;
	}
	return false;
}

bool Player::checkBoxFalling(float platformX) {
	//checks if the character jumped on the FIRST box
	if ((platformX <= -11.5) && (platformX >= -60.0) && (posY > 58.0 && (posY < 60.0))){
		setOnBox1(true);
		return true;
	}
	//checks if the character jumped on the SECOND box
	if ((platformX <= -101.0) && (platformX >= -150.0) && (posY > 65.0) && (posY < 70.0)){
		setOnBox2(true);
		return true;
	}
	//checks if the character jumped on the THIRD box
	if ((platformX <= -240.0) && (platformX >= -340.0) && (posY > 74.0) && (posY < 78.0)){
		setOnBox3(true);
		return true;
	}
	//checks if the character jumped on the FORTH box
	if ((platformX <= -350.0) && (platformX >= -420.0) && (posY > 123.0) && (posY < 125.0)) {
		setOnBox4(true);
		return true;
	}
	else return false;
}

bool Player::checkBoxJumping(float platformX, std::vector<Box> boxes) {
	//if it jumps and is on a box, dont let it fall
	
	//character collides with the FIRST box from underneath
	 if ((posY >= boxes[0].getBottomY() - topY) && (posY <= boxes[0].getLeftX()) 
		 && (platformX <= -11.5) && (platformX >= -60))
	 {
		//setPosY(boxes[0].getBottomY() - topY);
		return true;
	 }
	//character collides with the SECOND box from underneath
	 else if ((posY >= boxes[1].getBottomY() - topY) && (posY <= boxes[1].getLeftX())
		 && (platformX < -101.0) && (platformX > -150.0))
	 {
		 //setPosY(boxes[1].getBottomY() - topY);
		 return true;
	 }
	//character collides with the THIRD box from underneath
	 else if ((posY >= boxes[2].getBottomY() - topY) && (posY <= boxes[2].getLeftX())
		 && (platformX < -240.0) && (platformX > -340.0))
	 {
		// setPosY(boxes[2].getBottomY() - topY);
		 return true;
	 }
	//character collides with the FORTH box from underneath
	 else if ((posY >= boxes[3].getBottomY() - topY) && (posY <= boxes[3].getLeftX())
		 && (platformX < -350.0) && (platformX > -419.0))
	 {
		 //setPosY(boxes[3].getBottomY() - topY);
		 return true;
	 }
	 else return false;
}