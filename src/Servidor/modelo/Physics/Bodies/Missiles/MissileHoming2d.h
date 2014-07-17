#ifndef MISSILE2DHOMING_H_
#define MISSILE2DHOMING_H_
#include "Missile2d.h"

#define BULLET_RADIUS 0.4f

class MissileHoming2d : public Missile2d{


	public:
		MissileHoming2d(ElementType type, float posX, float posY, float angle_x, float angle_y, float fuerzaDisparo, b2World *myWorld, GameElement *modelElement);
		MissileHoming2d();
		virtual ~MissileHoming2d();
		virtual void animate( float time );
		virtual void explode( );
};


#endif