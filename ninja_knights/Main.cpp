
//includes areas for keyboard control, mouse control, resizing the window
//and draws a spinning rectangle

//#include <windows.h>		// Header file for Windows
//#include <iostream>
//#include <gl\glu.h>			// Header file for the GLu32 Library
//#include <gl\gl.h>			// Header file for the OpenGL32 Library
//
//#include "Player.h"
//#include "Platform.h"
	

#include "Header.h"
#include <ctime>
#include <string>			// used for strings
#include <sstream>			// used for streaming text

int	mouse_x = 0, mouse_y = 0;
int screenWidth = 1280, screenHeight = 720;
int gameTimer = 0;
int counter = 0;
int enemyCounter = 0;
int kunaiAttackTimer = 0;
int attackCounter = 0;
int rightDashTimer = 0;
int leftDashTimer = 0;
int kills = 0;
int temp_kills = 0;
int limit = 0;
int timerGame = 0;


float timer = 0;
float walkTime = 0;
float matrix[16];
float kunaiXPosition = 0.0;
float kunaiYPosition = 0.0;
float meleeXPosition = 0.0;
float meleeYPosition = 0.0;
float xnew1 = 0.0;
float ynew1 = 0.0;
float previousX = 0.0;
float delta;
float previousDistance = 0.0;
float initVelocity = 0.0;

bool LeftPressed = false;
bool keys[256];
bool jumpPressed = false;
bool attacked = false;
bool startWait = false;
bool drawKunai = false;
bool kunaiLeftDirection = false;
bool meleeLeftDirection = false;
bool startFire = false;
bool throwAttack = false;
bool inAttack = false;
bool meleeDirection = false;
bool platformMoved = false;
bool attackLeft = false;
bool attackRight = false;
bool justAttacked = false;
bool previousState = true;
bool setEnemy = false;//for debugging enemy
bool startGame = false;

clock_t previousTicks = 1;
clock_t currentTicks;

//OPENGL FUNCTION PROTOTYPES
void display();				//called in winmain to draw everything to the screen
void reshape(int width, int height);				//called when the window is resized
void init();				//called in winmain when the program starts.
void processKeys();         //called in winmain to process keyboard input
GLuint loadPNG(char* name);
void loadTextures();	//load all the textures from init()
void update();				//called in winmain to update variables
void sideCollision();
float calculateDelta();
void updateEnemies(float delta);
void updateScore();
void updateEnemiesAI();
void updateDashAttack();
void KillGLWindow();
bool wait(); 
GLvoid showKills();
GLvoid showKunais();
GLvoid showHealth();
GLvoid showTimer(int gameTimer);
GLvoid printTimer(); 
GLvoid printKills();

GLvoid glPrint(string fmt);
GLvoid BuildFont(GLvoid);								// Build Our Bitmap Font

Player player;
Platform platform;

Box bg = Box(0.0, 0.0, 400.0,100.0);
Box title = Box(25.0, 70.0, 50.0, 20.0);
Box option1 = Box(10.0, 10.0, 80, 80.0);
Box option2 = Box(10.0, 10.0, 80.0, 80.0);
Box helpScreen = Box(0.0, 0.0, 100.0, 100.0);
Box gameOverScreen = Box(0.0, 0.0, 100.0, 100.0);


Box box1 = Box(70.0, 50.0, 40.0, 10.0);
Box box2 = Box(160.0, 60.0, 40.0, 10.0);
Box box3 = Box(300.0, 70.0, 90.0, 10.0);
Box box4 = Box(410.0, 120.0, 60.0, 10.0);
Box box5 = Box(220.0, 110.0, 60.0, 10.0);
Box leftBar = Box(0.0, 0.0, 5.0, 500.0);
Box rightBar = Box(695.0, 0.0, 5.0, 500.0);
Box sky = Box(0.0, 0.8, 700.0, 380.0);
Box landscape1 = Box(0.0, 8.0-20.0, 700.0, 380.0+20.0);
Box landscape2 = Box(0.0, 30.0-20, 1500.0, 380.0+10);
Box trainBG = Box(0.0, 8.0+30, 1500.0, 380.0+10);
Box train = Box(700.0, 140.0+44, 50.0, 20.0);
vector<Box> boxes;
vector<Enemy*> enemies;
vector<Enemy*> enemiesAI;
Enemy* e1 = new Enemy(500.0, 8.0, 10.0, 20.0);
Enemy *e2 = new Enemy(550.0, 8.0, 10.0, 20.0);
Enemy *e3 = new Enemy(70.0, 60.0, 10.0, 20.0, 0.0, 10.0);
Enemy *e4 = new Enemy(300.0, 80.0, 10.0, 20.0, 0.0, 50.0);
Enemy *e5 = new Enemy(410.0, 130.0, 10.0, 20.0, -50.0, 0.0);

Enemy *eA1 = new Enemy(-10.0, 8.0, 10.0, 25.0);
Enemy *eA2 = new Enemy(-10.0, 8.0, 10.0, 25.0);
Enemy *eA3 = new Enemy(-10.0, 8.0, 10.0, 25.0);
Enemy *eA4 = new Enemy(-10.0, 8.0, 10.0, 25.0);
Enemy *eA5 = new Enemy(-10.0, 8.0, 10.0, 25.0);
Enemy *eA6 = new Enemy(-10.0, 8.0, 10.0, 25.0);
Enemy *eA7 = new Enemy(-10.0, 8.0, 10.0, 25.0);
Enemy *eA8 = new Enemy(-10.0, 8.0, 10.0, 25.0);
Enemy *eA9 = new Enemy(-10.0, 8.0, 10.0, 25.0);
Enemy *eA10 = new Enemy(-10.0, 8.0, 10.0, 25.0);
Enemy *eA11 = new Enemy(-10.0, 8.0, 10.0, 25.0);
Enemy *eA12 = new Enemy(-10.0, 8.0, 10.0, 25.0);
Enemy *eA13 = new Enemy(-10.0, 8.0, 10.0, 25.0);
Enemy *eA14 = new Enemy(-10.0, 8.0, 10.0, 25.0);
Enemy *eA15 = new Enemy(-10.0, 8.0, 10.0, 25.0);
Enemy *eA16 = new Enemy(-10.0, 8.0, 10.0, 25.0);
Enemy *eA17 = new Enemy(-10.0, 8.0, 10.0, 25.0);
Enemy *eA18 = new Enemy(-10.0, 8.0, 10.0, 25.0);
Enemy *eA19 = new Enemy(-10.0, 8.0, 10.0, 25.0);
Enemy *eA20 = new Enemy(-10.0, 8.0, 10.0, 25.0);

bool gameOver = false;
bool mainMenu = true;
bool downPressed = false;
bool upPressed = true;
bool showHelp = false;
float jumpPoints[5] = { 50.0,140.0,230.0,279.0,416.0 };
float jump2Points[6] = { 196.0, 230.0, 275.0, 315.0,380.0, 425.0 };

