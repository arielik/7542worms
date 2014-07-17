#pragma once

#ifndef __PROJECTILE_VIEW_H__
#define __PROJECTILE_VIEW_H__
#include "TextureManager.h"
#include "View.h"
#include "TextView.h"
#include "Sprite.h"
#include "../../Servidor/modelo/GameElement.h"
#include "../sonido/SoundManager.h"
#include "../../utils/Constantes/Colors.h"

class ProjectileView: public View
{
protected:

	int id;

	SDL_RendererFlip flip;
	
	Sprite* currentSprite;

	TextView timerText;

	Sprite spriteBullet;

	Sprite spriteExplosion;

	bool detonated;

	bool detonatedParcial;

	bool drowned;

	tDirection direction;
	
	int currentLife;

	int lifeInitial;

	int widhtLife100;

	int widhtLifeCurrent;

public:
	ProjectileView(int id);

	int getId() {return this->id;}

	void setSpriteBullet(Sprite spriteBullet) {this->spriteBullet = spriteBullet;}
	void setSpriteExplosion(Sprite spriteExplosion) {this->spriteExplosion = spriteExplosion;}
					
	int ProjectileView::getLifeInitial();
		
	void ProjectileView::setLifeInitial(int life);

	void clean();
	
	void update(GameElement* domainElement);

	void update();

	bool isDetonateDone();

	virtual void draw(SDLScreen & screen) = 0;

	virtual int getXCenter();

	virtual int getYCenter();

	virtual void detonate();
	virtual void detonateParcial();

	bool isDrowned() {return this->drowned;}

	~ProjectileView(void);

	void turnRight() {this->direction = D_RIGHT;}
	void turnLeft() {this->direction = D_LEFT;}

	void calcRemainTime(int domainLife);
};


#endif /** __PROJECTILE_VIEW_H__ **/