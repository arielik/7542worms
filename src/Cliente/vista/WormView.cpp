#include "WormView.h"


WormView::WormView(int id)
	: View(0, 0), id(id), flip(SDL_FLIP_NONE), state(WORM_VIEW_MOTIONLESS), alive(true)
{
	currentSprite = NULL;
	this->selected = false;
	this->gray = false;
	white.a = 0xFF;
	white.r = 0xFF;
	white.g = 0xFF;
	white.b = 0xFF;
	this->weaponId = NO_WEAPON;
	this->widhtLife100 = 25;
	this->widhtLifeCurrent = 25;
	this->currentLife = 100;
	this->enableScroll();
	labelUsuario.enableZoom();
	labelNombre.enableZoom();
	this->lastWords = true;
}

void WormView::setUserLabel(std::string text)
{
	labelUsuario.setText(text, white);
}

void WormView::setName(std::string text)
{
	labelNombre.setText(text, white);
}


WormView::~WormView(void)
{
}


void WormView::clean()
{

}


bool WormView::isLastWords(){
	return this->lastWords;
}

void WormView::setLastWords(bool lastWords){
	this->lastWords = lastWords;
}

void WormView::selectWeapon(WeaponId idWapon)
{
	this->weaponId = idWapon;
}

void WormView::update(GameElement* domainElement)
{
	std::pair<float, float> pointUL = domainElement->getPosition();
	tPoint pointSDL = TextureManager::Instance().convertPointUL2PXSDL(pointUL.first, pointUL.second);
	this->setX(pointSDL.x);
	this->setY(pointSDL.y);
	this->selectWeapon((WeaponId)domainElement->getWeaponId());
	//Log::i("WormView::update >> weapon %d", this->weaponId);
	// ACTIONS
	switch (domainElement->getAction())
	{
		case MOVE_RIGHT:
		case MOVE_LEFT:
			this->state = WORM_VIEW_DOING;
			break;
		case MOVELESS:
		case WITH_WEAPON_LEFT:
		case WITH_WEAPON_RIGHT:
			this->state = WORM_VIEW_MOTIONLESS;
			break;
		case JUMP_LEFT:
		case JUMP:
		case JUMP_RIGHT:
			this->state = WORM_VIEW_JUMPING;
			break;
		case DEAD:
			this->state = WORM_VIEW_DEAD;
			break;
		case WORM_DROWNED:
			Log::i("WormView:: WORM_VIEW_DROWNED %d", domainElement->getId());
			this->state = WORM_VIEW_DROWNED;
			break;
		/*default:
			this->state = WORM_VIEW_MOTIONLESS;
			break;*/
	}
  
    // DIRECTION
	switch (domainElement->getAction())
	{
		case MOVELESS_RIGHT:
		case NOT_CONNECTED_RIGHT:
		case MOVE_RIGHT:
		case JUMP_RIGHT:
		case WITH_WEAPON_RIGHT:
			this->flip = SDL_FLIP_HORIZONTAL;
			break;
		case MOVELESS_LEFT:
		case NOT_CONNECTED_LEFT:
		case MOVE_LEFT:
		case JUMP_LEFT:
		case WITH_WEAPON_LEFT:
			this->flip = SDL_FLIP_NONE;
			break;
		/*default:
			this->flip = SDL_FLIP_NONE; 
			break;*/
	}

	if (domainElement->getLife() < this->currentLife) {
		this->widhtLifeCurrent = (int)(((float)domainElement->getLife() * (float)this->widhtLife100) / 100.0f);
		if (this->widhtLifeCurrent > this->widhtLife100) {
			this->widhtLifeCurrent = this->widhtLife100;
		} else if (this->widhtLifeCurrent <= 0) {
			this->widhtLifeCurrent = 1;
		}
		this->currentLife = domainElement->getLife();
		SoundManager::Instance().pOUCH();
	}
	
}
	
