#ifndef MISSILE2DBAZOOKA_H_
#define MISSILE2DBAZOOKA_H_
#include "Missile2d.h"

#define BULLET_RADIUS 0.4f

class Missile2dBazooka : public Missile2d{


	public:
		Missile2dBazooka(ElementType type, float posX, float posY, float angle_x, float angle_y, float fuerzaDisparo, b2World *myWorld, GameElement *modelElement);
		Missile2dBazooka();
		virtual ~Missile2dBazooka();
		virtual void animate( float time );
		virtual void explode( );

};


#endif