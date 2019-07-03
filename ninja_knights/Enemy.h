#pragma once
class Enemy
{
private:
	float leftX, bottomY, rightX, topY, width, height;
	float xPos = 0.0f;
	float yPos = 0.0f;
	float xspeed = 0.0;
	float fallingSpeed = 80.0f;
	float velocity = 100.0f + this->yPos;	//gives initial velocity
	float maxHeight = 100;
	float jumpSpeed = 300.0;
	float boxFloor1 = 0.0;
	float boxFloor2 = 0.0;
	float onPlatformMap = 0.0;
	
	int walkTimer = 0;
	int attackTimer = 0;
	int walkTextureCounter = 0;
	int attackTextureCounter = 0;
	float temp_eu;
	CollisionBox col_box;
	bool firstBar = true;
	bool secondBar = true;
	bool thirdBar = true;

	bool canJump = true;
	bool jumping = false;
	bool falling = false;
	bool walking = true;
	bool walkingLeft = false;
	bool onBox1 = false;
	bool onBox2 = false;
	bool onBox3 = false;
	bool onBox4 = false;
	bool goLeft = false;
	bool goRight = false;
	bool edgeHit = false;
	bool needJump = false;
	bool wallHit = false;
	bool collide = false;
	bool leftWallHit = false;
	bool rightWallHit = false;
	bool finishedJump = false;
	bool attack = false;
	bool attackFinished = false;
	bool playerAttacked = false;
	bool killedPlayer = false;
	bool alive = true;
public:
	Enemy();
	Enemy(float _x, float _y, float _width, float _height);
	Enemy(float _x, float _y, float _width, float _height, float _bh1, float _bh2);

	GLuint enemyRunTex[10];
	GLuint enemyAttackTex[10];
	GLuint enemyIdle;
	CollisionBox getCollisionBox();

	void drawEnemy();
	void drawEnemyLine(float x, float y, float r, float g, float b);
	void drawEnemyLeftLine(float x, float y, float r, float g, float b);
	void drawEnemyRightLine(float x, float y, float r, float g, float b);
	void drawEnemyCollisionLine(float x, float y, float r, float g, float b);
	void drawCollisionBox(float x, float y);

	//void update();
	void updateGroundEnemy(float distance,float delta);
	void updateEnemyOnPlatform(float distance,float delta);
	void updateAttack(float distance,float delta);
	void jump(float delta);
	void jumpRight(float delta);
	void jumpLeft(float delta);
	//void checkPlatform();
	void setXPos(float xpos);
	void setYPos(float ypos);
	void setJump(bool jumping);
	void setCanJump(bool jump);
	void setNeedJump(bool jump);
	void setWallHit(bool hit);
	void setWalkingLeft(bool walk);
	void setXSpeed(float speed);
	void setCollide(bool collide);
	void setLeftWallHit(bool left);
	void setRightWallHit(bool right);
	void setEdgeHit(bool hit);
	void setOnBox1(bool x);
	void setOnBox2(bool x);
	void setOnBox3(bool x);
	void setOnBox4(bool x);
	void setGoLeft(bool left);
	void setGoRight(bool right);
	void setJumpSpeed(float speed);
	void setPlayerAttacked(bool attacked);
	void setFallingSpeed(float speed);
	void setAlive(bool x);

	float getXPos();
	float getYPos();
	float getX();
	float getY();
	float getHeight();
	float getWidth();
	float getXPoint();
	float getYPoint();
	float getXSpeed();

	bool wait();
	bool getOnBox1();
	bool getOnBox2();
	bool getOnBox3();
	bool getOnBox4();
	bool getWallHit();
	bool getLeftWallHit();
	bool getRightWallHit();
	bool getGoLeft();
	bool getGoRight();
	bool getJumpFinished();
	bool getPlayerAttacked();
	bool getKilledPlayer();
	bool getAlive();
};


/****************GETTERS***********************/
inline float Enemy::getXPos()
{
	return this->xPos;
}

inline float Enemy::getYPos()
{
	return this->yPos;
}