/*************    START OF OPENGL FUNCTIONS   ****************/
float spin = 0.0;
void display()
{
	//float pCurrentX = -platform.getX() + player.getX() + player.getWidth() + player.getPosX();
	//float pCurrentY = platform.getY() + player.getPosY() + player.getHeight();
	player.setPlayerX(platform.getX());
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer

	glLoadIdentity();

	currentTicks = clock();		//current cpu ticks for delta time
	float deltaTicks = (float)(currentTicks / previousTicks);

	if (mainMenu) {
		gameOver = false;
		glPushMatrix();
			bg.draw(6.0, 1.0, spin, 0.0);
			spin -= 0.001;
			if (spin < -650.0)
				spin = 0;
		glPopMatrix();
		glPushMatrix();
			if (showHelp) {
				helpScreen.draw();
			}
			else {
				if (downPressed)
					option2.draw();
				else if (upPressed)
					option1.draw();
			}
		glPopMatrix();
	}
	else if (startGame) {

		glPushMatrix();
		glScalef(0.4, 0.4, 0);
		glPushMatrix();

		//check for edge of the main platform
		if ((platform.getX() <= 0.0)) {
			glTranslatef(platform.getX(), platform.getY() - player.getPosY(), 0);
		}
		else {
			glTranslatef(0, platform.getY() - player.getPosY(), 0);
		}

		sky.draw(6.0, 1.0, 0.0, 0.0);
		landscape2.draw(6.0, 1.0, platform.getX()*0.3, 0.0);
		train.drawTrain(delta);
		trainBG.draw(6.0, 1.0, platform.getX()*.5, 0.0);
		landscape1.draw(3.0, 1.0, 0.0, 0.0);

		//draw platforms
		for (int i = 0; i < boxes.size(); i++) {
			boxes.at(i).draw();
		}
		//cout << gameTimer << endl;
		platform.drawPlatform();



		if (gameTimer > 1000) {
			if (gameTimer % 700 == 0 && limit < enemiesAI.size()) {
				limit++;
			}

			for (int i = 0; i < limit; i++) {
				if (!enemiesAI[i]->deadEffect)
					enemiesAI[i]->drawEnemyAI();
			}
		}
		cout << enemiesAI[0]->getXPos() << endl;

		//draw enemies
		for (int i = 0; i < enemies.size(); i++) {
			if (!enemies[i]->deadEffect) {
				enemies[i]->drawEnemy();
				//enemies[i]->drawCollisionBox(enemies[i]->getXPos(), enemies[i]->getYPos());
			}
		}
		//enable fire
		if (player.getFire())
			throwAttack = true;

		//throw kunai
		if (throwAttack) {
			//get the latest coordinates for the kunai to spawn when the throw animation end
			if (player.getThrowing()) {
				kunaiLeftDirection = player.getWalkingLeft();
				kunaiXPosition = -platform.getX() + player.getPosX();
				kunaiYPosition = player.getPosY();
			}
			player.drawWeapon(kunaiLeftDirection, kunaiXPosition, kunaiYPosition, delta, enemies, enemiesAI);
		}

		glPopMatrix();

		glPushMatrix();
		glTranslatef(player.getPosX(), platform.getY() + player.getPosY(), 0.0);
			player.drawCharacter();
			//player.drawCollisionBox();
		
		glPopMatrix();


		// Position The Text On The Screen
		glRasterPos2f(220.0, 0.0);
		showKills();	// Print GL Text To The Screen

		glRasterPos2f(0.0, 0.0);
		showKunais();

		glRasterPos2f(110.0, 0.0);
		showTimer(gameTimer);
		glPopMatrix();
		glFlush();

		//calculate the delta time for the animations
		previousTicks = currentTicks;
		delta = deltaTicks / (float)CLOCKS_PER_SEC;

		updateEnemiesAI();

		//update enemies
		if (gameTimer > 50 && player.isAlive() && true) {
			updateEnemies(delta);
		}


		if (gameTimer % 4 == 0)
			previousX = platform.getX();

		//update left and right melee attack
		meleeLeftDirection = player.getWalkingLeft();
		meleeXPosition = -platform.getX() + player.getPosX();
		meleeYPosition = player.getPosY();

		player.updateMeleeAttack(meleeLeftDirection, platform.getX(), platform.getY(), delta, enemies);
		player.updateMeleeAttackAI(meleeLeftDirection, platform.getX(), platform.getY(), delta, enemiesAI);
		//cout << "player: " << platform.getX() << "  " << player.getPosY() << endl;

		//side collision of the player with the platforms
		if (player.isJumping() || player.isFalling()) {
			sideCollision();
		}
		//on platform and underneath the platform collisions
		//jump, speed and main platforms collision
		player.update(delta, platform.getX(), jumpPressed, boxes);	//player update

		//set gliding off if hit floor or a platform
		if (player.checkFloor() || player.getOnBox()) {
			player.setGliding(false);
		}

		//takes care of dash attack cooldown 
		updateDashAttack();
		gameTimer++;
		updateScore();


		if (!player.isAlive() || player.getKills() >= 25) {
			startGame = false;
		}
	}
	else if (!startGame) {
	gameOver = true;
	cout << "GAME OVER" << endl;
		glPushMatrix();
			bg.draw(6.0, 1.0, spin, 0.0);
			spin -= 0.001f;
			gameOverScreen.draw();

			glRasterPos2f(55.0, 49.0);
			printTimer();

			glRasterPos2f(60.0, 36.0);
			printKills();
		glPopMatrix();
	}
}
/*******************************END DISPLAY************************************************/

void updateScore() {
	kills = 0 + temp_kills;
	for (int i = 0; i < enemies.size(); i++) {
		if (!enemies[i]->getAlive()) {
			kills++;
		}
	}
	for (int i = 0; i < enemiesAI.size(); i++) {
		if (!enemiesAI[i]->getAlive()) {
			kills++;
		}
	}
	player.setKills(kills);
}

void update(){}

void updateEnemiesAI() {
	
	float tempDistance = 100000.0;

	for (int i = 0; i < enemiesAI.size(); i++) {
		//does not allow the enemy to leave the map
		if (enemiesAI.at(i)->spawned) {
			float left_distance = leftBar.getRightX() + enemiesAI.at(i)->getXPos();
			float right_distance = rightBar.getLeftX() - enemiesAI.at(i)->getXPos();

		//	cout << right_distance << endl;
			if (left_distance < 20.0) {
				enemiesAI.at(i)->setXPos(20.0);
				if (enemiesAI.at(i)->getGoLeft())
					enemiesAI.at(i)->setGoRight(true);
			}
			if (right_distance < 0.0) {
				enemiesAI.at(i)->setXPos(690.0);
				if (enemiesAI.at(i)->getGoRight())
					enemiesAI.at(i)->setGoLeft(true);
			}
		}

		float currentDistance = player.getEU_distance(enemiesAI.at(i)->getXPoint(), enemiesAI.at(i)->getYPoint(), platform.getX(), platform.getY());

		//get the previous Distance every 5 frames
		if (enemyCounter % 5 == 0) {
			previousDistance = player.getEU_distance(enemiesAI.at(i)->getXPoint(), enemiesAI.at(i)->getYPoint(), platform.getX(), platform.getY());
		}

		//enemy getting close
		if (currentDistance <= previousDistance) {

		}
		//player getting further
		else if (currentDistance > previousDistance) {
			if (player.getWalkingLeft()) {
				enemiesAI.at(i)->setGoLeft(true);
			}
			else enemiesAI.at(i)->setGoRight(true);
		}
		//enemy getting further
		else {
			if (enemiesAI.at(i)->getGoLeft()) {
				enemiesAI.at(i)->setGoRight(true);
			}
			else enemiesAI.at(i)->setGoLeft(true);
		}

		//tells the enemy when to jump when player is on platform and enemy notc
		if (player.getOnBox() && !enemiesAI.at(i)->getOnBox()) {
			enemiesAI.at(i)->jumpOnPlatformsAI(jumpPoints);
		}
		//tells enemy to jump on nother platform if its already on one and the player as well
		else if (player.getOnBox() && enemiesAI.at(i)->getOnBox()) {
			enemiesAI.at(i)->jumpOnPlatforms2AI(jump2Points, boxes, player.getOnBox1(), player.getOnBox2(), player.getOnBox3(), player.getOnBox4(), player.getOnBox5());
		}

		//update enemys position, attack
		enemiesAI.at(i)->updateAIEnemy(currentDistance, delta, boxes, player.getOnBox());

		
	}
	//determine if the enemy attacked the player
	//and if they succeded to lose a health bar
	bool playerAttackedAI = false;
	for (int i = 0; i < enemiesAI.size(); i++) {
		if (enemiesAI.at(i)->getPlayerAttacked()) {
			playerAttackedAI = true;
		}
		enemiesAI[i]->setPlayerAttacked(false);					
	}
	if (playerAttackedAI && !startWait) {
		player.decreaseHealth();				
		startWait = true;
	}
	//cooldown
	if (startWait) {
		if (wait()) {
			startWait = false;
		}
	}

	enemyCounter++;

	/*if (player.getKills() > 10) {
		temp_kills = 9;
		for (int i = 0; i < enemiesAI.size(); i++) {
			enemiesAI[i]->setAlive(true);
			enemiesAI[i]->setXPos(enemiesAI[i]->getInitX());
		}
	}*/
}

void updateDashAttack() {
	//if the character kill an enemy, it can dash attack one more time without cooldown
	if (player.getOneMoreDash()) {
		rightDashTimer = 0;
		leftDashTimer = 0;
		player.canDash = true;
		player.setOneMoreDash(false);
	}

	if (!(rightDashTimer <= 0)) {
		rightDashTimer--;
	}
	if (!(leftDashTimer <= 0)) {
		leftDashTimer--;
	}
	//start cooldown for the dash attack
	if (justAttacked) {
		attackCounter++;
		if (attackCounter % 80 == 0) {
			attackCounter = 0;
			rightDashTimer = 300;
			leftDashTimer = 300;
			justAttacked = false;
		}
	}

	float tempDistance = 10000.0;
	for (int i = 0; i < enemies.size(); i++) {
		if (enemies[i]->getAlive()) {
			//stores distance between enemy and player for the dash attack
			float distance = player.getEU_distance(enemies[i]->getXPoint(), enemies[i]->getYPoint(), platform.getX(), platform.getY());
			if (tempDistance > distance) {
				tempDistance = distance;
			}
		}
	}
	
	for (int j = 0; j < enemiesAI.size(); j++) {
		if (enemiesAI[j]->getAlive()) {
			//stores distance between enemy and player for the dash attack
			float distance = player.getEU_distance(enemiesAI[j]->getXPoint(), enemiesAI[j]->getYPoint(), platform.getX(), platform.getY());
			if (tempDistance > distance) {
				tempDistance = distance;
			}
		}
	}


	//enables dashAttack when is nearby enemies
	if (tempDistance < 50.0) {
		player.canDash = true;
	}
	else player.canDash = false;
}

float calculateDelta() {
	currentTicks = clock();
	float deltaTicks = (float)(currentTicks / previousTicks);
	previousTicks = currentTicks;

	float fDeltaTime = deltaTicks / (float) CLOCKS_PER_SEC;
	return fDeltaTime;
}

