#ifndef WORM_H_
#define WORM_H_

#include "../GameElement.h"
#include "../Physics/Bodies/Worm/Worm2d.h"
#define MAX_WORM_LIFE 100

using namespace std;

class Worm : public GameElement{

protected:

bool jumping;
bool jumpingRight;
bool jumpingLeft;
bool movingRight;
bool movingLeft;
bool selected;
bool stopped;



public:
	Worm();
//Worm(int id, ElementType type, float posX, float posY, float degrees, float h, float w, float mass, bool isFixed);
Worm(int id, std::string playerID, ElementType type, float posX, float posY, float degrees, float h, float w, float mass, bool isFixed);



void stop();
void shoot();
void jump();
void jumpRight();
void jumpLeft();
void moveLeft();
void moveRight();
void stopMoving();
void weaponedLeft(int weaponid);
void weaponedRight(int weaponid);

bool isSelected();
bool isJumping();
bool isJumpingRight(){ return this->jumpingRight; }
bool isJumpingLeft(){ return this->jumpingLeft; }
bool isMovingRight();
bool isMovingLeft();
bool isStopped();




bool weaponRight;
bool weaponLeft;


void select();
void deselect();
virtual ~Worm();



};


#endif
