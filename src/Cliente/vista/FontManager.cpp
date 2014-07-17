#include "FontManager.h"


FontManager::FontManager(void)
{
}


FontManager::~FontManager(void)
{
}


void FontManager::init(SDL_Renderer * renderer)
{
	Log::i("FontManager: Iniciando");
	this->renderer = renderer;
	if( TTF_Init() == -1 )
	{
		Log::e("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
	} 
	else
	{
		openFonts();
	}
}

void FontManager::openFonts()
{
	TTF_Font * aFont = TTF_OpenFont( "res/font/arial.ttf", 11 );
	if( aFont == NULL )
	{
		Log::e("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
	}
	else
	{
		Log::i("Font levantado");
		map["arial"] = aFont;
	}
}
TTF_Font* FontManager::getFont(std::string fontId)
{
	if (map.find(fontId) != map.end())
	{
		return map[fontId];
	} 
	else 
	{
		Log::e("FontManager: not found font by id: ", fontId);
		return NULL;
	}
}
void FontManager::closeFonts()
{
	Log::i("TTF: Cerrando");
	std::map<std::string, TTF_Font*>::iterator iter;
	for (iter = map.begin(); iter!=map.end(); ++iter)
	{
		TTF_CloseFont(iter->second);
	}
	map.clear();
}