#pragma once

#ifndef __SPRITE_CONFIGURATOR_H__
#define __SPRITE_CONFIGURATOR_H__
#include <string>
#include <sstream>
#include <map>
#include "Sprite.h"
#include "GameException.h"
class SpriteConfigurator
{
private:
	
	// Contains all texture
	std::map<std::string, Sprite> sprite_map;

public:
	
	SpriteConfigurator(void);

	static SpriteConfigurator & Instance(){
			static SpriteConfigurator theInstance;
			return theInstance;
	}

	/**
	* @param imageId			The image key stored in texture manager
	* @param width				Width of frame
	* @param height				Height of frame
	* @param rows				Count of rows in the sprite
	* @param countSleepFrame	Times to wait in each frame
	* 
	* @throw GameException		When the imageId has already registered
	**/
	void add(std::string imageId, int width, int height, int rows, int countSleepFrame);
	

	/**
	* @param imageId			The image key stored in texture manager
	* 
	* @throw GameException		when the sprite wasn't found
	**/
	Sprite get(std::string imageId);

	~SpriteConfigurator(void);
};



#endif /* __SPRITE_CONFIGURATOR_H__ */