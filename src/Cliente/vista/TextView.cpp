#include "TextView.h"

TextView::TextView()
{

	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
	this->font = Arial16;
	this->zoom = false;
}

TextView::~TextView()
{
	free();
}

void TextView::setFont(Tfont font){
	this->font = font;

}

bool TextView::setText( std::string textureText, SDL_Color textColor)
{/*
	free();

	SDL_Surface* textSurface = TTF_RenderText_Solid( FontManager::Instance().getFont("arial"), 
													textureText.c_str(), textColor );
	if( textSurface == NULL )
	{
		//printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
	}
	else
	{
        mTexture = SDL_CreateTextureFromSurface( FontManager::Instance().getRenderer(), textSurface );
		if( mTexture == NULL )
		{
			//printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
		}
		else
		{
			mWidth = textSurface->w;
			mHeight = textSurface->h;
		}

		SDL_FreeSurface( textSurface );
	}
	
	return mTexture != NULL;*/
	
	this->text = textureText;
	this->textColor = textColor;
	return true;
}

void TextView::free()
{
	if( mTexture != NULL )
	{
		SDL_DestroyTexture( mTexture );
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

void TextView::setColor( Uint8 red, Uint8 green, Uint8 blue )
{
	SDL_SetTextureColorMod( mTexture, red, green, blue );
}

void TextView::setBlendMode( SDL_BlendMode blending )
{
	SDL_SetTextureBlendMode( mTexture, blending );
}
		
void TextView::setAlpha( Uint8 alpha )
{
	SDL_SetTextureAlphaMod( mTexture, alpha );
}

void TextView::draw(SDL_Renderer * gRenderer, int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip )
{
	/*
	x = x - TextureManager::Instance().getCamera().getX();
	y = y - TextureManager::Instance().getCamera().getY();

	SDL_Rect renderQuad = { x, y, mWidth, mHeight };

	if( clip != NULL )
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	SDL_RenderCopyEx( gRenderer, mTexture, clip, &renderQuad, angle, center, flip );*/

	TextManager::Instance().write(this->font,x, y,this->text,this->textColor, zoom);
}

int TextView::getWidth()
{
	return mWidth;
}

int TextView::getHeight()
{
	return mHeight;
}
