#ifndef PELOTA_H_
#define PELOTA_H_


#include "../Body.h"

class Pelota: public Body{
public:
	Pelota(b2World* myWorld);
	virtual ~Pelota();
	void animate();

private:
	b2Body* createBody();
};


#endif 
