//#pragma once

//#include <windows.h>		// Header file for Windows
//#include <iostream>
//#include <gl\glu.h>			// Header file for the GLu32 Library
//#include <gl\gl.h>			// Header file for the OpenGL32 Library
//
//#include "Platform.h"


#include "Header.h"
//#include "Player.h"
#include <iostream>
#include <vector>
class Player {
private:
	float x = 50.0;
	float y = 8.0;
	float width = 10.0;
	float height = 22.0;

	float leftX = x;
	float bottomY = y;
	float topY = y + height;
	float rightX = leftX + width;
	float posX;
	float posY;	
	float playerX = 0.0;
	float previousX = 0.0;
	float xspeed = 220.0f;
	float velocity;
	float maxHeight = 200.0;
	float time = 0.0;
	float currentTime;
	float previousTime = 0.0;	
	float scaler = 0.4f;
	//int attackTimer = 0;
	int counter = 0;
	int waitCounter = 0;
	int magazineCounter = 0;
	int maxKunai = 20;
	int enemiesKilled = 0;
	int frameCounter = 0;

		/*textures*/
	int glideTextureCounter = 0;
	int throwTextureCounter = 0;
	int attackTextureCounter = 2;
	int deadTextureCounter = 0;
	int idleTextureCounter = 0;
	int walkTextureCounter = 0;
	int jumpTextureCounter = 0;
	int idleTimer = 0;
	int walkTimer = 0;
	int jumpTimer = 0;
	int deadTimer = 0;
	int throwTimer = 0;
	int glideTimer = 0;
	int attackMeleeTimer = 0;
	int healthBarCounter = 0;
		/**********/

	bool dead = false;
	bool fire = false;
	bool alive = true;
	bool playerAttacked = false;
	bool jumping = false;	//check if character is jumping
	bool falling = false;	//checks if the character is falling
	bool canJump = true;
	bool isOnBox = false;
	bool onBox1 = false;
	bool onBox2 = false;
	bool onBox3 = false;
	bool onBox4 = false;
	bool onBox5 = false;
	bool walking = true;
	bool running = false;
	bool gliding = true;
	bool walkingLeft = false;
	bool walkingRight = false;
	bool canDecrease = true;
	bool maxMagazine = false;
	bool weaponThrew = false;
	bool isThrowing = false;
	bool attacking = false;
	bool firstThrow = true;
	bool posInfo = false;
	bool throwing = false;
	bool dashAttackFinished = false;
	bool oneMoreDash = false;
	CollisionBox col_box;
	Box healthBar;
	Weapon kunai;
	std::vector<Weapon> magazine;
public:
	bool canDash = false;
	bool throwFinished = false;
	GLuint charIdle[10];
	GLuint charDeadTex[10];
	GLuint charRunTex[10];
	GLuint charThrowTex[10];
	GLuint charGlideTex[10];
	GLuint charAttackTex[10];
	GLuint charJumpTex[2];
	GLuint healthBarTex[4];

	GLfloat getPosX();
	GLfloat getPosY();
	GLfloat getX();
	GLfloat getY();
	Player();
	~Player();
	int getKills();
	int getHealth();
	int getKunaiCounter();
	void initMagazine();
	//void removeMagazine();
	//void moveDown(void);
	void moveRight(float delta);
	void moveUp(void);
	void moveLeft(float delta);
	void moveDown(void);
	void ThrowAttack();
	void setPosX(float x);
	void setPosY(float y);
	void setPosition(void);
	void setJump(bool x);
	void setFalling(bool x);
	void setOnBox(bool x);
	void setCanJump(bool x);
	void setOnBox1(bool x);
	void setOnBox2(bool x);
	void setOnBox3(bool x);
	void setOnBox4(bool x);
	void setOnBox5(bool x);
	void setWalking(bool x);
	void setRunning(bool x);
	void setWalkingLeft(bool left);
	void setWalkingRight(bool right);
	void setAlive(bool alive);
	void setPlayerAttacked(bool attack);
	void setFire(bool x);
	void setPlayerX(float px);
	void setThrowing(bool x);
	void setPosInfo(bool x);
	void setGliding(bool glide);
	void setAttacking(bool attack);
	void setOneMoreDash(bool x);
	void setKills(int x);
	//void setWeaponTex(GLuint tex);
	void addToX(float x);
	void addToY(float y);
	void increaseHealth();
	
