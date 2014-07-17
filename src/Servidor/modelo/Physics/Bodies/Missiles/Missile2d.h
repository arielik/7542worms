#ifndef MISSILE2D_H_
#define MISSILE2D_H_
#include "../../Body.h"
#include "../../../Entities/Missile.h"

#define BULLET_RADIUS 0.4f

class Missile2d : public Body{
	
	protected:
		Explosion explosion;

	public:
		Missile2d();
		Missile2d(ElementType type, float posX, float posY, float angle_x, float angle_y, float fuerzaDisparo, b2World *myWorld, GameElement *modelElement);
		virtual void animate( float time ) = 0;
		virtual void explode() = 0;
		 Explosion getExplosion();
		virtual ~Missile2d();

};


#endif