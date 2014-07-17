#ifndef WORM2D_H_
#define WORM2D_H_
#include "../../../Entities/Worm.h"
#include "../Cuadrado.h"
#include "WormActions.h"

using namespace std;

class WormActions;
class Worm2d : public Body{

protected:
WormActions* aWormActions;

public:
Worm2d(ElementType type, float posX, float posY, float h, 
		float w, float masa, float angle, b2World *myWorld, GameElement *modelElement, bool fixed);
void jump();
void jumpRight();
void jumpLeft();
void moveLeft();
void moveRight();
void animate();
void animate(bool update);
virtual ~Worm2d();
void makeTumb();




};


#endif
