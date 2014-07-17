#pragma once

#ifndef __BOOTSTRAP_H_
#define __BOOTSTRAP_H_

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include "SDLScreen.h"
#include "TextureManager.h"
#include "SpriteConfigurator.h"
#include "FontManager.h"
#include "TextManager.h"

#include "../../utils/ParserYaml.h"



class Bootstrap
{
private:
	SDLScreen screen;

public:
	Bootstrap(void);

	/**Inicialize enviroment*/
	void init();

	void reinit();

	void loadConfigGame();

	/**Shout down enviroment*/
	void shoutDown();

	/**Load sprites*/
	void loadSprites();

	void loadImg();

	void initCamera(int w, int h);

	void reloadEart();

	void loadEart();

	void loadMenuWeapon();

	void loadWaterImg();

	SDLScreen & getScreen();
	
	~Bootstrap(void);
};

#endif /* defined(__BOOTSTRAP_H_) */