#ifndef MISSILE2DBANANA_H_
#define MISSILE2DBANANA_H_
#include "Missile2d.h"

#define BULLET_RADIUS 0.4f

class MissileBanana2d : public Missile2d{


	public:
		MissileBanana2d(ElementType type, float posX, float posY, float angle_x, float angle_y, float fuerzaDisparo, b2World *myWorld, GameElement *modelElement);
		MissileBanana2d();
		virtual ~MissileBanana2d();
		virtual void animate( float time );
		virtual void explode( );
};


class MissileBananita2d : public Missile2d{


	public:
		MissileBananita2d(ElementType type, float posX, float posY, float angle_x, float angle_y, float fuerzaDisparo, b2World *myWorld, GameElement *modelElement);
		MissileBananita2d();
		virtual ~MissileBananita2d();
		virtual void animate( float time );
		virtual void explode( );
};




#endif