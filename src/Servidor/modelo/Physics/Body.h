#ifndef CUERPO_H_
#define CUERPO_H_

//#include "../../../utils/Vec2.h"
#include "../GameElement.h"

#include <Box2D/Common/b2Math.h>
#include <Box2D/Box2D.h>
#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f

/*
­ tipo:   rect
  x:      5
  y:      90
  ancho:  2
  alto:   1
  rot:    45
  masa:   3
  estatico:   no
  */


class b2Body;
class b2Vec2;
class b2World;

 enum _entityCategory {
    WORM_CAT =          0x0001,
    TUMB_CAT =     0x0002,
    TERRAIN_CAT =        0x0004,
    MISSIL_CAT = 0x0008,
    WATER_CAT =    0x0010,
  };

class Body {
public:
	Body();
	Body(ElementType type, b2Body *body, int posX, int posY, float h, 
		float w, float masa, float angle, b2World *myWorld);

	virtual ~Body();
	virtual b2Body* getBody(){ return this->body; };
	virtual void touch(Body* touchingWith, b2World* mundo){};
	virtual void animate(){};

	virtual void setPosition(float x, float y,float rot){};
	float getMass();
	bool damaged;

	float width;
	float height;
	ElementType type;
	b2Body* body;
	float angle;
	float masa;
	b2Vec2 center;
	b2World* myWorld;

	// Posicion original X,Y cada 4 pasos se actualiza
	float ox;
	float oy;
	
};

#endif 