inline float Enemy::getX()
{
	return this->leftX;
}

inline float Enemy::getY()
{
	return this->bottomY;
}

inline float Enemy::getYPoint() {
	return bottomY + yPos + height/2;
}

inline float Enemy::getXPoint() {
	return leftX + xPos + width/2;
}

inline bool Enemy::getWallHit() {
	return this->wallHit;
}

inline bool Enemy::getLeftWallHit() {
	return this->leftWallHit;
}

inline bool Enemy::getRightWallHit() {
	return this->rightWallHit;
}

inline bool Enemy::getOnBox1(){
	return this->onBox1;

}

inline bool Enemy::getOnBox2() {
	return this->onBox2;
}

inline bool Enemy::getOnBox3() {
	return this->onBox3;
}

inline bool Enemy::getOnBox4() {
	return this->onBox4;
}

inline bool Enemy::getGoRight() {
	return this->goRight;
}

inline bool Enemy::getGoLeft() {
	return this->goLeft;
}

inline bool Enemy::getJumpFinished() {
	return this->finishedJump;
}

inline CollisionBox Enemy::getCollisionBox() {
	return this->col_box;
}

inline float Enemy::getHeight() {
	return this->height;
}

inline float Enemy::getWidth() {
	return this->width;
}

inline bool Enemy::getKilledPlayer() {
	return this->killedPlayer;
}

inline bool Enemy::getPlayerAttacked() {
	return this->playerAttacked;
}

inline float Enemy::getXSpeed() {
	return this->xspeed;
}

inline bool Enemy::getAlive() {
	return this->alive;
}
/**********************************************/

/****************SETTERS***********************/
inline void Enemy::setXPos(float xpos) {
	this->xPos += xpos;
}

inline void Enemy::setYPos(float ypos) {
	this->yPos += ypos;
}

inline void Enemy::setWallHit(bool hit) {
	this->wallHit = hit;
}

inline void Enemy::setXSpeed(float speed) {
	this->xspeed = speed;
}

inline void Enemy::setCollide(bool collide) {
	this->collide = collide;
}

inline void Enemy::setLeftWallHit(bool left) {
	this->leftWallHit = left;
}

inline void Enemy::setRightWallHit(bool right) {
	this->rightWallHit = right;
}

inline void Enemy::setEdgeHit(bool hit) {
	this->edgeHit = hit;
}

inline void Enemy::setCanJump(bool jump) {
	this->canJump = jump;
}

inline void Enemy::setJump(bool jumping) {
	this->jumping = jumping;
}

inline void Enemy::setNeedJump(bool jump) {
	this->needJump = jump;
}

inline void Enemy::setOnBox1(bool x) {
	this->onBox1 = x;
	if (x) onBox2 = onBox3 = onBox4 = false;
}

inline void Enemy::setOnBox2(bool x) {
	this->onBox2 = x;
	if (x) onBox1 = onBox3 = onBox4 = false;
}

inline void Enemy::setOnBox3(bool x) {
	this->onBox3 = x;
	if (x) onBox1 = onBox2 = onBox4 = false;
}

inline void Enemy::setOnBox4(bool x) {
	this->onBox4 = x;
	if (x) onBox1 = onBox2 = onBox3 = false;
}

inline void Enemy::setGoLeft(bool left) {
	this->goLeft = left;
	if (left) {
		goRight = false;
	}
}

inline void Enemy::setGoRight(bool right) {
	this->goRight = right;
	if (right) {
		goLeft = false;
	}
}

inline void Enemy::setJumpSpeed(float speed) {
	this->jumpSpeed = speed;
}

inline void Enemy::setWalkingLeft(bool left) {
	this->walkingLeft = left;
}

inline void Enemy::setPlayerAttacked(bool attacked) {
	this->playerAttacked = attacked;
}

inline void Enemy::setFallingSpeed(float speed) {
	this->fallingSpeed = speed;
}

inline void Enemy::setAlive(bool x) {
	this->alive = x;
}
/**********************************************/