void updateEnemies(float delta)
{
	
	float left_distanceenemiesE1 = leftBar.getRightX() - enemies[0]->getXPos();
	float right_distanceenemiesE1 = rightBar.getRightX() - enemies[0]->getXPos();
	
	float left_distanceenemiesE2 = leftBar.getRightX() - enemies[1]->getXPos();
	float right_distanceenemiesE2 = rightBar.getLeftX() - enemies[1]->getXPos();
	
	/*******************GROUND EMENIES*************************/
	if (left_distanceenemiesE1 > enemies[0]->getX()) {
		enemies[0]->setLeftWallHit(true);
		enemies[0]->setRightWallHit(false);
	}
	else if (right_distanceenemiesE1 < 515.0) {
		enemies[0]->setLeftWallHit(false);
		enemies[0]->setRightWallHit(true);
	}

	if (left_distanceenemiesE2 >= enemies[1]->getX()){	// > 100.0
		enemies[1]->setLeftWallHit(true);
		enemies[1]->setRightWallHit(false);
	}
	else if (right_distanceenemiesE2 < 560.0) {
		enemies[1]->setLeftWallHit(false);
		enemies[1]->setRightWallHit(true);
	}	

	/*******************PLATFORM EMENIES***********************/
				/**************ENEMY 3******************/
	//jump from the first box to the second
	
	if (enemies[2]->getOnBox1() && enemies[2]->getXPos() > 30.0 && enemies[2]->getXPos() < 80.0) {
		enemies[2]->setNeedJump(true);
		enemies[2]->setCanJump(true);
	}
	//jump from the second box to the first
	if (enemies[2]->getOnBox2() && enemies[2]->getXPos() < 88.0) {
		enemies[2]->setNeedJump(true);
		enemies[2]->setCanJump(true);
	}
	//the enemy will go left when goes to edge of the second box
	if (enemies[2]->getOnBox2() && enemies[2]->getXPos() > 120.0) {
		enemies[2]->setEdgeHit(true);
		enemies[2]->setGoLeft(true);
	}
	//the enemy will go right when goes to edge of the first box
	if (enemies[2]->getOnBox1() && enemies[2]->getXPos() < 0.0) {
		enemies[2]->setEdgeHit(true);
		enemies[2]->setGoRight(true);
	}
	
				
				/**************ENEMY 4******************/
	//jump from the third box to the forth
	if (enemies[3]->getOnBox3() && enemies[3]->getXPos() > 80.0 && enemies[3]->getXPos() < 108.0) {
		enemies[3]->setNeedJump(true);
		enemies[3]->setCanJump(true);
	}
	//jump from the forth box to the third
	if (enemies[3]->getOnBox4() && enemies[3]->getXPos() < 108.0) {
		enemies[3]->setNeedJump(true);
		enemies[3]->setCanJump(true);
	}
	//the enemy will go left when goes to edge of the forth box	
	if (enemies[3]->getOnBox4() && enemies[3]->getXPos() > 160.0) {
		enemies[3]->setEdgeHit(true);
		enemies[3]->setGoLeft(true);
	}
	//the enemy will go right when goes to edge of the third box
	if (enemies[3]->getOnBox3() && enemies[3]->getXPos() < 0.0) {
		enemies[3]->setEdgeHit(true);
		enemies[3]->setGoRight(true);
	}

			/**************ENEMY 5******************/
	//the enemy will go left when goes to edge of the forth box	
	if (enemies[4]->getOnBox4() && enemies[4]->getXPos() > 50.0) {
		enemies[4]->setEdgeHit(true);
		enemies[4]->setGoLeft(true);
	}
	//jump from the forth box to the third
	if (enemies[4]->getOnBox4() && enemies[4]->getXPos() < 0.0) {
		enemies[4]->setNeedJump(true);
		enemies[4]->setCanJump(true);
	}
	//jump from the forth box to the third
	if (enemies[4]->getOnBox3() && enemies[4]->getXPos() < -112.0) {
		enemies[4]->setEdgeHit(true);
		enemies[4]->setGoRight(true);
	}
	//jump from the third box to the forth
	if (enemies[4]->getOnBox3() && enemies[4]->getXPos() > -30.0 && enemies[4]->getXPos() < 0.0) {
		enemies[4]->setNeedJump(true);
		enemies[4]->setCanJump(true);
	}

	/******************************UPDATES********************************/
	float tempDistance = 100000.0;
	for (int i = 0; i < enemies.size(); i++) {
		float distance = player.getEU_distance(enemies[i]->getXPoint(), enemies[i]->getYPoint(), platform.getX(), platform.getY());
		if (enemies.at(i)->getAlive()) {
			if (tempDistance > distance) {
				tempDistance = distance;
			}
		}
		if (i == 0 || i == 1) {
			enemies[i]->updateGroundEnemy(distance, player.getWalkingLeft(), delta);
		}
		else {
			enemies[i]->updateEnemyOnPlatform(distance, player.getWalkingLeft(), delta);
		}
	}
	//enables dash attack when is nearby enemies
/*	if (tempDistance < 50.0) {
		player.canDash = true;
	}
	else player.canDash = false;*/

	bool playerAttacked = false;
	for (int i = 0; i < enemies.size(); i++) {
		if (enemies.at(i)->getPlayerAttacked()) {
			playerAttacked = true;
		}
		enemies[i]->setPlayerAttacked(false);
	}
	if (playerAttacked && !startWait) {
		player.decreaseHealth();
		startWait = true;
	}
	//updates the health bar for any hit and adds a cooldown of 1 sec for the next hit to be taken into account
	/*if ((enemies[0]->getPlayerAttacked() || enemies[1]->getPlayerAttacked() || enemies[2]->getPlayerAttacked() || enemies[3]->getPlayerAttacked() || enemies[4]->getPlayerAttacked()) && !startWait)
	{
		enemies[0]->setPlayerAttacked(false);
		enemies[1]->setPlayerAttacked(false);
		enemies[2]->setPlayerAttacked(false);
		enemies[3]->setPlayerAttacked(false);
		enemies[4]->setPlayerAttacked(false);
		player.decreaseHealth();
		startWait = true;
	}*/
	if (startWait) {
		if (wait()) {
			startWait = false;
		}
	}

	/**********/
	//switch boxes option so it can jump on box2
	if (enemies[2]->getJumpFinished() && enemies[2]->getXPos() > 90.0 && enemies[2]->getXPos() < 120.0) {
		enemies[2]->setOnBox2(true);
	}
	//switch boxes option so it can jump on box1
	if (enemies[2]->getJumpFinished() && enemies[2]->getXPos() >= 0.0 && enemies[2]->getXPos() <= 30.0) {
		enemies[2]->setOnBox1(true);
	}

	//switch boxes option so it can jump on box3
	if (enemies[3]->getJumpFinished() && enemies[3]->getXPos() >= 0.0 && enemies[3]->getXPos() <= 80.0) {
		enemies[3]->setOnBox3(true);
	}
	//switch boxes option so it can jump on box4
	if (enemies[3]->getJumpFinished() && enemies[3]->getXPos() > 108.0 && enemies[3]->getXPos() < 160.0) {
		enemies[3]->setOnBox4(true);
	}

	//switch boxes option so it can jump on box3
	if (enemies[4]->getJumpFinished() && enemies[4]->getXPos() >= 0.0 && enemies[4]->getXPos() <= 50.0) {
		enemies[4]->setOnBox4(true);
	}
	//switch boxes option so it can jump on box4
	if (enemies[4]->getJumpFinished() && enemies[4]->getXPos() < -30.0 && enemies[4]->getXPos() > -112.0) {
		enemies[4]->setOnBox3(true);
	}
}

bool playerIsKilled() {
	if (!player.isAlive()){
		return true;
	}
	return false;
}

bool wait() {
	counter++;
	if (counter > 100) {
		counter = 0;
		return true;
	}
	return false;
}

void reshape(int width, int height)		// Resize the OpenGL window
{
	screenWidth = width; screenHeight = height;           // to ensure the mouse coordinates match 
	glViewport(0, 0, width, height);						// Reset the current viewport
	glMatrixMode(GL_PROJECTION);						// select the projection matrix stack
	glLoadIdentity();									// reset the top of the projection matrix to an identity matrix
	gluOrtho2D(0, 100, 0, 100);           // set the coordinate system for the window

														//	gluOrtho2D(-100,100,-100,100);           // set the coordinate system for the window
	glMatrixMode(GL_MODELVIEW);							// Select the modelview matrix stack
	glLoadIdentity();									// Reset the top of the modelview matrix to an identity matrix
}

