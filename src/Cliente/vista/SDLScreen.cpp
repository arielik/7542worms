#include "SDLScreen.h"



SDLScreen::SDLScreen() 
{
	this->scale = 1;
	this->mTexture = NULL;
}

void SDLScreen::init(const char* title, int xpos, int ypos, int width,
			int height, int flags)
{
	this->title.append(title);
	// init the window
	m_pWindow = SDL_CreateWindow(title, xpos, ypos,	width, height, flags);

	if(m_pWindow != 0) // window init success
	{
		this->height = height;
		this->width = width;
		renderer = SDL_CreateRenderer(m_pWindow, -1, 0);
		//renderer = SDL_CreateRenderer(m_pWindow, -1, SDL_RENDERER_TARGETTEXTURE);
		 
			if(renderer != 0) // renderer init success
		{
			//SDL_RenderSetLogicalSize( renderer, width, height );
			SDL_SetRenderDrawColor(renderer,
			0xFF,0xFF,0xFF,0xFF);

		}
		else
		{

			//return false; // renderer init fail
		}
	}
	else
	{
		//return false; // window init fail
	}

	
}	

void SDLScreen::createTarget(int w, int h) {
	this->mTexture = SDL_CreateTexture( renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, this->width, this->height  );
	if (this->mTexture == NULL) 
	{
		Log::e( "Unable to create blank texture target! SDL Error: %s\n", SDL_GetError() );
	} else
	{
		Log::i( "TARGETE was created" );
	}

	this->mTexture2 = SDL_CreateTexture( renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, this->width, this->height );
	if (this->mTexture == NULL) 
	{
		Log::e( "Unable to create blank texture target 2! SDL Error: %s\n", SDL_GetError() );
	} else
	{
		Log::i( "TARGETE was created" );
	}
}

void SDLScreen::setTarget(int index) {
	if (index==1) {
		//SDL_SetTextureBlendMode(this->mTexture, SDL_BLENDMODE_BLEND);
		SDL_SetRenderTarget(renderer, this->mTexture);	
	} else if (index==2) {
		//SDL_SetTextureBlendMode(this->mTexture2, SDL_BLENDMODE_BLEND);
		SDL_SetRenderTarget(renderer, this->mTexture2);	
	}
}

void SDLScreen::setOriginalTarget()
{
	SDL_SetRenderTarget(renderer, NULL);
}

void SDLScreen::clear()
{
	SDL_RenderClear(renderer); // clear the renderer to the draw color
}	
void SDLScreen::render()
{
	/*setOriginalTarget();*/
	//SDL_RenderCopy(renderer, this->mTexture, NULL, NULL);
	//SDL_SetRenderTarget(renderer, NULL); //NULL SETS TO DEFAULT

	/*SDL_Rect canvas;
	canvas.x=0;
	canvas.y=0;
	canvas.w=700;
	canvas.h=400;

	SDL_RenderCopy(renderer, this->mTexture, NULL, &canvas);*/
	SDL_RenderPresent(renderer); // draw to the screen
}	
void SDLScreen::terminate()
{
	SDL_DestroyTexture(this->mTexture);	
	SDL_DestroyWindow(m_pWindow);
	SDL_DestroyRenderer(renderer);
	TTF_Quit();
	SDL_Quit();
}

void SDLScreen::setState(std::string string_state)
{
	std::stringstream caption;

	caption<<this->title<<" - Estado: "<<string_state;
	SDL_SetWindowTitle(m_pWindow, caption.str().c_str());
}

SDL_Renderer* SDLScreen::getRenderer()
{
	return renderer;
}

SDLScreen::~SDLScreen(void)
{
	
}

void SDLScreen::OnZoom(ZoomEvent e)
{
	SDL_Rect newViewPort;
	float nextScale = this->scale + (0.01 * e.y);
	if (nextScale > 0.5 && nextScale <= 3) 
	{
//		this->setTarget(1);
		SDL_RenderSetScale(renderer, nextScale, nextScale);
		SDL_RenderGetViewport(renderer, &newViewPort);
		int w_new = (int)(700.0f * 1/nextScale);   // nuevo ancho manual
		int h_new = (int)(400.0f * 1/nextScale);   // nuevo alto manual

		Log::i(" new view port posX:%d		posY:%d		ancho: %d		alto: %d  scale: %f", newViewPort.x, newViewPort.y, newViewPort.w, newViewPort.h, nextScale);
		
		//Log::i(" new view port posX:%d		posY:%d		ancho: %d		alto: %d  scale: %f ZOOMSURSICE", newViewPort.x, newViewPort.y, w_new, h_new, nextScale);
		//todo: pasar a camera
		int camaraBootom = newViewPort.h + this->refCam->getY();
		int camaraRight = newViewPort.w + this->refCam->getX();
		if (camaraBootom <= this->refCam->getHeightScenario() &&
			camaraRight <= this->refCam->getWidthScenario())
		{
			this->refCam->setH(newViewPort.h);
			this->refCam->setW(newViewPort.w);
			this->scale = nextScale;
		}
		else
		{
			SDL_RenderSetScale(renderer, this->scale, this->scale);
		}
		
	}
	
}