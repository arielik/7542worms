#pragma once

#ifndef __WORMVIEW_H__
#define __WORMVIEW_H__
#include "TextureManager.h"
#include "View.h"
#include "TextView.h"
#include "Sprite.h"
#include "../../Servidor/modelo/GameElement.h"
#include "../controlador/Contracts/OnMovementListener.h"
#include "StateBarView.h"
#include "../../utils/Constantes/Colors.h"
#include "../sonido/SoundManager.h";


enum WormState {
	WORM_VIEW_DOING,
	WORM_VIEW_JUMPING,
	WORM_VIEW_MOTIONLESS,
	WORM_VIEW_DROWNED,
	WORM_VIEW_DEAD
};

class WormView: public View, public OnMovementListener
{
private: 
	int id;
	SDL_RendererFlip flip;

	bool selected;

	

	WormState state;
	
	Sprite* currentSprite;

	bool alive,
		 lastWords;

	TextView labelUsuario;
	TextView labelNombre;

	bool gray;

	std::string player;
	TeamColors color;

	SDL_Color white;

	WeaponId weaponId;

	int currentLife;

	int widhtLife100;
	int widhtLifeCurrent;
	
	void selectWeapon(WeaponId idWapon);
	void unselectWeapon() {this->weaponId = NO_WEAPON;}


public:
	WormView(int id);
	
	std::map<std::string, Sprite> sprites;
	void clean();
	
	void update(GameElement* domainElement);

	void update();

	void draw(SDLScreen & screen);

	int getId() {return this->id;}
	std::string getPlayer();

	/*void setSpriteWalk(Sprite spriteWalk) {this->spriteWalk = spriteWalk;}
	void setSpriteJump(Sprite spriteJump) {this->spriteJump = spriteJump;}
	void setSpriteBazooka(Sprite spriteBazooka) {this->spriteBazooka = spriteBazooka;}
*/
	
	WeaponId getWeaponId() {return this->weaponId;}

	void OnMovement(MovementEvent e);

	bool isSelected();
	void select();
	void deselect();

	bool isDead();
	bool isAlive();
	bool isDrowned() {return (this->state == WORM_VIEW_DROWNED);}
	bool isJumping() {return (this->state == WORM_VIEW_JUMPING);}
	bool isLastWords();
	void setLastWords(bool lastWords);

	bool isGrey();
	void putGrey();
	void quitGrey();

	void setColor(TeamColors color);

	void setPlayer(std::string player);

	int getXCenter();
	int getYCenter();

	int getW() {return this->currentSprite->getWidth();}
	int getH() {return this->currentSprite->getHeight();}

	void setUserLabel(std::string text);
	void WormView::setName(std::string text);

	tDirection getDirection();

	~WormView(void);

};

#endif /** __WORMVIEW_H__ **/