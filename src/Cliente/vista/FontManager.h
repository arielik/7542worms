#ifndef __FONT_MANAGER__
#define __FONT_MANAGER__
#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include <map>
#include <string>
#include "../../utils/Log.h"
class FontManager
{
private:
	std::map<std::string, TTF_Font *> map;
	SDL_Renderer * renderer;
public:
	FontManager(void);
	~FontManager(void);

	static FontManager & Instance(){
			static FontManager instance;
			return instance;
	}

	void init(SDL_Renderer * renderer);
	void openFonts();
	TTF_Font* getFont(std::string fontId);
	SDL_Renderer * getRenderer() {return this->renderer;}
	void closeFonts();
};

#endif /*__FONT_MANAGER__*/