	/*DRAW AND UPDATES*/
	void drawCollisionBox();
	void drawCharacter();
	void drawHealthBar();
	void drawWeapon(bool kunaiDirection, float px, float py, float delta, std::vector<Enemy*> enemies, std::vector<Enemy*> enemiesAI);
	void update(float delta, float platformX, bool jumpPressed,std::vector<Box> boxes);
	void updateWeapon();
	void updateMeleeLeft(float delta);
	void updateMeleeRight(float delta);
	void updateMeleeAttack(bool playerLeftDirection, float meleeXPos, float meleeYPos, float delta, std::vector<Enemy*> enemies);
	void updateMeleeAttackAI(bool playerLeftDirection, float px, float py, float delta, std::vector<Enemy*> enemies);
	void platformsCollisionUpdate(float platformX, bool jumpPressed, std::vector<Box> boxes);
	bool checkBoxJumping(float platformX, std::vector<Box> boxes);
	bool checkBoxFalling(float platformX, std::vector<Box> boxes);
	bool checkOnBoxUpdate(float platformX);
	void sideCollision(float platformX, std::vector<Box> boxes);
	void jump();
	
	bool wait();
	bool checkFloor();
	bool isJumping();
	bool isFalling();
	bool isAlive();
	bool getOnBox();
	bool getOnBox1();
	bool getOnBox2();
	bool getOnBox3();
	bool getOnBox4();
	bool getOnBox5();
	bool getWalking();
	bool getRunning();
	bool getWalkingLeft();
	bool getWalkingRight();
	bool getPlayerAttacked();
	bool getFire();
	bool getThrowing();
	bool decreaseHealth();
	bool getPosInfo();
	bool getGliding();
	bool getAttacking();
	bool getDashAttackFinished();
	bool getOneMoreDash();
	float getWidth();
	float getHeight();
	float getEU_distance(float enemyX, float enemyY, float platformX, float platformY);


	Weapon getWeapon();
	std::vector<Weapon> getMagazine();
};



inline void Player::moveDown(void)
{
	posY -= 0.2f;
}

inline void Player::moveUp(void)
{
	posY += 0.2f;
}

inline void Player::moveLeft(float delta)
{
	posX -= (xspeed * delta);
}

inline void Player::moveRight(float delta)
{
	posX += (xspeed * delta);
}


inline bool Player::decreaseHealth() {
	this->healthBarCounter++;
	if (healthBarCounter >= 3) {
		healthBarCounter = 3;
		alive = false;
	}
	return false;
}

inline void Player::increaseHealth() {
	this->healthBarCounter--;
	if (healthBarCounter < 0) {
		healthBarCounter = 0;
	}
}

inline void Player::initMagazine() {
	for (int i = 0; i < 20; i++) {
		//magazine.push_back(kunai);
	}
}

/******************GETTERS***********************/

inline bool Player::getOnBox()
{
	return this->isOnBox;
}

inline GLfloat Player::getPosX()
{
	return posX;
}

inline GLfloat Player::getPosY()
{
	return posY;
}

inline GLfloat Player::getX() {
	return this->leftX;
}

inline GLfloat Player::getY() {
	return this->bottomY;
}

inline bool Player::isJumping()
{
	return jumping;
}

inline bool Player::isFalling()
{
	return falling;
}

inline bool Player::getOnBox1()
{
	return this->onBox1;
}

inline bool Player::getOnBox2()
{
	return this->onBox2;
}

inline bool Player::getOnBox3()
{
	return this->onBox3;
}

inline bool Player::getOnBox4()
{
	return this->onBox4;
}

inline bool Player::getOnBox5()
{
	return this->onBox5;
}

inline bool Player::getWalking()
{
	return this->walking;
}

inline bool Player::getWalkingLeft()
{
	return this->walkingLeft;
}

inline bool Player::getWalkingRight()
{
	return this->walkingRight;
}

