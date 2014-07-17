#ifndef MISSILE2DGRENADE_H_
#define MISSILE2DGRENADE_H_
#include "Missile2d.h"

#define BULLET_RADIUS 0.4f

class Missile2dGrenade : public Missile2d{


	public:
		Missile2dGrenade(ElementType type, float posX, float posY, float angle_x, float angle_y, float fuerzaDisparo, b2World *myWorld, GameElement *modelElement);
		Missile2dGrenade();
		virtual ~Missile2dGrenade();
		virtual void animate( float time );
		virtual void explode( );

};


#endif