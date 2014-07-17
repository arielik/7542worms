#ifndef MISSILE2DBURRO_H_
#define MISSILE2DBURRO_H_
#include "Missile2d.h"

#define BULLET_RADIUS 0.4f

class MissileBurro2d : public Missile2d{


	public:
		MissileBurro2d(ElementType type, float posX, float posY, float angle_x, float angle_y, float fuerzaDisparo, b2World *myWorld, GameElement *modelElement);
		MissileBurro2d();
		virtual ~MissileBurro2d();
		virtual void animate( float time );
		virtual void explode( );
};


#endif