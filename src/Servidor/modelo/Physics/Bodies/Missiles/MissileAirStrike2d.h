#ifndef MISSILE2DAIRSTRIKE_H_
#define MISSILE2DAIRSTRIKE_H_
#include "Missile2d.h"

#define BULLET_RADIUS 0.4f

class MissileAirStrike2d : public Missile2d{


	public:
		MissileAirStrike2d(ElementType type, float posX, float posY, float angle_x, float angle_y, float fuerzaDisparo, b2World *myWorld, GameElement *modelElement);
		MissileAirStrike2d();
		virtual ~MissileAirStrike2d();
		virtual void animate( float time );
		virtual void explode( );
};


#endif