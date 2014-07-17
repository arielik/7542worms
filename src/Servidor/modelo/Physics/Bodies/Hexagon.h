#ifndef HEXAGON_H_
#define HEXAGON_H_


#include "../Body.h"

class Hexagon: public Body{
public:
	Hexagon(ElementType type, float posX, float posY, float scale,
			float masa, float angle, b2World *myWorld, GameElement* modelElement, bool fixed);
	virtual ~Hexagon();
	std::list<std::pair<float,float>> GetVertex();
	void animate();
	void touch(Body* touchingWith, b2World* mundo);
	void setPosition(float x, float y,float rot);

private:
	b2Body* createBody();
};


#endif 