void init()
{
	BuildFont();										// Build The Font

	initVelocity = 100.0f;

	enemiesAI.push_back(eA1);
	enemiesAI.push_back(eA2);
	enemiesAI.push_back(eA3);
	enemiesAI.push_back(eA4);
	enemiesAI.push_back(eA5);
	enemiesAI.push_back(eA6);
	enemiesAI.push_back(eA7);
	enemiesAI.push_back(eA8);
	enemiesAI.push_back(eA9);
	enemiesAI.push_back(eA10);
	enemiesAI.push_back(eA11);
	enemiesAI.push_back(eA12);
	enemiesAI.push_back(eA13);
	enemiesAI.push_back(eA14);
	enemiesAI.push_back(eA15);
	enemiesAI.push_back(eA16);
	enemiesAI.push_back(eA17);
	enemiesAI.push_back(eA18);
	enemiesAI.push_back(eA19);
	enemiesAI.push_back(eA20);




	//enemies coming from left need setGoleft =true
	//enemies coming from right need setGoright =true
	for (int i = 0; i < enemiesAI.size(); i++) {
		if (i % 2 == 0) {
			enemiesAI[i]->setXPos(i*(70));
			enemiesAI[i]->setGoRight(true);
			enemiesAI[i]->setJumpSpeed(40);
		}
		else {
			enemiesAI[i]->setXPos(i*(-70));
			enemiesAI[i]->setGoRight(true);
			enemiesAI[i]->setJumpSpeed(40);
		}
	}
	
	//player.setGliding(true);
	player.setFalling(true);
	player.setPosY(100.0);

	enemies.push_back(e1);
	enemies.push_back(e2);
	enemies.push_back(e3);
	enemies.push_back(e4);
	enemies.push_back(e5);
	/*********************/
	enemies[0]->setXSpeed(85);
	enemies[0]->setWalkingLeft(true);
	
	enemies[1]->setXSpeed(85);
	enemies[1]->setWalkingLeft(true);

	enemies[2]->setOnBox1(true);
	enemies[2]->setXSpeed(30.0);
	enemies[2]->setJumpSpeed(16.0);
	//enemies[2].setFallingSpeed(-10.0);

	enemies[3]->setOnBox3(true);
	enemies[3]->setXSpeed(30.0);
	enemies[3]->setJumpSpeed(20.0);
	enemies[3]->setFallingSpeed(5.0);

	enemies[4]->setOnBox4(true);
	enemies[4]->setXSpeed(30.0);
	enemies[4]->setJumpSpeed(-10.0);
	enemies[4]->setFallingSpeed(5.0);
	/*********************/
	glClearColor(0.0, 0.0, 0.0, 0.0);	//sets the clear colour to yellow
										//glClear(GL_COLOR_BUFFER_BIT) in the display function
										//will clear the buffer to this colour.
	
	boxes.push_back(box1);
	boxes.push_back(box2);
	boxes.push_back(box3);
	boxes.push_back(box4);
	boxes.push_back(box5);

	loadTextures();
}
void processKeys()
{
	if (keys[VK_UP]) {
		upPressed = true;
		downPressed = false;
	}

	if (keys[VK_DOWN]) {
		upPressed = false;
		downPressed = true;
	}

	if (!playerIsKilled()) {
		if (keys[VK_LEFT] && !player.getThrowing()) {
			player.setWalking(true);
			player.setWalkingLeft(true);
			//edge of left main platform
			if (player.getPosX() < -42.0)
			{
				player.setPosX(-42.0);
			}

			//control the rigth edge of the platform
			if ((platform.getX() < -400.0)
				&& (player.getPosX() <= 0.0))
			{
				platform.moveLeft(delta);
			}
			//control the left edge of the platfrom
			if ((platform.getX() >= -0.0)
				|| (platform.getX() <= -450.0))
			{
				player.moveLeft(delta);
			}
			//move the character accross the platfrom
			else {
				platform.moveLeft(delta);
			}
		}
		else {
			player.setWalking(false);
		}

		if (keys[VK_RIGHT] && !player.getThrowing())
		{
			player.setWalking(true);
			player.setWalkingLeft(false);
			/*p.setWalkingRight(true);
			p.setWalkingLeft(false);*/

			//right edge of the platform
			if (player.getPosX() > 185.0)
			{
				player.setPosX(185.0);
			}

			//move character right on the left and right edge of the platform
			if ((player.getPosX() <= 0.0)
				|| (platform.getX() < -450.0))
			{
				player.moveRight(delta);
			}
			//move the charactrer accross the platform
			else {
				platform.moveRight(delta);
			}

		}

		if (keys[VK_SPACE])
		{
			if (!player.isFalling()) {
				jumpPressed = true;
				player.setJump(true);
				player.jump();
			}
		}
		else jumpPressed = false;

		//throw kunai attack
		if (keys['W'] && !player.getThrowing()){

				player.ThrowAttack();
				//get the coordinates of the new kunai spawn only when the fire is true
				//so the coordinates will not mix up with the character's translation
		}
		else {
			player.setFire(false);
		}

		//attack with meelee on the right
		if (keys['D'] && rightDashTimer <=0 && player.canDash) {
			justAttacked = true;

			meleeLeftDirection = false;
			meleeXPosition = -platform.getX() + player.getPosX();
			meleeYPosition = player.getPosY();

			player.setWalkingLeft(false);
			attackRight = true;
			attackLeft = false;
			player.setAttacking(true);

			if ((player.getPosX() <= 0.0)
				|| (platform.getX() <= -450.0))
			{
				player.updateMeleeRight(delta);
			}
			else {
				platform.updateMeleeRight(player, delta);
			}
		}

		//attack with melee on the left
		if (keys['A'] && leftDashTimer <=0 && player.canDash) {
			justAttacked = true;

			meleeLeftDirection = true;
			meleeXPosition = -platform.getX() + player.getPosX();
			meleeYPosition = player.getPosY();

			player.setWalkingLeft(true);
			attackLeft = true;
			attackRight = false;
			player.setAttacking(true);

			if ((platform.getX() < -400.0)
				&& (player.getPosX() <= 0.0))
			{
				platform.updateMeleeLeft(player, delta);
			}
			//control the left edge of the platfrom
			if ((platform.getX() >= -0.0)
				|| (platform.getX() <= -450.0))
			{
				player.updateMeleeLeft(delta);
			}
			//move the character accross the platfrom
			else {
				platform.updateMeleeLeft(player, delta);
			}
		}

	}
	if (keys[13] && !gameOver) {
		if (upPressed) {
			startGame = true;
			mainMenu = false;
		}
		else if (downPressed) {
			showHelp = true;
			
		}
	}
	if (keys['B']) {
		if (showHelp) {
			showHelp = false;
		}
		if (gameOver) {
			KillGLWindow();
			mainMenu = true; 
			startGame = false;
		}
	}

	//debuggin enemies
/*	if (keys['U']) {
		enemiesAI[0]->moveUp();
	}
	if (keys['H']) {
		enemiesAI[0]->moveLeft();
	}
	if(keys['K']) {
		enemiesAI[0]->moveRight();
	}
	if (keys['J']) {
		enemiesAI[0]->moveDown();
	}
	if (keys['P']) {
		setEnemy = true;
		enemiesAI[0]->setFalling(true);
		enemiesAI[0]->setWalking(true);
	}*/
}

//method responsible for the collision of the character on the side of the platforms
void sideCollision() {
	//platform 1
	if (
		player.getPosY() > 10 &&
		player.getPosY() < 25 &&
		platform.getX() < -10.0 &&
		platform.getX() > -60.0) {

		platform.setX(previousX);
		player.setFalling(true);
	}

	//platform 2
	if (
		player.getPosY() > 15.0 &&
		player.getPosY() < 30.0 &&
		platform.getX() < -100.0 &&
		platform.getX() > -150.0) {

		platform.setX(previousX);
		player.setFalling(true);
	}

	//platform 3
	if (
		player.getPosY() > 20.0 &&
		player.getPosY() < 35.0 &&
		platform.getX() < -240.0 &&
		platform.getX() > -340.0) {

		platform.setX(previousX);
		player.setFalling(true);
	}

	//platform 4
	if (
		player.getPosY() > 45.0 &&
		player.getPosY() < 55.0 &&
		platform.getX() < -349.0&&
		platform.getX() > -420.0) {

		platform.setX(previousX);
		player.setFalling(true);
	}

	//platform 5
	if (
		player.getPosY() > 40.0+boxes[4].getYPos() &&
		player.getPosY() < 55.0+boxes[4].getYPos() &&
		platform.getX() < -160.0 &&
		platform.getX() > -230.0) {

		platform.setX(previousX);
		player.setFalling(true);
	}
}

/**************** END OPENGL FUNCTIONS *************************/

//WIN32 functions
LRESULT	CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);	// Declaration For WndProc
//void KillGLWindow();									// releases and destroys the window
bool CreateGLWindow(char* title, int width, int height); //creates the window
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int);  // Win32 main function

//win32 global variabless
HDC			hDC = NULL;		// Private GDI Device Context
HGLRC		hRC = NULL;		// Permanent Rendering Context
HWND		hWnd = NULL;		// Holds Our Window Handle
HINSTANCE	hInstance;		// Holds The Instance Of The Application

GLuint	base;				// Base Display List For The Font Set


