#ifndef CUADRADO_H_
#define CUADRADO_H_

#include <math.h>
#include "../../../../utils/Log.h"
#include "../Body.h"


class Cuadrado: public Body{
public:
	Cuadrado(ElementType type, float posX, float posY, float h, 
		float w, float masa, float angle, b2World *myWorld, GameElement* modelElement, bool fixed);
	virtual ~Cuadrado();
	std::list<std::pair<float,float>> GetVertex();
	virtual void animate();
	void touch(Body* touchingWith, b2World* mundo);
	void setPosition(float x, float y,float rot);


private:
	b2Body* createBody();
};


#endif 
