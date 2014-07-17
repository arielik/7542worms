#ifndef MISSILE2DDYNAMITE_H_
#define MISSILE2DDYNAMITE_H_
#include "Missile2d.h"

#define BULLET_RADIUS 0.4f

class MissileDynamite2d : public Missile2d{


	public:
		MissileDynamite2d(ElementType type, float posX, float posY, float angle_x, float angle_y, float fuerzaDisparo, b2World *myWorld, GameElement *modelElement);
		MissileDynamite2d();
		virtual ~MissileDynamite2d();
		virtual void animate( float time );
		virtual void explode( );
};


#endif