inline float Player::getWidth() {
	return this->width;
}

inline float Player::getHeight() {
	return this->height;
}

inline float Player::getEU_distance(float enemyX, float enemyY, float platformX,float platformY) {
	float pCurrentX = posX - platformX + 50;
	float pCurrentY = (posY + height / 2) * 2;
	return sqrt(pow(enemyX - pCurrentX, 2) + pow(enemyY - pCurrentY, 2));
}

inline bool Player::isAlive() {
	return this->alive;
}

inline bool Player::getPlayerAttacked() {
	return this->playerAttacked;
}

inline bool Player::getFire() {
	return this->fire;

}

inline bool Player::getRunning() {
	return this->running;
}

inline Weapon Player::getWeapon() {
	return this->kunai;
}

inline bool Player::getThrowing() {
	return this->throwing;
}

inline bool Player::getPosInfo() {
	return this->posInfo;
}

inline bool Player::getGliding() {
	return this-> gliding;
}

inline std::vector<Weapon> Player::getMagazine() {
	return this->magazine;
}

inline bool Player::getAttacking() {
	return this->attacking;
}

inline bool Player::getOneMoreDash() {
	return this->oneMoreDash;
}

inline int Player::getKills() {
	return this->enemiesKilled;
}

inline int Player::getHealth() {
	return this->healthBarCounter;
}

inline int Player::getKunaiCounter() {
	return 10 - magazineCounter;
}
/**********************************************/

/****************SETTERS***********************/

inline void Player::setCanJump(bool x)
{
	this->canJump = x;
}

inline void Player::setJump(bool x)
{
	this->jumping = x;
}

inline void Player::setPosition(void)
{
	this->posY = 0;
}

inline void Player::setPosX(float x)
{
	posX = x;
}

inline void Player::setPosY(float y)
{
	posY = y;
}

inline void Player::setFalling(bool x)
{
	this->falling = x;
}

inline void Player::setOnBox(bool x)
{
	this->isOnBox = x;
}

inline void Player::setOnBox1(bool x)
{
	this->onBox1 = x;
	if (x) onBox2 = onBox3 = onBox4 = onBox5 = false;
}

inline void Player::setOnBox2(bool x)
{
	this->onBox2 = x;
	if (x)onBox1 = onBox3 = onBox4 = onBox5 = false;
}

inline void Player::setOnBox3(bool x)
{
	this->onBox3 = x;
	if (x) onBox1 = onBox2 = onBox4 = onBox5 = false;
}

inline void Player::setOnBox4(bool x)
{
	this->onBox4 = x;
	if (x) onBox1 = onBox2 = onBox3 = onBox5 = false;
}

inline void Player::setOnBox5(bool x)
{
	this->onBox5 = x;
	if(x) onBox1 = onBox2 = onBox3 = onBox4 = false;
}

inline void Player::setWalking(bool x)
{
	this->walking = x;
}

inline void Player::setWalkingLeft(bool left)
{
	this->walkingLeft = left;
}

inline void Player::setWalkingRight(bool right)
{
	this->walkingRight = right;
}

inline void Player::setAlive(bool alive) {
	this->alive = alive;
}

inline void Player::setPlayerAttacked(bool attack) {
	this->playerAttacked = attack;
}

inline void Player::setFire(bool x) {
	this->fire = x;
}

inline void Player::setRunning(bool x) {
	this->running = x;
	if (x) walking = false;
}

inline void Player::setPlayerX(float px) {
	this->playerX = px;
}

inline void Player::setThrowing(bool x) {
	this->isThrowing = x;
}

inline void Player::setPosInfo(bool x) {
	this->posInfo = x;
}

inline void Player::setGliding(bool glide) {
	this->gliding = glide;
}

inline void Player::setAttacking(bool attack) {
	this->attacking = attack;
}

inline void Player::setOneMoreDash(bool x) {
	this->oneMoreDash = x;
}

inline void Player::setKills(int x) {
	this->enemiesKilled = x;
}

inline bool Player::wait() {
	waitCounter++;
	if (waitCounter > 100) {
		waitCounter = 0;
		return true;
	}
	else return false;
}

/**********************************************/
