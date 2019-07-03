
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


int	mouse_x = 0, mouse_y = 0;
bool LeftPressed = false;
int screenWidth = 1280, screenHeight = 720;
bool keys[256];
float keyboard_x = 0.0;
float keyboard_y = 0.0;
float spin = 0;
float speed = 0;
float timer = 0;
float walkTime = 0;
float matrix[16];
int gameTimer = 0;
int counter = 0;
bool jumpPressed = false;
bool attacked = false;
bool startWait = false;
bool drawKunai = false;
bool kunaiDirection = false;
float kunaiXPosition = 0.0;
float kunaiYPosition = 0.0;
bool startFire = false;
bool throwAttack = false;
clock_t previousTicks = 1;
clock_t currentTicks;
float delta;
int attackTimer = 0;

//OPENGL FUNCTION PROTOTYPES
void display();				//called in winmain to draw everything to the screen
void reshape(int width, int height);				//called when the window is resized
void init();				//called in winmain when the program starts.
void processKeys();         //called in winmain to process keyboard input
GLuint loadPNG(char* name);
void update();				//called in winmain to update variables
float calculateDelta();
void updateEnemies(float delta);
bool wait();

Player player;
Platform platform;

Box box1 = Box(70.0, 50.0, 40.0, 10.0);
Box box2 = Box(160.0, 60.0, 40.0, 10.0);
Box box3 = Box(300.0, 70.0, 90.0, 10.0);
Box box4 = Box(410.0, 120.0, 60.0, 10.0);
Box leftBar = Box(0.0, 0.0, 5.0, 500.0);
Box rightBar = Box(695.0, 0.0, 5.0, 500.0);
//Box sky = Box(0.0,200.0,700.0,50.0);
Box landscape = Box(0.0, 8.0, 700.0, 300.0);
vector<Box> boxes;
vector<Enemy> enemies;
Enemy e1 = Enemy(500.0, 8.0, 10.0, 20.0);
Enemy e2 = Enemy(550.0, 8.0, 10.0, 20.0);
Enemy e3 = Enemy(70.0, 60.0, 10.0, 20.0, 0.0, 10.0);
Enemy e4 = Enemy(300.0, 80.0, 10.0, 20.0, 0.0, 50.0);
Enemy e5 = Enemy(410.0, 130.0, 10.0, 20.0, -50.0, 0.0);

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


