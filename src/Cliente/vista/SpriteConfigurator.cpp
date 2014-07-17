#include "SpriteConfigurator.h"


SpriteConfigurator::SpriteConfigurator(void) 
{
}

SpriteConfigurator::~SpriteConfigurator(void)
{
	
}

void SpriteConfigurator::add(std::string imageId, int width, int height, int rows, int countSleepFrame)
{
	
	if (sprite_map.find(imageId) != sprite_map.end())
	{
		std::stringstream msg;
		msg<<"SpriteConfigurator: El sprite id: "<<imageId<< "ya existe";
		throw GameException(msg.str());
	} 
	else 
	{
		Sprite aSprite(imageId, width, height, rows, countSleepFrame);
		sprite_map[imageId] = aSprite;
	}
}


Sprite SpriteConfigurator::get(std::string imageId) {
	if (sprite_map.find(imageId) != sprite_map.end())
	{
		return sprite_map[imageId];
	} 
	else 
	{
		std::stringstream msg;
		msg<<"SpriteConfigurator: no se encontro encontro el sprite id: "<<imageId;
		throw GameException(msg.str());
	}
}