/******************* WIN32 FUNCTIONS ***************************/
int WINAPI WinMain(HINSTANCE	hInstance,			// Instance
	HINSTANCE	hPrevInstance,		// Previous Instance
	LPSTR		lpCmdLine,			// Command Line Parameters
	int			nCmdShow)			// Window Show State
{
	MSG		msg;									// Windows Message Structure
	bool	done = false;								// Bool Variable To Exit Loop


	//OPENS CONSOLE WINDOW
	AllocConsole();
	FILE *stream;
	freopen_s(&stream, "CONOUT$", "w", stdout);

	// Create Our OpenGL Window
	if (!CreateGLWindow("OpenGL Win32 Example", screenWidth, screenHeight))
	{
		return 0;									// Quit If Window Was Not Created
	}

	while (!done)									// Loop That Runs While done=FALSE
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))	// Is There A Message Waiting?
		{
			if (msg.message == WM_QUIT)				// Have We Received A Quit Message?
			{
				done = true;							// If So done=TRUE
			}
			else									// If Not, Deal With Window Messages
			{
				TranslateMessage(&msg);				// Translate The Message
				DispatchMessage(&msg);				// Dispatch The Message
			}
		}
		else										// If There Are No Messages
		{
			if (keys[VK_ESCAPE])
				done = true;

			processKeys();

			display();					// Draw The Scene
			SwapBuffers(hDC);				// Swap Buffers (Double Buffering)
		}
	}

	// Shutdown
	KillGLWindow();									// Kill The Window
	return (int)(msg.wParam);						// Exit The Program
}

//WIN32 Processes function - useful for responding to user inputs or other events.
LRESULT CALLBACK WndProc(HWND	hWnd,			// Handle For This Window
	UINT	uMsg,			// Message For This Window
	WPARAM	wParam,			// Additional Message Information
	LPARAM	lParam)			// Additional Message Information
{
	switch (uMsg)									// Check For Windows Messages
	{
	case WM_CLOSE:								// Did We Receive A Close Message?
	{
		PostQuitMessage(0);						// Send A Quit Message
		return 0;								// Jump Back
	}
	break;

	case WM_SIZE:								// Resize The OpenGL Window
	{
		reshape(LOWORD(lParam), HIWORD(lParam));  // LoWord=Width, HiWord=Height
		return 0;								// Jump Back
	}
	break;

	case WM_LBUTTONDOWN:
	{
		mouse_x = LOWORD(lParam);
		mouse_y = screenHeight - HIWORD(lParam);
		LeftPressed = true;
	}
	break;

	case WM_LBUTTONUP:
	{
		LeftPressed = false;
	}
	break;

	case WM_MOUSEMOVE:
	{
		mouse_x = LOWORD(lParam);
		mouse_y = screenHeight - HIWORD(lParam);
	}
	break;
	case WM_KEYDOWN:							// Is A Key Being Held Down?
	{
		keys[wParam] = true;					// If So, Mark It As TRUE
		return 0;								// Jump Back
	}
	break;
	case WM_KEYUP:								// Has A Key Been Released?
	{
		keys[wParam] = false;					// If So, Mark It As FALSE
		return 0;								// Jump Back
	}
	break;
	}

	// Pass All Unhandled Messages To DefWindowProc
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

void KillGLWindow()								// Properly Kill The Window
{
	if (hRC)											// Do We Have A Rendering Context?
	{
		if (!wglMakeCurrent(NULL, NULL))					// Are We Able To Release The DC And RC Contexts?
		{
			MessageBox(NULL, "Release Of DC And RC Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		}

		if (!wglDeleteContext(hRC))						// Are We Able To Delete The RC?
		{
			MessageBox(NULL, "Release Rendering Context Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		}
		hRC = NULL;										// Set RC To NULL
	}

	if (hDC && !ReleaseDC(hWnd, hDC))					// Are We Able To Release The DC
	{
		MessageBox(NULL, "Release Device Context Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		hDC = NULL;										// Set DC To NULL
	}

	if (hWnd && !DestroyWindow(hWnd))					// Are We Able To Destroy The Window?
	{
		MessageBox(NULL, "Could Not Release hWnd.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		hWnd = NULL;										// Set hWnd To NULL
	}

	if (!UnregisterClass("OpenGL", hInstance))			// Are We Able To Unregister Class
	{
		MessageBox(NULL, "Could Not Unregister Class.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		hInstance = NULL;									// Set hInstance To NULL
	}
}

/*	This Code Creates Our OpenGL Window.  Parameters Are:					*
 *	title			- Title To Appear At The Top Of The Window				*
 *	width			- Width Of The GL Window Or Fullscreen Mode				*
 *	height			- Height Of The GL Window Or Fullscreen Mode			*/

bool CreateGLWindow(char* title, int width, int height)
{
	GLuint		PixelFormat;			// Holds The Results After Searching For A Match
	WNDCLASS	wc;						// Windows Class Structure
	DWORD		dwExStyle;				// Window Extended Style
	DWORD		dwStyle;				// Window Style
	RECT		WindowRect;				// Grabs Rectangle Upper Left / Lower Right Values
	WindowRect.left = (long)0;			// Set Left Value To 0
	WindowRect.right = (long)width;		// Set Right Value To Requested Width
	WindowRect.top = (long)0;				// Set Top Value To 0
	WindowRect.bottom = (long)height;		// Set Bottom Value To Requested Height

	hInstance = GetModuleHandle(NULL);				// Grab An Instance For Our Window
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;	// Redraw On Size, And Own DC For Window.
	wc.lpfnWndProc = (WNDPROC)WndProc;					// WndProc Handles Messages
	wc.cbClsExtra = 0;									// No Extra Window Data
	wc.cbWndExtra = 0;									// No Extra Window Data
	wc.hInstance = hInstance;							// Set The Instance
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);			// Load The Default Icon
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);			// Load The Arrow Pointer
	wc.hbrBackground = NULL;									// No Background Required For GL
	wc.lpszMenuName = NULL;									// We Don't Want A Menu
	wc.lpszClassName = "OpenGL";								// Set The Class Name

	if (!RegisterClass(&wc))									// Attempt To Register The Window Class
	{
		MessageBox(NULL, "Failed To Register The Window Class.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return false;											// Return FALSE
	}

	dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;			// Window Extended Style
	dwStyle = WS_OVERLAPPEDWINDOW;							// Windows Style

	AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);		// Adjust Window To True Requested Size

	// Create The Window
	if (!(hWnd = CreateWindowEx(dwExStyle,							// Extended Style For The Window
		"OpenGL",							// Class Name
		title,								// Window Title
		dwStyle |							// Defined Window Style
		WS_CLIPSIBLINGS |					// Required Window Style
		WS_CLIPCHILDREN,					// Required Window Style
		0, 0,								// Window Position
		WindowRect.right - WindowRect.left,	// Calculate Window Width
		WindowRect.bottom - WindowRect.top,	// Calculate Window Height
		NULL,								// No Parent Window
		NULL,								// No Menu
		hInstance,							// Instance
		NULL)))								// Dont Pass Anything To WM_CREATE
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Window Creation Error.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return false;								// Return FALSE
	}

	static	PIXELFORMATDESCRIPTOR pfd =				// pfd Tells Windows How We Want Things To Be
	{
		sizeof(PIXELFORMATDESCRIPTOR),				// Size Of This Pixel Format Descriptor
		1,											// Version Number
		PFD_DRAW_TO_WINDOW |						// Format Must Support Window
		PFD_SUPPORT_OPENGL |						// Format Must Support OpenGL
		PFD_DOUBLEBUFFER,							// Must Support Double Buffering
		PFD_TYPE_RGBA,								// Request An RGBA Format
		24,										// Select Our Color Depth
		0, 0, 0, 0, 0, 0,							// Color Bits Ignored
		0,											// No Alpha Buffer
		0,											// Shift Bit Ignored
		0,											// No Accumulation Buffer
		0, 0, 0, 0,									// Accumulation Bits Ignored
		24,											// 24Bit Z-Buffer (Depth Buffer)  
		0,											// No Stencil Buffer
		0,											// No Auxiliary Buffer
		PFD_MAIN_PLANE,								// Main Drawing Layer
		0,											// Reserved
		0, 0, 0										// Layer Masks Ignored
	};

	if (!(hDC = GetDC(hWnd)))							// Did We Get A Device Context?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Can't Create A GL Device Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return false;								// Return FALSE
	}

	if (!(PixelFormat = ChoosePixelFormat(hDC, &pfd)))	// Did Windows Find A Matching Pixel Format?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Can't Find A Suitable PixelFormat.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return false;								// Return FALSE
	}

	if (!SetPixelFormat(hDC, PixelFormat, &pfd))		// Are We Able To Set The Pixel Format?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Can't Set The PixelFormat.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return false;								// Return FALSE
	}

	if (!(hRC = wglCreateContext(hDC)))				// Are We Able To Get A Rendering Context?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Can't Create A GL Rendering Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return false;								// Return FALSE
	}

	if (!wglMakeCurrent(hDC, hRC))					// Try To Activate The Rendering Context
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Can't Activate The GL Rendering Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return false;								// Return FALSE
	}

	ShowWindow(hWnd, SW_SHOW);						// Show The Window
	SetForegroundWindow(hWnd);						// Slightly Higher Priority
	SetFocus(hWnd);									// Sets Keyboard Focus To The Window
	reshape(width, height);					// Set Up Our Perspective GL Screen

	init();

	return true;									// Success
}

