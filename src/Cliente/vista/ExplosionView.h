#pragma once

#ifndef __EXPLOSION_VIEW_H__
#define __EXPLOSION_VIEW_H__
#include "TextureManager.h"
#include "View.h"
#include "TextView.h"
#include "Sprite.h"
#include "../sonido/SoundManager.h"

class ExplosionView: public View
{
protected:
	
	Sprite* currentSprite;

	Sprite spriteExplosion;


public:
	ExplosionView(int x, int y);

	void setSpriteExplosion(Sprite spriteExplosion) {this->spriteExplosion = spriteExplosion;}
					

	void clean();
	

	void update();

	
	void draw(SDLScreen & screen);

	int getXCenter();

	int getYCenter();

	bool isDone();


	~ExplosionView(void);
};


#endif /** __EXPLOSION_VIEW_H__ **/