#ifndef WATER_H_
#define WATER_H_

#include <Box2D/Common/b2Math.h>
#include "../../../../utils/ParserYaml.h"

class b2Body;
class b2Vec2;
class b2World;
class Water{
public:
	Water(float level, b2World* myWorld);
	virtual ~Water();


private:
	b2Body* body;
	b2World* myWorld;
	float waterLevel;
};


#endif 