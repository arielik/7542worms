#pragma once
#ifndef __TEXT_VIEW_H_
#define __TEXT_VIEW_H_
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <iostream>
#include <string.h>
#include "TextureManager.h"
#include "FontManager.h"
#include "TextManager.h"


class TextView
{
	bool zoom;

	public:

		TextView();


		~TextView();


		void setFont(Tfont font);

		bool setText( std::string textureText, SDL_Color textColor);

		void free();

		void setColor( Uint8 red, Uint8 green, Uint8 blue );

		void setBlendMode( SDL_BlendMode blending );

		void setAlpha( Uint8 alpha );
		
		void draw(SDL_Renderer * gRenderer, int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );
		int getWidth();
		int getHeight();

		void enableZoom() {this->zoom = true;};

	private:
		
		SDL_Texture* mTexture;

		Tfont font;
		std::string text;
		SDL_Color textColor;


		int mWidth;
		int mHeight;
};

#endif /*__TEXT_VIEW_H_*/