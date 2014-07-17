#ifndef MISSILE2DSHEEP_H_
#define MISSILE2DSHEEP_H_
#include "Missile2d.h"

#define BULLET_RADIUS 0.4f

class MissileSheep2d : public Missile2d{


	public:
		MissileSheep2d(ElementType type, float posX, float posY, float angle_x, float angle_y, float fuerzaDisparo, b2World *myWorld, GameElement *modelElement);
		MissileSheep2d();
		virtual ~MissileSheep2d();
		virtual void animate( float time );
		virtual void explode( );
		bool left;
		bool right;
		bool detention;
};


#endif