GLvoid BuildFont(GLvoid)								// Build Our Bitmap Font
{
	HFONT	font;										// Windows Font ID
	HFONT	oldfont;									// Used For Good House Keeping

	base = glGenLists(96);								// Storage For 96 Characters

	font = CreateFont(-30,							// Height Of Font
		0,								// Width Of Font
		0,								// Angle Of Escapement
		0,								// Orientation Angle
		FW_NORMAL,						// Font Weight
		FALSE,							// Italic
		FALSE,							// Underline
		FALSE,							// Strikeout
		ANSI_CHARSET,					// Character Set Identifier
		OUT_TT_PRECIS,					// Output Precision
		CLIP_DEFAULT_PRECIS,			// Clipping Precision
		ANTIALIASED_QUALITY,			// Output Quality
		FF_DONTCARE | DEFAULT_PITCH,		// Family And Pitch
		"Times New Roman");					// Font Name

	oldfont = (HFONT)SelectObject(hDC, font);           // Selects The Font We Want
	wglUseFontBitmaps(hDC, 32, 96, base);				// Builds 96 Characters Starting At Character 32
	SelectObject(hDC, oldfont);							// Selects The Font We Want
	DeleteObject(font);									// Delete The Font
}

GLvoid KillFont(GLvoid)									// Delete The Font List
{
	glDeleteLists(base, 96);							// Delete All 96 Characters
}

GLvoid showTimer(int gameTimer)					// Custom GL "Print" Routine
{
	stringstream stream;
	if (gameTimer % 1000 == 0) {
		timerGame++;
	}
	stream << "TIME: "<<timerGame;

	glPushAttrib(GL_LIST_BIT);							// Pushes The Display List Bits
	glListBase(base - 32);								// Sets The Base Character to 32
														// first 32 chars not used
	glCallLists(stream.str().size(), GL_UNSIGNED_BYTE, stream.str().c_str());	// Draws The Display List Text
	glPopAttrib();										// Pops The Display List Bits

}

GLvoid printKills()					// Custom GL "Print" Routine
{
	stringstream stream;
	stream << player.getKills();

	glPushAttrib(GL_LIST_BIT);							// Pushes The Display List Bits
	glListBase(base - 32);								// Sets The Base Character to 32
														// first 32 chars not used
	glCallLists(stream.str().size(), GL_UNSIGNED_BYTE, stream.str().c_str());	// Draws The Display List Text
	glPopAttrib();										// Pops The Display List Bits

}

GLvoid printTimer()					// Custom GL "Print" Routine
{
	stringstream stream;
	stream << timerGame;

	glPushAttrib(GL_LIST_BIT);							// Pushes The Display List Bits
	glListBase(base - 32);								// Sets The Base Character to 32
														// first 32 chars not used
	glCallLists(stream.str().size(), GL_UNSIGNED_BYTE, stream.str().c_str());	// Draws The Display List Text
	glPopAttrib();										// Pops The Display List Bits

}

GLvoid showKunais()					// Custom GL "Print" Routine
{
	stringstream stream;
	stream << "KUNAIS: " << player.getKunaiCounter() << "/10";

	glPushAttrib(GL_LIST_BIT);							// Pushes The Display List Bits
	glListBase(base - 32);								// Sets The Base Character to 32
														// first 32 chars not used
	glCallLists(stream.str().size(), GL_UNSIGNED_BYTE, stream.str().c_str());	// Draws The Display List Text
	glPopAttrib();										// Pops The Display List Bits

}
GLvoid showKills()					// Custom GL "Print" Routine
{
	stringstream stream;
	stream << "KILLS: " << player.getKills();

	glPushAttrib(GL_LIST_BIT);							// Pushes The Display List Bits
	glListBase(base - 32);								// Sets The Base Character to 32
														// first 32 chars not used
	glCallLists(stream.str().size(), GL_UNSIGNED_BYTE, stream.str().c_str());	// Draws The Display List Text
	glPopAttrib();										// Pops The Display List Bits

}
GLvoid showHeaLth()					// Custom GL "Print" Routine
{
	stringstream stream;
	stream << "LIVES: " << player.getHealth();

	glPushAttrib(GL_LIST_BIT);							// Pushes The Display List Bits
	glListBase(base - 32);								// Sets The Base Character to 32
														// first 32 chars not used
	glCallLists(stream.str().size(), GL_UNSIGNED_BYTE, stream.str().c_str());	// Draws The Display List Text
	glPopAttrib();										// Pops The Display List Bits

}
GLuint loadPNG(char* name)
{
	// Texture loading object
	nv::Image img;

	GLuint myTextureID;

	// Return true on success
	if (img.loadImageFromFile(name))	//open the tecture file
	{
		glGenTextures(1, &myTextureID);
		glBindTexture(GL_TEXTURE_2D, myTextureID);
		glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
		glTexImage2D(GL_TEXTURE_2D, 0, img.getInternalFormat(), img.getWidth(), img.getHeight(), 0, img.getFormat(), img.getType(), img.getLevel(0));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 16.0f);
	}
	else
		MessageBox(NULL, "Failed to load texture", "End of the world", MB_OK | MB_ICONINFORMATION);

	return myTextureID;
}