void WormView::update() 
{
	if (currentSprite == NULL) {
		currentSprite = &this->sprites["caminar"];
	}
	if (this->state == WORM_VIEW_JUMPING)
	{
		// Camino sin arma
		if (currentSprite != &this->sprites["saltar"]) {
			SoundManager::Instance().pJUMP1();
			currentSprite = &this->sprites["saltar"];
		}
		currentSprite->update();
	} else if (this->state == WORM_VIEW_DOING)
	{
		// Camino sin arma
		if (currentSprite != &this->sprites["caminar"]) {
			currentSprite = &this->sprites["caminar"];
		}
		currentSprite->update();
	} 
	else if (this->state == WORM_VIEW_MOTIONLESS)
	{
		if (this->weaponId == GRENADE && currentSprite != &this->sprites["granada"]) 
		{
			currentSprite = &this->sprites["granada"];
		} 
		if (this->weaponId == DYNAMITE && currentSprite != &this->sprites["dinamita"]) 
		{
			currentSprite = &this->sprites["dinamita"];
		}
		if (this->weaponId == BAZOOKA && currentSprite != &this->sprites["bazooka"]) 
		{
			currentSprite = &this->sprites["bazooka"];
		}
		if (this->weaponId == BANANA && currentSprite != &this->sprites["banana"]) 
		{
			currentSprite = &this->sprites["banana"];
		}
		if (this->weaponId == SHEEP && currentSprite != &this->sprites["sheep"]) 
		{
			currentSprite = &this->sprites["oveja"];
		}
		if (this->weaponId == HOLY && currentSprite != &this->sprites["holy"]) 
		{
			currentSprite = &this->sprites["holy"];
		}
		if ((this->weaponId == AIRATTACK || this->weaponId == BURRO)
						&& currentSprite != &this->sprites["radio"]) 
		{
			currentSprite = &this->sprites["radio"];
		}
		
		if (this->weaponId == NO_WEAPON && currentSprite != &this->sprites["caminar"]) 
		{
			currentSprite = &this->sprites["caminar"];
		}
		
		currentSprite->clean();

	} else if (this->state == WORM_VIEW_DEAD) {
	
		Log::i("WormView::update >> sprite worm mori");
		if (alive) {
			SoundManager::Instance().pBYEBYE();
			currentSprite = &this->sprites["morir"];
		}
		if (currentSprite == &this->sprites["morir"] && currentSprite->isLastFrame()) {
			currentSprite = &this->sprites["explosion"];
		} 

		alive=false;

		currentSprite->update();
	}

}

void WormView::draw(SDLScreen & screen)
{ 
	
	TextureManager::Instance().drawFrame(currentSprite->getImageId(), 
										this->getXCenter(), 
										this->getYCenter(), 
										currentSprite->getWidth(), 
										currentSprite->getHeight(), 
										currentSprite->getCurrentRow(), 
										currentSprite->getCurrentFrame(), 
										screen.getRenderer(),
										this->gray, 
										this->flip,
										true);
	
	 
	if (this->isSelected())
	{
		labelNombre.draw(screen.getRenderer(),
						 this->getXCenter(),
						 this->getYCenter() - 15);
	}

	SDL_Rect rect;
	rect.x = this->getX()-10;
	rect.y = this->getY()-22;
	rect.w = this->widhtLifeCurrent;
	rect.h = 5;
	SDL_Color color = Util::geColorTeam(this->color);
	TextureManager::Instance().drawFillRect(screen.getRenderer(),rect, color.r, color.g, color.b, color.a,true);

}

bool WormView::isSelected(){
	return this->selected;
}

void WormView::select(){
	this->selected = true;
}
void WormView::deselect(){
	//this->state = WORM_VIEW_MOTIONLESS;
	this->selected = false;
}

bool WormView::isGrey(){ return this->gray;}
void WormView::putGrey(){ this->gray = true;}
void WormView::quitGrey(){this->gray = false;}


void WormView::OnMovement(MovementEvent e){

	//if (e.x == 1) // derecha
	//{
	//	this->state = WORM_VIEW_DOING;
	//	this->flip = SDL_FLIP_HORIZONTAL;
	//}
	//else if (e.x == -1) // izquierda
	//{
	//	this->state = WORM_VIEW_DOING;
	//	this->flip = SDL_FLIP_NONE;
	//} 
	//else if (e.x == 0) // quieto
	//{
	//	this->state = WORM_VIEW_MOTIONLESS;
	//}

}

void WormView::setColor(TeamColors color){
	this->color = color;
}

void WormView::setPlayer(std::string player){
	this->player = player;
}

std::string WormView::getPlayer(){
	return this->player;
}

int WormView::getXCenter()
{
	return this->getX()-(currentSprite->getWidth()/2);
}


int WormView::getYCenter()
{
	return this->getY()-(currentSprite->getHeight()/2);
}

tDirection WormView::getDirection()
{
	if (this->flip == SDL_FLIP_NONE) {
		return D_LEFT;
	} else {
		return D_RIGHT;
	}
}

bool WormView::isDead() {
	return (!this->alive && (&this->sprites["explosion"] == currentSprite) && currentSprite->isLastFrame());
}

bool WormView::isAlive(){
	return this->alive;
}