/*************    START OF OPENGL FUNCTIONS   ****************/
void display()
{
	float pCurrentX = -platform.getX() + player.getX() + player.getWidth() + player.getPosX();
	float pCurrentY = platform.getY() + player.getPosY() + player.getHeight();
	player.setPlayerX(platform.getX());
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	
	currentTicks = clock();		//current cpu ticks for delta time
	float deltaTicks = (float)(currentTicks / previousTicks);

	glPushMatrix();
		glScalef(0.4, 0.4, 0);
		glPushMatrix();
			//check for edge of the main platform
			if ((platform.getX() <= 0.0)){
				glTranslatef(platform.getX(), platform.getY(), 0);
			}
			//sky.draw(10.0);
			landscape.draw(5.0);
			//landscapenemies[1].drawLandscape();
			boxes[0].draw();
			boxes[1].draw();
			boxes[2].draw();
			boxes[3].draw();
			//leftBar.draw();
			//rightBar.draw();
			platform.drawPlatform();

			//enemies[0].drawEnemy();
			
			for (int i = 0; i < enemies.size(); i++) {
				if (enemies[i].getAlive()) {
					enemies[i].drawEnemy();
				}
				else {
					cout << "dead: " << i << endl;
				}
			}
			//enemies[0].drawEnemy();
			//enemies[0].drawCollisionBox(enemies[0].getXPos(),enemies[0].getYPos());	//give translation coordinates
			//enemies[0].drawEnemyLine(rightBar.getRightX(), enemies[0].getY(), 1.0, 1.0, 1.0);
			//enemies[0].drawEnemyLine(leftBar.getRightX(), enemies[0].getY(), 1.0, 0.0, 0.0);

			//enemies[1].drawEnemy();
			//enemies[1].drawCollisionBox(enemies[1].getXPos(), enemies[1].getYPos()); //give translation coordinates
			//enemies[1].drawEnemyLine(rightBar.getRightX(), enemies[1].getY(), 1.0, 1.0, 1.0);
			//enemies[1].drawEnemyLine(leftBar.getRightX(), enemies[1].getY(), 1.0, 0.0, 0.0);

			//enemies[2].drawEnemy();
			//enemies[2].drawCollisionBox(enemies[2].getXPos(), enemies[2].getYPos()); //give translation coordinates
			//enemies[2].getCollisionBox().drawCollisionLine(platform.getX(), p.getY(),1,1,1);
			
			//enemies[2].drawEnemyCollisionLine(pCurrentX, pCurrentY, 0.0, 1.0, 0.0);
			//enemies[3].drawEnemy();
			//enemies[3].drawCollisionBox(enemies[3].getXPos(), enemies[3].getYPos()); //give translation coordinates

			//enemies[4].drawEnemy();
			//enemies[4].drawCollisionBox(enemies[4].getXPos(), enemies[4].getYPos()); //give translation coordinates
			
			if (player.getFire()) { 
				throwAttack = true;
			}

			if (throwAttack) {
				player.drawWeapon(kunaiDirection, kunaiXPosition,kunaiYPosition,delta,enemies);
			}
			if (player.getThrowing()) {
				//player.getWeapon().drawWeaponCollisionLine(enemies[0].getXPoint(), enemies[0].getYPoint(), 1, 1, 1);
				/*glPushMatrix();
				glLineWidth(1.0);
				glColor3f(1, 1, 1);
				glBegin(GL_LINES);
				glVertex2d(player.getWeapon().getXPoint(), player.getWeapon().getYPoint());
				glVertex2d(enemies[0].getXPoint() - enemies[0].getXPos(), enemies[0].getYPoint());
				glEnd();
				glPopMatrix();*/
				
			}
			

				/*glColor3f(1, 1, 0);
				glPointSize(5);
				glPushMatrix();
					glBegin(GL_POINTS);
						glVertex2i(enemies[0].getXPoint(), enemies[0].getYPoint());
					glEnd();
				glPopMatrix();*/
		glPopMatrix();

		glPushMatrix();
			glTranslatef(player.getPosX(), player.getPosY(), 0);
			player.drawCharacter();
		//	player.drawCollisionBox();
		glPopMatrix();
		
	glPopMatrix();
	glFlush();
	
	//calculate the delta time for the animations
	previousTicks = currentTicks;
	delta = deltaTicks / (float)CLOCKS_PER_SEC;
	
	if (gameTimer > 50 && player.isAlive() && false) {
		updateEnemies(delta);
	}
	

	player.platformsCollisionUpdate(platform.getX(), jumpPressed, boxes);
	player.update(delta);	//player update

	gameTimer += 1;
}
/*******************************END DISPLAY************************************************/
void update() {

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
	float left_distanceenemiesE1 = leftBar.getRightX() - enemies[0].getXPos();
	float right_distanceenemiesE1 = rightBar.getRightX() - enemies[0].getXPos();
	
	float left_distanceenemiesE2 = leftBar.getRightX() - enemies[1].getXPos();
	float right_distanceenemiesE2 = rightBar.getLeftX() - enemies[1].getXPos();
	
	/*******************GROUND EMENIES*************************/
	if (left_distanceenemiesE1 > enemies[0].getX()) {
		enemies[0].setLeftWallHit(true);
		enemies[0].setRightWallHit(false);
	}
	else if (right_distanceenemiesE1 < 515.0) {
		enemies[0].setLeftWallHit(false);
		enemies[0].setRightWallHit(true);
	}

	if (left_distanceenemiesE2 >= enemies[1].getX()){	// > 100.0
		enemies[1].setLeftWallHit(true);
		enemies[1].setRightWallHit(false);
	}
	else if (right_distanceenemiesE2 < 560.0) {
		enemies[1].setLeftWallHit(false);
		enemies[1].setRightWallHit(true);
	}	

	/*******************PLATFORM EMENIES***********************/
				/**************ENEMY 3******************/
	//jump from the first box to the second
	
	if (enemies[2].getOnBox1() && enemies[2].getXPos() > 30.0 && enemies[2].getXPos() < 80.0) {
		enemies[2].setNeedJump(true);
		enemies[2].setCanJump(true);
	}
	//jump from the second box to the first
	if (enemies[2].getOnBox2() && enemies[2].getXPos() < 88.0) {
		enemies[2].setNeedJump(true);
		enemies[2].setCanJump(true);	
	}
	//the enemy will go left when goes to edge of the second box
	if (enemies[2].getOnBox2() && enemies[2].getXPos() > 120.0) {
		enemies[2].setEdgeHit(true);
		enemies[2].setGoLeft(true);
	}
	//the enemy will go right when goes to edge of the first box
	if (enemies[2].getOnBox1() && enemies[2].getXPos() < 0.0) {
		enemies[2].setEdgeHit(true);
		enemies[2].setGoRight(true);
	}
	
				
				/**************ENEMY 4******************/
	//jump from the third box to the forth
	if (enemies[3].getOnBox3() && enemies[3].getXPos() > 80.0 && enemies[3].getXPos() < 108.0) {
		enemies[3].setNeedJump(true);
		enemies[3].setCanJump(true);
	}
	//jump from the forth box to the third
	if (enemies[3].getOnBox4() && enemies[3].getXPos() < 108.0) {
		enemies[3].setNeedJump(true);
		enemies[3].setCanJump(true);
	}
	//the enemy will go left when goes to edge of the forth box	
	if (enemies[3].getOnBox4() && enemies[3].getXPos() > 160.0) {
		enemies[3].setEdgeHit(true);
		enemies[3].setGoLeft(true);
	}
	//the enemy will go right when goes to edge of the third box
	if (enemies[3].getOnBox3() && enemies[3].getXPos() < 0.0) {
		enemies[3].setEdgeHit(true);
		enemies[3].setGoRight(true);
	}

			/**************ENEMY 5******************/
	//the enemy will go left when goes to edge of the forth box	
	if (enemies[4].getOnBox4() && enemies[4].getXPos() > 50.0) {
		enemies[4].setEdgeHit(true);
		enemies[4].setGoLeft(true);
	}
	//jump from the forth box to the third
	if (enemies[4].getOnBox4() && enemies[4].getXPos() < 0.0) {
		enemies[4].setNeedJump(true);
		enemies[4].setCanJump(true);
	}
	//jump from the forth box to the third
	if (enemies[4].getOnBox3() && enemies[4].getXPos() < -112.0) {
		enemies[4].setEdgeHit(true);
		enemies[4].setGoRight(true);
	}
	//jump from the third box to the forth
	if (enemies[4].getOnBox3() && enemies[4].getXPos() > -30.0 && enemies[4].getXPos() < 0.0) {
		enemies[4].setNeedJump(true);
		enemies[4].setCanJump(true);
	}

	/******************************UPDATES********************************/
	float distance1 = player.getEU_distance(enemies[0].getXPoint(), enemies[0].getYPoint(), platform.getX(), platform.getY());
	float distance2 = player.getEU_distance(enemies[1].getXPoint(), enemies[1].getYPoint(), platform.getX(), platform.getY());
	float distance3 = player.getEU_distance(enemies[2].getXPoint(), enemies[2].getYPoint(), platform.getX(), platform.getY());
	float distance4 = player.getEU_distance(enemies[3].getXPoint(), enemies[3].getYPoint(), platform.getX(), platform.getY());
	float distance5 = player.getEU_distance(enemies[4].getXPoint(), enemies[4].getYPoint(), platform.getX(), platform.getY());

	enemies[0].updateGroundEnemy(distance1,delta);
	enemies[1].updateGroundEnemy(distance2,delta);
	//eTest.updateGroundEnemy();
	enemies[2].updateEnemyOnPlatform(distance3,delta);
	//enemies[0].updateAttack(distance);
	enemies[3].updateEnemyOnPlatform(distance4,delta);
	enemies[4].updateEnemyOnPlatform(distance5,delta);
	if ((enemies[0].getPlayerAttacked() || enemies[1].getPlayerAttacked() || enemies[2].getPlayerAttacked() || enemies[3].getPlayerAttacked() || enemies[4].getPlayerAttacked()) && !startWait)
	{
		enemies[0].setPlayerAttacked(false);
		enemies[1].setPlayerAttacked(false);
		enemies[2].setPlayerAttacked(false);
		enemies[3].setPlayerAttacked(false);
		enemies[4].setPlayerAttacked(false);
		player.decreaseHealth();
		startWait = true;
	}
	if (startWait) {
		if (wait()) {
			startWait = false;
		}
	}

	/**********/
	//switch boxes option so it can jump on box2
	if (enemies[2].getJumpFinished() && enemies[2].getXPos() > 90.0 && enemies[2].getXPos() < 120.0) {
		enemies[2].setOnBox2(true);
	}
	//switch boxes option so it can jump on box1
	if (enemies[2].getJumpFinished() && enemies[2].getXPos() >= 0.0 && enemies[2].getXPos() <= 30.0) {
		enemies[2].setOnBox1(true);
	}

	//switch boxes option so it can jump on box3
	if (enemies[3].getJumpFinished() && enemies[3].getXPos() >= 0.0 && enemies[3].getXPos() <= 80.0) {
		enemies[3].setOnBox3(true);
	}
	//switch boxes option so it can jump on box4
	if (enemies[3].getJumpFinished() && enemies[3].getXPos() > 108.0 && enemies[3].getXPos() < 160.0) {
		enemies[3].setOnBox4(true);
	}

	//switch boxes option so it can jump on box3
	if (enemies[4].getJumpFinished() && enemies[4].getXPos() >= 0.0 && enemies[4].getXPos() <= 50.0) {
		enemies[4].setOnBox4(true);
	}
	//switch boxes option so it can jump on box4
	if (enemies[4].getJumpFinished() && enemies[4].getXPos() < -30.0 && enemies[4].getXPos() > -112.0) {
		enemies[4].setOnBox3(true);
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
	enemies.push_back(e1);
	enemies.push_back(e2);
	enemies.push_back(e3);
	enemies.push_back(e4);
	enemies.push_back(e5);
	/*********************/
	enemies[0].setXSpeed(85);
	enemies[0].setWalkingLeft(true);
	
	enemies[1].setXSpeed(85);
	enemies[1].setWalkingLeft(true);

	enemies[2].setOnBox1(true);
	enemies[2].setXSpeed(30.0);
	enemies[2].setJumpSpeed(16.0);
	//enemies[2].setFallingSpeed(-10.0);

	enemies[3].setOnBox3(true);
	enemies[3].setXSpeed(30.0);
	enemies[3].setJumpSpeed(20.0);
	enemies[3].setFallingSpeed(5.0);

	enemies[4].setOnBox4(true);
	enemies[4].setXSpeed(30.0);
	enemies[4].setJumpSpeed(-10.0);
	enemies[4].setFallingSpeed(5.0);
	/*********************/
	glClearColor(0.0, 0.0, 0.0, 0.0);	//sets the clear colour to yellow
										//glClear(GL_COLOR_BUFFER_BIT) in the display function
										//will clear the buffer to this colour.
	
	boxes.push_back(box1);
	boxes.push_back(box2);
	boxes.push_back(box3);
	boxes.push_back(box4);

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

	player.charJumpTex[0] = loadPNG("Images/ninja/jump/Jump__001.png");
	player.charJumpTex[1] = loadPNG("Images/ninja/jump/Jump__009.png");
	
	enemies[0].enemyRunTex[0] = loadPNG("Images/SamuraiHeavy/Run0/Run0.png");
	enemies[0].enemyRunTex[1] = loadPNG("Images/SamuraiHeavy/Run0/Run1.png");
	enemies[0].enemyRunTex[2] = loadPNG("Images/SamuraiHeavy/Run0/Run2.png");
	enemies[0].enemyRunTex[3] = loadPNG("Images/SamuraiHeavy/Run0/Run3.png");
	enemies[0].enemyRunTex[4] = loadPNG("Images/SamuraiHeavy/Run0/Run4.png");
	enemies[0].enemyRunTex[5] = loadPNG("Images/SamuraiHeavy/Run0/Run5.png");
	enemies[0].enemyRunTex[6] = loadPNG("Images/SamuraiHeavy/Run0/Run6.png");
	enemies[0].enemyRunTex[7] = loadPNG("Images/SamuraiHeavy/Run0/Run7.png");
	enemies[0].enemyRunTex[8] = loadPNG("Images/SamuraiHeavy/Run0/Run8.png");
	enemies[0].enemyRunTex[9] = loadPNG("Images/SamuraiHeavy/Run0/Run9.png");

	enemies[0].enemyAttackTex[0] = loadPNG("Images/SamuraiHeavy/Attack/Attack0.png");
	enemies[0].enemyAttackTex[1] = loadPNG("Images/SamuraiHeavy/Attack/Attack1.png");
	enemies[0].enemyAttackTex[2] = loadPNG("Images/SamuraiHeavy/Attack/Attack2.png");
	enemies[0].enemyAttackTex[3] = loadPNG("Images/SamuraiHeavy/Attack/Attack3.png");
	enemies[0].enemyAttackTex[4] = loadPNG("Images/SamuraiHeavy/Attack/Attack4.png");
	enemies[0].enemyAttackTex[5] = loadPNG("Images/SamuraiHeavy/Attack/Attack5.png");
	enemies[0].enemyAttackTex[6] = loadPNG("Images/SamuraiHeavy/Attack/Attack6.png");
	enemies[0].enemyAttackTex[7] = loadPNG("Images/SamuraiHeavy/Attack/Attack7.png");
	enemies[0].enemyAttackTex[8] = loadPNG("Images/SamuraiHeavy/Attack/Attack8.png");
	enemies[0].enemyAttackTex[9] = loadPNG("Images/SamuraiHeavy/Attack/Attack9.png");

	enemies[4].enemyRunTex[0] = enemies[3].enemyRunTex[0] = enemies[2].enemyRunTex[0] = enemies[1].enemyRunTex[0] = enemies[0].enemyRunTex[0];
	enemies[4].enemyRunTex[1] = enemies[3].enemyRunTex[1] = enemies[2].enemyRunTex[1] = enemies[1].enemyRunTex[1] = enemies[0].enemyRunTex[1];
	enemies[4].enemyRunTex[2] = enemies[3].enemyRunTex[2] = enemies[2].enemyRunTex[2] = enemies[1].enemyRunTex[2] = enemies[0].enemyRunTex[2];
	enemies[4].enemyRunTex[3] = enemies[3].enemyRunTex[3] = enemies[2].enemyRunTex[3] = enemies[1].enemyRunTex[3] = enemies[0].enemyRunTex[3];
	enemies[4].enemyRunTex[4] = enemies[3].enemyRunTex[4] = enemies[2].enemyRunTex[4] = enemies[1].enemyRunTex[4] = enemies[0].enemyRunTex[4];
	enemies[4].enemyRunTex[5] = enemies[3].enemyRunTex[5] = enemies[2].enemyRunTex[5] = enemies[1].enemyRunTex[5] = enemies[0].enemyRunTex[5];
	enemies[4].enemyRunTex[6] = enemies[3].enemyRunTex[6] = enemies[2].enemyRunTex[6] = enemies[1].enemyRunTex[6] = enemies[0].enemyRunTex[6];
	enemies[4].enemyRunTex[7] = enemies[3].enemyRunTex[7] = enemies[2].enemyRunTex[7] = enemies[1].enemyRunTex[7] = enemies[0].enemyRunTex[7];
	enemies[4].enemyRunTex[8] = enemies[3].enemyRunTex[8] = enemies[2].enemyRunTex[8] = enemies[1].enemyRunTex[8] = enemies[0].enemyRunTex[8];
	enemies[4].enemyRunTex[9] = enemies[3].enemyRunTex[9] = enemies[2].enemyRunTex[9] = enemies[1].enemyRunTex[9] = enemies[0].enemyRunTex[9];

	
	enemies[4].enemyAttackTex[0] = enemies[3].enemyAttackTex[0] = enemies[2].enemyAttackTex[0] = enemies[1].enemyAttackTex[0] = enemies[0].enemyAttackTex[0];
	enemies[4].enemyAttackTex[1] = enemies[3].enemyAttackTex[1] = enemies[2].enemyAttackTex[1] = enemies[1].enemyAttackTex[1] = enemies[0].enemyAttackTex[1];
	enemies[4].enemyAttackTex[2] = enemies[3].enemyAttackTex[2] = enemies[2].enemyAttackTex[2] = enemies[1].enemyAttackTex[2] = enemies[0].enemyAttackTex[2];
	enemies[4].enemyAttackTex[3] = enemies[3].enemyAttackTex[3] = enemies[2].enemyAttackTex[3] = enemies[1].enemyAttackTex[3] = enemies[0].enemyAttackTex[3];
	enemies[4].enemyAttackTex[4] = enemies[3].enemyAttackTex[4] = enemies[2].enemyAttackTex[4] = enemies[1].enemyAttackTex[4] = enemies[0].enemyAttackTex[4];
	enemies[4].enemyAttackTex[5] = enemies[3].enemyAttackTex[5] = enemies[2].enemyAttackTex[5] = enemies[1].enemyAttackTex[5] = enemies[0].enemyAttackTex[5];
	enemies[4].enemyAttackTex[6] = enemies[3].enemyAttackTex[6] = enemies[2].enemyAttackTex[6] = enemies[1].enemyAttackTex[6] = enemies[0].enemyAttackTex[6];
	enemies[4].enemyAttackTex[7] = enemies[3].enemyAttackTex[7] = enemies[2].enemyAttackTex[7] = enemies[1].enemyAttackTex[7] = enemies[0].enemyAttackTex[7];
	enemies[4].enemyAttackTex[8] = enemies[3].enemyAttackTex[8] = enemies[2].enemyAttackTex[8] = enemies[1].enemyAttackTex[8] = enemies[0].enemyAttackTex[8];
	enemies[4].enemyAttackTex[9] = enemies[3].enemyAttackTex[9] = enemies[2].enemyAttackTex[9] = enemies[1].enemyAttackTex[9] = enemies[0].enemyAttackTex[9];
	
	boxes[0].platformTexture = loadPNG("Images/box_platform.png");
	boxes[1].platformTexture = loadPNG("Images/box_platform.png");
	boxes[2].platformTexture = loadPNG("Images/box_platform.png");
	boxes[3].platformTexture = loadPNG("Images/box_platform.png");
	platform.platform_texture = loadPNG("Images/platform.png");
	landscape.platformTexture = loadPNG("Images/3.png");

}
void processKeys()
{
	if (!playerIsKilled()) {
		if (keys[VK_UP]) {
			player.moveUp();
		}

		if (keys[VK_DOWN]) {
			player.moveDown();
		}

		if (keys[VK_LEFT]) {
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

		if (keys[VK_RIGHT])
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

		if (keys['A']  && ( (attackTimer % 250 == 0) && player.getCanThrow()) ) {
			//attackTimer = 0;
			player.ThrowAttack();
			//get the coordinates of the new kunai spawn only when the fire is true
			//so the coordinates will not mix up with the character's translation
			if (player.getFire()) {
				kunaiDirection = player.getWalkingLeft();
				kunaiXPosition = -platform.getX() + player.getPosX();
				kunaiYPosition = player.getPosY();
				player.setPosInfo(false);
			}
		}
		else {
			player.setFire(false);
			player.setPosInfo(false);
		}
		attackTimer++;
	}
}

/**************** END OPENGL FUNCTIONS *************************/

//WIN32 functions
LRESULT	CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);	// Declaration For WndProc
void KillGLWindow();									// releases and destroys the window
bool CreateGLWindow(char* title, int width, int height); //creates the window
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int);  // Win32 main function

//win32 global variabless
HDC			hDC = NULL;		// Private GDI Device Context
HGLRC		hRC = NULL;		// Permanent Rendering Context
HWND		hWnd = NULL;		// Holds Our Window Handle
HINSTANCE	hInstance;		// Holds The Instance Of The Application


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
