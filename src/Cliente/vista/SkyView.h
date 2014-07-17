#pragma once

#ifndef __SKYVIEW_H__
#define __SKYVIEW_H__
#include "TextureManager.h"
#include "View.h"
#include "Sprite.h"
class SkyView: public View
{
	std::string imageId;

public:

	std::map<std::string, Sprite> sprites;

	SkyView(std::string imageId);
									
	void clean();
	
	void update();

	void draw(SDLScreen & screen);

	~SkyView(void);
};

#endif /** __SKYVIEW_H__ **/