#ifndef __TEXT_MANAGER__
#define __TEXT_MANAGER__
#include <SDL_mixer.h>
#include "../../utils/Constantes/Constantes.h"
#include <map>
#include <SDL.h>
#include "../../utils/Log.h"
#include "TextureManager.h"

enum Tfont{
	Arial16,
	Arial12,
};

class TextManager{
private:
	SDL_Renderer * renderer;
	struct stFont{
		std::string idFont;
		int ancho, alto;
		int anchoLetra, altoLetra;
	};
	std::map<std::string, stFont> font_map;
	stFont font;
public:

	static TextManager & Instance(){
			static TextManager theTextManager;
			return theTextManager;
	}

	void init(SDL_Renderer * renderer);
	void loadFont(Tfont font);
	void wLetter(std::string idFont,int x, int y, char lett,SDL_Color color, bool zoom = false);
	void write(Tfont fuente,int x, int y, std::string w,SDL_Color color, bool zoom = false);




};




#endif /* defined(__TEXT_MANAGER__) */