void loadTextures() {
	player.healthBarTex[0] = loadPNG("Images/healthBar/threeHealthBar.png");
	player.healthBarTex[1] = loadPNG("Images/healthBar/twoHealthBar.png");
	player.healthBarTex[2] = loadPNG("Images/healthBar/oneHealthBar.png");
	player.healthBarTex[3] = loadPNG("Images/healthBar/zeroHealthBar.png");

	player.charIdle[0] = loadPNG("Images/ninja/idle/Idle__000.png");
	player.charIdle[1] = loadPNG("Images/ninja/idle/Idle__001.png");
	player.charIdle[2] = loadPNG("Images/ninja/idle/Idle__002.png");
	player.charIdle[3] = loadPNG("Images/ninja/idle/Idle__003.png");
	player.charIdle[4] = loadPNG("Images/ninja/idle/Idle__004.png");
	player.charIdle[5] = loadPNG("Images/ninja/idle/Idle__005.png");
	player.charIdle[6] = loadPNG("Images/ninja/idle/Idle__006.png");
	player.charIdle[7] = loadPNG("Images/ninja/idle/Idle__007.png");
	player.charIdle[8] = loadPNG("Images/ninja/idle/Idle__008.png");
	player.charIdle[9] = loadPNG("Images/ninja/idle/Idle__009.png");

	player.charDeadTex[0] = loadPNG("Images/ninja/dead/Dead__000.png");
	player.charDeadTex[1] = loadPNG("Images/ninja/dead/Dead__001.png");
	player.charDeadTex[2] = loadPNG("Images/ninja/dead/Dead__002.png");
	player.charDeadTex[3] = loadPNG("Images/ninja/dead/Dead__003.png");
	player.charDeadTex[4] = loadPNG("Images/ninja/dead/Dead__004.png");
	player.charDeadTex[5] = loadPNG("Images/ninja/dead/Dead__005.png");
	player.charDeadTex[6] = loadPNG("Images/ninja/dead/Dead__006.png");
	player.charDeadTex[7] = loadPNG("Images/ninja/dead/Dead__007.png");
	player.charDeadTex[8] = loadPNG("Images/ninja/dead/Dead__008.png");
	player.charDeadTex[9] = loadPNG("Images/ninja/dead/Dead__009.png");

	player.charRunTex[0] = loadPNG("Images/ninja/run/Run__000.png");
	player.charRunTex[1] = loadPNG("Images/ninja/run/Run__001.png");
	player.charRunTex[2] = loadPNG("Images/ninja/run/Run__002.png");
	player.charRunTex[3] = loadPNG("Images/ninja/run/Run__003.png");
	player.charRunTex[4] = loadPNG("Images/ninja/run/Run__004.png");
	player.charRunTex[5] = loadPNG("Images/ninja/run/Run__005.png");
	player.charRunTex[6] = loadPNG("Images/ninja/run/Run__006.png");
	player.charRunTex[7] = loadPNG("Images/ninja/run/Run__007.png");
	player.charRunTex[8] = loadPNG("Images/ninja/run/Run__008.png");
	player.charRunTex[9] = loadPNG("Images/ninja/run/Run__009.png");

	player.charThrowTex[0] = loadPNG("Images/ninja/throw/Throw__000.png");
	player.charThrowTex[1] = loadPNG("Images/ninja/throw/Throw__001.png");
	player.charThrowTex[2] = loadPNG("Images/ninja/throw/Throw__002.png");
	player.charThrowTex[3] = loadPNG("Images/ninja/throw/Throw__003.png");
	player.charThrowTex[4] = loadPNG("Images/ninja/throw/Throw__004.png");
	player.charThrowTex[5] = loadPNG("Images/ninja/throw/Throw__005.png");
	player.charThrowTex[6] = loadPNG("Images/ninja/throw/Throw__006.png");
	player.charThrowTex[7] = loadPNG("Images/ninja/throw/Throw__007.png");
	player.charThrowTex[8] = loadPNG("Images/ninja/throw/Throw__008.png");
	player.charThrowTex[9] = loadPNG("Images/ninja/throw/Throw__009.png");


	player.charAttackTex[0] = loadPNG("Images/ninja/attack/Attack__000.png");
	player.charAttackTex[1] = loadPNG("Images/ninja/attack/Attack__001.png");
	player.charAttackTex[2] = loadPNG("Images/ninja/attack/Attack__002.png");
	player.charAttackTex[3] = loadPNG("Images/ninja/attack/Attack__003.png");
	player.charAttackTex[4] = loadPNG("Images/ninja/attack/Attack__004.png");
	player.charAttackTex[5] = loadPNG("Images/ninja/attack/Attack__005.png");
	player.charAttackTex[6] = loadPNG("Images/ninja/attack/Attack__006.png");
	player.charAttackTex[7] = loadPNG("Images/ninja/attack/Attack__007.png");
	player.charAttackTex[8] = loadPNG("Images/ninja/attack/Attack__008.png");
	player.charAttackTex[9] = loadPNG("Images/ninja/attack/Attack__009.png");


	player.charGlideTex[0] = loadPNG("Images/ninja/glide/Glide_000.png");
	player.charGlideTex[1] = loadPNG("Images/ninja/glide/Glide_001.png");
	player.charGlideTex[2] = loadPNG("Images/ninja/glide/Glide_002.png");
	player.charGlideTex[3] = loadPNG("Images/ninja/glide/Glide_003.png");
	player.charGlideTex[4] = loadPNG("Images/ninja/glide/Glide_004.png");
	player.charGlideTex[5] = loadPNG("Images/ninja/glide/Glide_005.png");
	player.charGlideTex[6] = loadPNG("Images/ninja/glide/Glide_006.png");
	player.charGlideTex[7] = loadPNG("Images/ninja/glide/Glide_007.png");
	player.charGlideTex[8] = loadPNG("Images/ninja/glide/Glide_008.png");
	player.charGlideTex[9] = loadPNG("Images/ninja/glide/Glide_009.png");

	player.charJumpTex[0] = loadPNG("Images/ninja/jump/Jump__001.png");
	player.charJumpTex[1] = loadPNG("Images/ninja/jump/Jump__009.png");

	enemies[0]->enemyRunTex[0] = loadPNG("Images/SamuraiHeavy/Run0/Run0.png");
	enemies[0]->enemyRunTex[1] = loadPNG("Images/SamuraiHeavy/Run0/Run1.png");
	enemies[0]->enemyRunTex[2] = loadPNG("Images/SamuraiHeavy/Run0/Run2.png");
	enemies[0]->enemyRunTex[3] = loadPNG("Images/SamuraiHeavy/Run0/Run3.png");
	enemies[0]->enemyRunTex[4] = loadPNG("Images/SamuraiHeavy/Run0/Run4.png");
	enemies[0]->enemyRunTex[5] = loadPNG("Images/SamuraiHeavy/Run0/Run5.png");
	enemies[0]->enemyRunTex[6] = loadPNG("Images/SamuraiHeavy/Run0/Run6.png");
	enemies[0]->enemyRunTex[7] = loadPNG("Images/SamuraiHeavy/Run0/Run7.png");
	enemies[0]->enemyRunTex[8] = loadPNG("Images/SamuraiHeavy/Run0/Run8.png");
	enemies[0]->enemyRunTex[9] = loadPNG("Images/SamuraiHeavy/Run0/Run9.png");

	enemies[0]->enemyAttackTex[0] = loadPNG("Images/SamuraiHeavy/Attack/Attack0.png");
	enemies[0]->enemyAttackTex[1] = loadPNG("Images/SamuraiHeavy/Attack/Attack1.png");
	enemies[0]->enemyAttackTex[2] = loadPNG("Images/SamuraiHeavy/Attack/Attack2.png");
	enemies[0]->enemyAttackTex[3] = loadPNG("Images/SamuraiHeavy/Attack/Attack3.png");
	enemies[0]->enemyAttackTex[4] = loadPNG("Images/SamuraiHeavy/Attack/Attack4.png");
	enemies[0]->enemyAttackTex[5] = loadPNG("Images/SamuraiHeavy/Attack/Attack5.png");
	enemies[0]->enemyAttackTex[6] = loadPNG("Images/SamuraiHeavy/Attack/Attack6.png");
	enemies[0]->enemyAttackTex[7] = loadPNG("Images/SamuraiHeavy/Attack/Attack7.png");
	enemies[0]->enemyAttackTex[8] = loadPNG("Images/SamuraiHeavy/Attack/Attack8.png");
	enemies[0]->enemyAttackTex[9] = loadPNG("Images/SamuraiHeavy/Attack/Attack9.png");

	enemies[0]->enemyDeadTex[0] = loadPNG("Images/SamuraiHeavy/Die/0.png");
	enemies[0]->enemyDeadTex[1] = loadPNG("Images/SamuraiHeavy/Die/1.png");
	enemies[0]->enemyDeadTex[2] = loadPNG("Images/SamuraiHeavy/Die/2.png");
	enemies[0]->enemyDeadTex[3] = loadPNG("Images/SamuraiHeavy/Die/3.png");
	enemies[0]->enemyDeadTex[4] = loadPNG("Images/SamuraiHeavy/Die/4.png");
	enemies[0]->enemyDeadTex[5] = loadPNG("Images/SamuraiHeavy/Die/5.png");
	enemies[0]->enemyDeadTex[6] = loadPNG("Images/SamuraiHeavy/Die/6.png");
	enemies[0]->enemyDeadTex[7] = loadPNG("Images/SamuraiHeavy/Die/7.png");
	enemies[0]->enemyDeadTex[8] = loadPNG("Images/SamuraiHeavy/Die/8.png");
	enemies[0]->enemyDeadTex[9] = loadPNG("Images/SamuraiHeavy/Die/9.png");


	enemies[4]->enemyRunTex[0] = enemies[3]->enemyRunTex[0] = enemies[2]->enemyRunTex[0] = enemies[1]->enemyRunTex[0] = enemies[0]->enemyRunTex[0];
	enemies[4]->enemyRunTex[1] = enemies[3]->enemyRunTex[1] = enemies[2]->enemyRunTex[1] = enemies[1]->enemyRunTex[1] = enemies[0]->enemyRunTex[1];
	enemies[4]->enemyRunTex[2] = enemies[3]->enemyRunTex[2] = enemies[2]->enemyRunTex[2] = enemies[1]->enemyRunTex[2] = enemies[0]->enemyRunTex[2];
	enemies[4]->enemyRunTex[3] = enemies[3]->enemyRunTex[3] = enemies[2]->enemyRunTex[3] = enemies[1]->enemyRunTex[3] = enemies[0]->enemyRunTex[3];
	enemies[4]->enemyRunTex[4] = enemies[3]->enemyRunTex[4] = enemies[2]->enemyRunTex[4] = enemies[1]->enemyRunTex[4] = enemies[0]->enemyRunTex[4];
	enemies[4]->enemyRunTex[5] = enemies[3]->enemyRunTex[5] = enemies[2]->enemyRunTex[5] = enemies[1]->enemyRunTex[5] = enemies[0]->enemyRunTex[5];
	enemies[4]->enemyRunTex[6] = enemies[3]->enemyRunTex[6] = enemies[2]->enemyRunTex[6] = enemies[1]->enemyRunTex[6] = enemies[0]->enemyRunTex[6];
	enemies[4]->enemyRunTex[7] = enemies[3]->enemyRunTex[7] = enemies[2]->enemyRunTex[7] = enemies[1]->enemyRunTex[7] = enemies[0]->enemyRunTex[7];
	enemies[4]->enemyRunTex[8] = enemies[3]->enemyRunTex[8] = enemies[2]->enemyRunTex[8] = enemies[1]->enemyRunTex[8] = enemies[0]->enemyRunTex[8];
	enemies[4]->enemyRunTex[9] = enemies[3]->enemyRunTex[9] = enemies[2]->enemyRunTex[9] = enemies[1]->enemyRunTex[9] = enemies[0]->enemyRunTex[9];


	enemies[4]->enemyAttackTex[0] = enemies[3]->enemyAttackTex[0] = enemies[2]->enemyAttackTex[0] = enemies[1]->enemyAttackTex[0] = enemies[0]->enemyAttackTex[0];
	enemies[4]->enemyAttackTex[1] = enemies[3]->enemyAttackTex[1] = enemies[2]->enemyAttackTex[1] = enemies[1]->enemyAttackTex[1] = enemies[0]->enemyAttackTex[1];
	enemies[4]->enemyAttackTex[2] = enemies[3]->enemyAttackTex[2] = enemies[2]->enemyAttackTex[2] = enemies[1]->enemyAttackTex[2] = enemies[0]->enemyAttackTex[2];
	enemies[4]->enemyAttackTex[3] = enemies[3]->enemyAttackTex[3] = enemies[2]->enemyAttackTex[3] = enemies[1]->enemyAttackTex[3] = enemies[0]->enemyAttackTex[3];
	enemies[4]->enemyAttackTex[4] = enemies[3]->enemyAttackTex[4] = enemies[2]->enemyAttackTex[4] = enemies[1]->enemyAttackTex[4] = enemies[0]->enemyAttackTex[4];
	enemies[4]->enemyAttackTex[5] = enemies[3]->enemyAttackTex[5] = enemies[2]->enemyAttackTex[5] = enemies[1]->enemyAttackTex[5] = enemies[0]->enemyAttackTex[5];
	enemies[4]->enemyAttackTex[6] = enemies[3]->enemyAttackTex[6] = enemies[2]->enemyAttackTex[6] = enemies[1]->enemyAttackTex[6] = enemies[0]->enemyAttackTex[6];
	enemies[4]->enemyAttackTex[7] = enemies[3]->enemyAttackTex[7] = enemies[2]->enemyAttackTex[7] = enemies[1]->enemyAttackTex[7] = enemies[0]->enemyAttackTex[7];
	enemies[4]->enemyAttackTex[8] = enemies[3]->enemyAttackTex[8] = enemies[2]->enemyAttackTex[8] = enemies[1]->enemyAttackTex[8] = enemies[0]->enemyAttackTex[8];
	enemies[4]->enemyAttackTex[9] = enemies[3]->enemyAttackTex[9] = enemies[2]->enemyAttackTex[9] = enemies[1]->enemyAttackTex[9] = enemies[0]->enemyAttackTex[9];

	enemies[4]->enemyDeadTex[0] = enemies[3]->enemyDeadTex[0] = enemies[2]->enemyDeadTex[0] = enemies[1]->enemyDeadTex[0] = enemies[0]->enemyDeadTex[0];
	enemies[4]->enemyDeadTex[1] = enemies[3]->enemyDeadTex[1] = enemies[2]->enemyDeadTex[1] = enemies[1]->enemyDeadTex[1] = enemies[0]->enemyDeadTex[1];
	enemies[4]->enemyDeadTex[2] = enemies[3]->enemyDeadTex[2] = enemies[2]->enemyDeadTex[2] = enemies[1]->enemyDeadTex[2] = enemies[0]->enemyDeadTex[2];
	enemies[4]->enemyDeadTex[3] = enemies[3]->enemyDeadTex[3] = enemies[2]->enemyDeadTex[3] = enemies[1]->enemyDeadTex[3] = enemies[0]->enemyDeadTex[3];
	enemies[4]->enemyDeadTex[4] = enemies[3]->enemyDeadTex[4] = enemies[2]->enemyDeadTex[4] = enemies[1]->enemyDeadTex[4] = enemies[0]->enemyDeadTex[4];
	enemies[4]->enemyDeadTex[5] = enemies[3]->enemyDeadTex[5] = enemies[2]->enemyDeadTex[5] = enemies[1]->enemyDeadTex[5] = enemies[0]->enemyDeadTex[5];
	enemies[4]->enemyDeadTex[6] = enemies[3]->enemyDeadTex[6] = enemies[2]->enemyDeadTex[6] = enemies[1]->enemyDeadTex[6] = enemies[0]->enemyDeadTex[6];
	enemies[4]->enemyDeadTex[7] = enemies[3]->enemyDeadTex[7] = enemies[2]->enemyDeadTex[7] = enemies[1]->enemyDeadTex[7] = enemies[0]->enemyDeadTex[7];
	enemies[4]->enemyDeadTex[8] = enemies[3]->enemyDeadTex[8] = enemies[2]->enemyDeadTex[8] = enemies[1]->enemyDeadTex[8] = enemies[0]->enemyDeadTex[8];
	enemies[4]->enemyDeadTex[9] = enemies[3]->enemyDeadTex[9] = enemies[2]->enemyDeadTex[9] = enemies[1]->enemyDeadTex[9] = enemies[0]->enemyDeadTex[9];

	boxes[0].platformTexture = loadPNG("Images/box_platform.png");
	boxes[1].platformTexture = loadPNG("Images/box_platform.png");
	boxes[2].platformTexture = loadPNG("Images/box_platform.png");
	boxes[3].platformTexture = loadPNG("Images/box_platform.png");
	boxes[4].platformTexture = loadPNG("Images/box_platform.png");
	platform.platform_texture = loadPNG("Images/platform.png");
	sky.platformTexture = loadPNG("Images/0.png");
	landscape1.platformTexture = loadPNG("Images/3.png");
	landscape2.platformTexture = loadPNG("Images/1.png");
	trainBG.platformTexture = loadPNG("Images/train/trainBG_13.png");
	train.platformTexture = loadPNG("Images/train.png");

	enemiesAI[0]->enemyRunTex[0] = loadPNG("Images/enemyNinja/Run/0.png");
	enemiesAI[0]->enemyRunTex[1] = loadPNG("Images/enemyNinja/Run/1.png");
	enemiesAI[0]->enemyRunTex[2] = loadPNG("Images/enemyNinja/Run/2.png");
	enemiesAI[0]->enemyRunTex[3] = loadPNG("Images/enemyNinja/Run/3.png");
	enemiesAI[0]->enemyRunTex[4] = loadPNG("Images/enemyNinja/Run/4.png");
	enemiesAI[0]->enemyRunTex[5] = loadPNG("Images/enemyNinja/Run/5.png");
	enemiesAI[0]->enemyRunTex[6] = loadPNG("Images/enemyNinja/Run/6.png");
	enemiesAI[0]->enemyRunTex[7] = loadPNG("Images/enemyNinja/Run/7.png");
	enemiesAI[0]->enemyRunTex[8] = loadPNG("Images/enemyNinja/Run/8.png");
	enemiesAI[0]->enemyRunTex[9] = loadPNG("Images/enemyNinja/Run/9.png");


	enemiesAI[0]->enemyAttackTex[0] = loadPNG("Images/enemyNinja/Attack/0.png");
	enemiesAI[0]->enemyAttackTex[1] = loadPNG("Images/enemyNinja/Attack/1.png");
	enemiesAI[0]->enemyAttackTex[2] = loadPNG("Images/enemyNinja/Attack/2.png");
	enemiesAI[0]->enemyAttackTex[3] = loadPNG("Images/enemyNinja/Attack/3.png");
	enemiesAI[0]->enemyAttackTex[4] = loadPNG("Images/enemyNinja/Attack/4.png");
	enemiesAI[0]->enemyAttackTex[5] = loadPNG("Images/enemyNinja/Attack/5.png");
	enemiesAI[0]->enemyAttackTex[6] = loadPNG("Images/enemyNinja/Attack/6.png");
	enemiesAI[0]->enemyAttackTex[7] = loadPNG("Images/enemyNinja/Attack/7.png");
	enemiesAI[0]->enemyAttackTex[8] = loadPNG("Images/enemyNinja/Attack/8.png");
	enemiesAI[0]->enemyAttackTex[9] = loadPNG("Images/enemyNinja/Attack/9.png");

	enemiesAI[0]->enemyDeadTex[0] = loadPNG("Images/enemyNinja/Die/0.png");
	enemiesAI[0]->enemyDeadTex[1] = loadPNG("Images/enemyNinja/Die/1.png");
	enemiesAI[0]->enemyDeadTex[2] = loadPNG("Images/enemyNinja/Die/2.png");
	enemiesAI[0]->enemyDeadTex[3] = loadPNG("Images/enemyNinja/Die/3.png");
	enemiesAI[0]->enemyDeadTex[4] = loadPNG("Images/enemyNinja/Die/4.png");
	enemiesAI[0]->enemyDeadTex[5] = loadPNG("Images/enemyNinja/Die/5.png");
	enemiesAI[0]->enemyDeadTex[6] = loadPNG("Images/enemyNinja/Die/6.png");
	enemiesAI[0]->enemyDeadTex[7] = loadPNG("Images/enemyNinja/Die/7.png");
	enemiesAI[0]->enemyDeadTex[8] = loadPNG("Images/enemyNinja/Die/8.png");
	enemiesAI[0]->enemyDeadTex[9] = loadPNG("Images/enemyNinja/Die/9.png");

	for (int i = 1; i < enemiesAI.size(); i++) {
		for (int j = 0; j <= 9; j++) {
			enemiesAI[i]->enemyRunTex[j] = enemiesAI[0]->enemyRunTex[j];
			enemiesAI[i]->enemyAttackTex[j] = enemiesAI[0]->enemyAttackTex[j];
			enemiesAI[i]->enemyDeadTex[j] = enemiesAI[0]->enemyDeadTex[j];
		}
	}
	
	bg.platformTexture = loadPNG("Images/mainMenuScreen/0.png");
	title.platformTexture = loadPNG("Images/mainMenuScreen/options/title.png");
	option1.platformTexture = loadPNG("Images/mainMenuScreen/options/newGameOption.png");
	option2.platformTexture = loadPNG("Images/mainMenuScreen/options/helpOption.png");
	helpScreen.platformTexture = loadPNG("Images/mainMenuScreen/helpScreen.png");
	gameOverScreen.platformTexture = loadPNG("Images/mainMenuScreen/gameOverScreen.png");


}