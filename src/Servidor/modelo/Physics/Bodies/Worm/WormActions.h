#ifndef WORMACTIONS_H_
#define WORMACTIONS_H_
#include "Worm2d.h"

using namespace std;

class Worm2d;
class WormActions{

protected:
Worm2d* aWorm2d;
float deltaMovement;
int jumpTimeOut;

public:
WormActions(Worm2d* worm2d);
void jump();
void jumpLeft();
void jumpRight();
void moveLeft();
void moveRight();
virtual ~WormActions();
void updateJumpTimeout(){ this->jumpTimeOut = this->jumpTimeOut -1; }

};


#endif
