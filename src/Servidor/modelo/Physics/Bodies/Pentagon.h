#ifndef PENTAGON_H_
#define PENTAGON_H_


#include "../Body.h"

class Pentagon: public Body{
public:
	Pentagon(ElementType type, float posX, float posY, float scale,
			float masa, float angle, b2World *myWorld, GameElement* modelElement, bool fixed);
	virtual ~Pentagon();
	std::list<std::pair<float,float>> GetVertex();
	void animate();
	void touch(Body* touchingWith, b2World* mundo);
	void setPosition(float x, float y,float rot);
private:
	b2Body* createBody();
};


#endif 