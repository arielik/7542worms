#include "GameActivity.h"
#define WORM_W 20
#define WORM_H 30




GameActivity::GameActivity(SDLScreen & screen, 
							GameDomain* domain, 
							GameController* cController,
							std::string playerId, Updater & updater)
							:Activity(screen), cController(cController), playerId(playerId), updater(updater)
{

	builder = new GameViewBuilder(domain, &screen);
	builder->setPlayerID(playerId);
	this->setListeners(screen);
	this->wormIdSelected = -1;
	this->wormIdDesSelected = -1;
	this->isMyTurn = false;
	this->idWeapon = NO_WEAPON;
	this->aimView = NULL;
	this->isRightAim = false;
	this->isLeftAim = false;
	this->iniHmissile();
	this->auxCallLog = CALL_NULL;
	
}

void GameActivity::buildView()
{
	builder->buildContainer();
	builder->buildSky();
	//builder.buildFigures();
	builder->buildWaterImg();
	builder->buildEart();
	builder->buildCharacters();
	builder->buildExplosionContainter();
	builder->buildProjectileContainer();
	
	builder->buildStateBar();
	builder->buildPower(cController);
	builder->buildTimer();
	builder->buildMenuWeapon();

	builder->buildWaterSurfImg();
	this->setContentView(builder->getGameView());
	GameView* gameView = static_cast<GameView*>(this->aView);
	aimView = new AimView();
	gameView->add(aimView);

	builder->buildPlayerProgress();
	this->cController->addOnChangeListener(aimView);
	this->cController->addOnMovementListener(aimView);
	TextureManager::Instance().setFocus(FOCUS_BOTOOM_CENTER);
}

void GameActivity::update() 
{
	
	GameView* gameView = static_cast<GameView*>(this->aView);
	std::map<int,GameElement>* domainElements = this->builder->getDomain()->getDomainElements();
	std::map<int,GameElement>::iterator it;
	Log::t(VIEW,"Actualizando %d elemento", domainElements->size());
	this->iniState();
	for (it = domainElements->begin(); it != domainElements->end(); ++it)
	{
		GameElement domainElement = it->second;
		Log::t(VIEW,"elemento id %d",domainElement.getId());
		try
		{
			if (domainElement.getType() == WORM) 
			{
				WormView* aWorm = gameView->findWormById(domainElement.getId());
				StateConn stateConn = this->builder->getDomain()->getPlayerState(domainElement.getPlayerID());
				if (!this->isThisClientOwner(domainElement.getId()))
				{
					if (stateConn == DISCONNECTED)
					{
						aWorm->putGrey();
						Log::d("El usuario %s tiene estado %d",domainElement.getPlayerID().c_str(),stateConn );	
					}
					else
					{
						aWorm->quitGrey();
					}
				}
				if (aWorm->isDead() || aWorm->isDrowned()) {
					this->futureFreeWorm.push_back(aWorm->getId());
				} else {
					aWorm->update(&domainElement);
				}
				
			}  
			else if (domainElement.getType() == WEAPON)
			{
				ProjectileView * aProjectile = gameView->findProjectileById(domainElement.getId());
				if (aProjectile->isDetonateDone() || aProjectile->isDrowned()) 
				{
					this->futureFree.push_back(aProjectile->getId());
				}
				aProjectile->update(&domainElement);
			}
		}
		catch (GameException e) {
			Log::e(e.what());
		}
	}
	this->runGarbarageColector();
	this->aView->update();
}

GameActivity::~GameActivity(void)
{
	delete builder;
}

void GameActivity::runGarbarageColector() {
	GameView* gameView = static_cast<GameView*>(this->aView);
	std::vector<int>::iterator itProj;
	for (itProj = this->futureFree.begin(); itProj != this->futureFree.end(); ++itProj)
	{
		int id = *itProj;
		gameView->freeProjectileView(id);
		this->builder->getDomain()->removeElement(id);
		Log::i("Elimine projectile %d en la vista", id);
	}
	this->futureFree.clear();

	std::vector<int>::iterator itWorm;
	for (itWorm = this->futureFreeWorm.begin(); itWorm != this->futureFreeWorm.end(); ++itWorm)
	{
		int id = *itWorm;
		if (this->wormIdSelected == id ){
			Log::i("Elimine Worm %d que estaba seleccionado", id);
			dettachWorm();
		}
		gameView->freeWormView(id);
		this->builder->getDomain()->removeElement(id);
		
		Log::i("Elimine Worm %d en la vista", id);
	}
	this->futureFreeWorm.clear();
}


void GameActivity::iniState(){
	ActionWorm aw;
	if(afterShoot){
		this->cController->remuveOnActionListener(this);
		this->offMenu();
		this->denyPower();
	}
	if(!this->isRightAim && this->aimView->isRightSide()){
		this->isLeftAim = false;
		this->isRightAim = true;
		//this->updater.notify(this->wormIdSelected, WITH_WEAPON_RIGHT, this->idWeapon);
		aw.moveView = WITH_WEAPON_RIGHT;
		this->ActionResult(CALL_MOVEVIEW, NULL, &aw);
	}
	else if(!this->isLeftAim && this->aimView->isLeftSide()){
		this->isRightAim = false;
		this->isLeftAim = true;
		//this->updater.notify(this->wormIdSelected, WITH_WEAPON_LEFT, this->idWeapon);
		aw.moveView = WITH_WEAPON_LEFT;
		this->ActionResult(CALL_MOVEVIEW, NULL, &aw);
	}
}

void GameActivity::allowPower(){
	GameView* gameView = static_cast<GameView*>(this->aView);
	return gameView->allowPower();
}

void GameActivity::denyPower(){
	GameView* gameView = static_cast<GameView*>(this->aView);
	return gameView->denyPower();
}


void GameActivity::deselectPreviewsWorm()
{
	ActionWorm aw;
	GameView* gameView = static_cast<GameView*>(this->aView);
	if (this->wormIdSelected > 0) {
		WormView* aWorm = gameView->findWormById(this->wormIdSelected);
		this->cController->remuveListener(aWorm);
		aWorm->deselect();
		

		ActionWorm aw;
		aw.dim = aWorm->getDirection();
		this->ActionResult(CALL_UNWEAPON, NULL, &aw);
	
		aw.id = aWorm->getId();
		this->ActionResult(CALL_STOPWORM, NULL, &aw);
		this->wormIdSelected = -1;
	}
}
void GameActivity::dettachWorm() {
	try {
		GameView* gameView = static_cast<GameView*>(this->aView);
		WormView* aWorm = gameView->findWormById(this->wormIdSelected);
		this->cController->remuveListener(aWorm);
		this->wormIdSelected = -1;
	} 
	catch (GameException & e) 
	{
		Log::e(e.what());
	}
}


void GameActivity::stop()
{
	ActionWorm aw;
	if (this->wormIdSelected > 0) 
	{
		//updater.doStopWorm(this->wormIdSelected);
		aw.id = this->wormIdSelected;
		this->ActionResult(CALL_STOPWORM, NULL, &aw);
		this->wormIdSelected = -1;
	}
}

void GameActivity::selectWorm(WormView* aWorm)
{
	this->wormIdSelected = aWorm->getId();
	aWorm->select();
	if (this->playerId.compare(aWorm->getPlayer()) == 0)
	{
		this->cController->addListener(aWorm);
	}
}

void GameActivity::doExplotion(float x, float y, float radio)
{
	Log::i(" Explotar terreno en %f y %f  y radio %f [UL]", x, y, radio);
	GameView* gameView = static_cast<GameView*>(this->aView);
	tPoint pointSDL = TextureManager::Instance().convertPointUL2PXSDL(x, y);

	int xView = pointSDL.x;
	int yView = pointSDL.y;

	int rView = radio * ESCALA_UL2PX;
	Log::i(" Explotar terreno en %d y %d  y radio %d [PX]", xView, yView, rView);
	gameView->getDestroyEart(xView, yView, rView);
}


void GameActivity::calcRectPosition(SDL_Rect& wormRect,WormView *aWorm){
	
	wormRect.x = (aWorm->getX()-(WORM_W/2));
	wormRect.y = (aWorm->getY()-(WORM_H/2));
	
	wormRect.w = WORM_W;  
	wormRect.h = WORM_H;  

}

bool GameActivity::hasClickedWorm(SDL_Point clickPoint)
{
	bool wormClicked = false;
	std::map<int,GameElement>* domainElements = this->builder->getDomain()->getDomainElements();
	std::map<int,GameElement>::iterator it;
	GameView* gameView = static_cast<GameView*>(this->aView);
	for (it = domainElements->begin(); it != domainElements->end(); ++it)
	{
		GameElement domainElement = it->second;
		if (domainElement.getType() == WORM){
			WormView* aWorm = gameView->findWormById(domainElement.getId());
			if (aWorm != NULL){
				SDL_Rect wormRect;
				this->calcRectPosition(wormRect,aWorm);
				if (SDL_EnclosePoints(&clickPoint,1,&wormRect,NULL))
				{
					wormClicked =  true;
					break;
				}
			}
		}
	}
	return wormClicked;
}

bool GameActivity::hasClickedMenu(SDL_Point clickPoint){
	GameView* gameView = static_cast<GameView*>(this->aView);
	return gameView->hasClickedMenu(clickPoint);
}

bool GameActivity::hasClickedWeapon(SDL_Point clickPoint){
	GameView* gameView = static_cast<GameView*>(this->aView);
	return gameView->hasClickedWeapon(clickPoint);
}

Weapon* GameActivity::retrieveWeaponClicked(SDL_Point clickPoint){
	GameView* gameView = static_cast<GameView*>(this->aView);
	return gameView->retrieveWeaponClicked(clickPoint);
}

WormView* GameActivity::retrieveWormClicked(SDL_Point clickPoint)
{
	WormView* aWormClicked = NULL;
	std::map<int,GameElement>* domainElements = this->builder->getDomain()->getDomainElements();
	std::map<int,GameElement>::iterator it;
	GameView* gameView = static_cast<GameView*>(this->aView);
	for (it = domainElements->begin(); it != domainElements->end(); ++it)
	{
		GameElement domainElement = it->second;
		try {
			if (domainElement.getType() == WORM){
				WormView* aWorm = gameView->findWormById(domainElement.getId());
				SDL_Rect wormRect;
				this->calcRectPosition(wormRect,aWorm);
				if (SDL_EnclosePoints(&clickPoint,1,&wormRect,NULL))
				{
					aWormClicked = aWorm;
					break;
				}
			}
		} catch (GameException & e) {
			Log::e(e.what());		
		}
	}
	return aWormClicked;
}

// nota: e.x e.y son posiciones de click en la pantalla sin importar el zoom ó scroll
void GameActivity::OnClick(ClickEvent e){
	ActionWorm aw;
	GameView* gameView = static_cast<GameView*>(this->aView);
	SDL_Point clickPointScreen;
	clickPointScreen.x = e.x;
	clickPointScreen.y = e.y;

	SDL_Point clickPoint = TextureManager::Instance().convertPointScreen2SDL(e.x,e.y); 

	WormView* aWorm = NULL;

	/*if(wormIdSelected != -1 && !this->isAlive(wormIdSelected)){
		wormIdSelected = -1;
	}*/

	//Agrego para escuchar el clic del arma
	if(aimView->isShootMouse() && !hasClickedMenu(clickPointScreen)){
		if(this->idWeapon != HMISSILE){	
			int xMira= e.x;
			int yMira= e.y;
			std::pair<int, int> data = this->aimView->getData();
			Log::i("\nShoot 1: x %d, y %d FACTOR 0",xMira,yMira);
			SDL_Point sdlCoordinate = TextureManager::Instance().convertPointScreen2SDL(xMira, yMira);
			tPointf domainCoordinate = TextureManager::Instance().convertPointPXSDL2UL(sdlCoordinate.x + TextureManager::Instance().getCamera().getX(), 
																					   sdlCoordinate.y + TextureManager::Instance().getCamera().getY());
			//updater.doShoot(data.first, data.second, domainCoordinate.x, domainCoordinate.y, 0);
			//updater.doUnselectWapon(wormIdSelected, this->idWeapon);
			aw.x = domainCoordinate.x;
			aw.y = domainCoordinate.y;
			aw.factor = 0;
			this->ActionResult(CALL_SHOOT, NULL, &aw); // Despues de shoot, el modelo desecciona el arma
			aimView->unAim();
			afterShoot = true;
			this->iniHmissile();
			deselectPreviewsWeapon();
		}
		else{
			//Estoy en el caso de que se eligio el misil, guardo el x e y Objetivo
			this->xHmissile = e.x;
			this->yHmissile = e.y;
			//cambio la mira para escucharEnter
			aimView->unAim();
			this->aimView->aimBuildEnter();
		}
		return; //proceso y me voy
	}

	

	if (!hasClickedMenu(clickPointScreen) && hasClickedWorm(clickPoint)) {
		linkWorm(clickPoint);
	}
	else if (wormIdSelected != -1 && hasClickedMenu(clickPointScreen) && this->isThisClientOwner(wormIdSelected))
	{
		if(hasClickedWeapon(clickPointScreen)){
			linkWormWithWeapon(clickPointScreen);
		}
		else{
			/*TODO: entra en este else cuando un worm esta seleccionado
					y soca algun sector del menu donde no hay armas			
			*/
		}
	}
	else
	{
		deselectPreviewsWorm();
		deselectPreviewsWeapon();
		aimView->unAim();		
	}

	
}
void GameActivity::linkWorm(SDL_Point clickPoint) {
	WormView* aWorm = retrieveWormClicked(clickPoint);
	if (!aWorm->isSelected()) {
		deselectPreviewsWorm();
		selectWorm(aWorm);
		if(this->idWeapon != NO_WEAPON){
			deselectPreviewsWeapon();
			aimView->unAim();
			denyPower();
		}
	}
}

void GameActivity::linkWormWithWeapon(SDL_Point clickPointScreen) {
	GameView* gameView = static_cast<GameView*>(this->aView);
	
	WeaponId aux = this->idWeapon;
	if(this->idWeapon != NO_WEAPON){
		this->deselectPreviewsWeapon();
		aimView->unAim();
		denyPower();
	}

	Weapon* aWeapon = retrieveWeaponClicked(clickPointScreen);
	this->idWeapon = aWeapon->getId();
	aWeapon->selected();
	WormView* aWorm = gameView->findWormById(wormIdSelected);

	ActionWorm aw;
	aw.dim = aWorm->getDirection();
	this->ActionResult(CALL_WEAPON, NULL, &aw); 
	
	if(!isWeaponWithOutPower()){
		allowPower();
	}
	//logica de la mira
	aimView->setWorm(aWorm, aWeapon);
	aimView->aimBuild();


	if(aux == this->idWeapon ){
		deselectPreviewsWeapon();
		//updater.doUnselectWapon(wormIdSelected, this->idWeapon);
		aw.dim = aWorm->getDirection();
		this->ActionResult(CALL_UNWEAPON, NULL, &aw);
		aimView->unAim();
		denyPower();
	}
}

void GameActivity::deselectPreviewsWeapon(){
	if(this->idWeapon != NO_WEAPON){
		GameView* gameView = static_cast<GameView*>(this->aView);
		Weapon* aWeapon = gameView->findWeaponById(idWeapon);
		aWeapon->unSelected();
		this->idWeapon = NO_WEAPON;
	}

}


void GameActivity::otherTurn(std::string playerId) 
{
	// seter el label del gameview para mostar el turno de peppito
	GameView* gameView = static_cast<GameView*>(this->aView);
	gameView->getStateBar()->setMessageCenter("Is turn of " + playerId);
	this->isMyTurn = false;
	//this->setTimer((float)TURN_DURATION);
}

void GameActivity::endMyTurn() {
	if ( this->isMyTurn ){
		Log::i("\nRemoving all listeners");
		this->cController->remuveOnClickListener(this);
		this->cController->remuveOnMovementListener(this);
		this->cController->remuveOnActionListener(this);
		//this->deselectPreviewsWeapon();
		this->deselectPreviewsWorm();
		this->offMenu();
		this->aimView->unAim();		
	}
}


void GameActivity::beginMyTurn() 
{
	this->isMyTurn = true;
	this->afterShoot = false;
	GameView* gameView = static_cast<GameView*>(this->aView);
	gameView->getStateBar()->setMessageCenter("Is your turn");
	this->cController->addOnClickListener(this);
	this->cController->addOnMovementListener(this);
	this->cController->addOnActionListener(this);
	//@Ari @Nestor : seteo el timer con un tiempo hardcode
	//this->setTimer((float)TURN_DURATION);
}



void GameActivity::printTimer(int second){
	GameView* gameView = static_cast<GameView*>(this->aView);
	gameView->printTimer(second);
}

void GameActivity::setListeners(SDLScreen &  screen) 
{
	this->cController->addOnScrollListener(&TextureManager::Instance().getCamera());
	//this->cController->addOnZoomListener(&screen);
	this->cController->addOnZoomListener(&TextureManager::Instance().getCamera());
}


void GameActivity::buildNewWorms(std::string playerID, int id, int x, int y) 
{
	GameView* gameView = static_cast<GameView*>(this->aView);

	GameElement aGameElem(id, playerID, WORM, x, y, 0, 0, 0, 0, false);
	
	this->builder->getDomain()->addElementToDomain(aGameElem);
	WormView* aWormView = this->builder->createWorm(&aGameElem);
	gameView->getWormContainer()->add(aWormView);

}

void GameActivity::buildProjectile(int idElement, float x, float y, int type, int life, Movement action)
{
	GameView* gameView = static_cast<GameView*>(this->aView);
	Log::i("GameActivity::buildProjectile >> Agregando GameElement id: %d,pos[ %f, %f ]", idElement, x, y);
	GameElement aGameElem(idElement, this->playerId, WEAPON, x, y, 0, 0, 0, 0, false);
	aGameElem.setLife(life);
	
	this->builder->getDomain()->addElementToDomain(aGameElem);

	ProjectileView* aProjectileView = this->builder->createBullet(&aGameElem, type);
	Log::i("GameActivity::buildProjectile >> Agregando ProjectileView id: %d,pos[ %d, %d ]", aProjectileView->getId(), aProjectileView->getX(), aProjectileView->getY());
	gameView->getProjectileContainer()->add(aProjectileView);

	// Quien esta selecionado al disparar??
	try {
		WormView* aWorm = gameView->findWormById(this->wormIdSelected);
		Log::i("GameActivity::buildProjectile >> WormView %d seleccionado y pos %d, %d [px]", aWorm->getId(), aWorm->getX(), aWorm->getY());
	} catch (GameException & e) {

	}

}


void GameActivity::buildExplosion( float x, float y, int type, int radio)
{
	GameView* gameView = static_cast<GameView*>(this->aView);
	ExplosionView* aExplosionView = this->builder->createExplosion(x, y, radio);
	Log::i("GameActivity::buildExplosion >> Agregando explosion ");
	gameView->getExplosionContainer()->add(aExplosionView);
}


bool GameActivity::isAlive(int wormId) {
	GameView* gameView = static_cast<GameView*>(this->aView);

	try
	{
		WormView* aWorm = gameView->findWormById(wormId);
		SDL_Rect wormDim;
		SDL_Rect scenaryDim;
		scenaryDim.y = 0;
		scenaryDim.x = 0;
		scenaryDim.w = TextureManager::Instance().getCamera().getWidthScenario();
		scenaryDim.h = TextureManager::Instance().getCamera().getHeightScenario();
		
		wormDim.x = aWorm->getXCenter();
		wormDim.y = aWorm->getYCenter();
		wormDim.w = aWorm->getW();
		wormDim.h = aWorm->getH();
		if (TextureManager::Instance().intersectRects(wormDim, scenaryDim))
		{
			return true;
		}
		else
		{
			return false;
		}

	}
	catch (GameException e) {
		Log::e(e.what());
		return false;
	}

	return true;
}

bool GameActivity::isThisClientOwner(int wormId)
{
	GameView* gameView = static_cast<GameView*>(this->aView);
	WormView* aWorm = gameView->findWormById(wormId);
	if (aWorm->getPlayer().compare(this->playerId)==0)
	{
			return true;
	} 
	else
	{
			return false;
	}
}

void GameActivity::setMessageView(std::string msg)
{
	GameView* gameView = static_cast<GameView*>(this->aView);
	gameView->getStateBar()->setMsj(msg);
}

void GameActivity::showMessageError(std::string msg)
{
	GameView* gameView = static_cast<GameView*>(this->aView);
	gameView->getStateBar()->setMsjError(msg);
}

void GameActivity::showMessageInfo(std::string msg)
{
	GameView* gameView = static_cast<GameView*>(this->aView);
	gameView->getStateBar()->setMsjInfo(msg);
}

void GameActivity::OnMovement(MovementEvent e)
{
	Playable p;
//	Util::clean(p);

	//no lo dejo mover si va a disparar
	/*if(aimView->isShootEnter()){
		return;
	}*/

	int wormIdSelected = this->getWormIdSelected();
	
	

	if (wormIdSelected > 0 && 
		this->isThisClientOwner(wormIdSelected) && 
		this->isAlive(wormIdSelected))
	{
		

		p.wormid = wormIdSelected;
		if ((e.y == -1) && !aimView->isShootEnter())  // Solo saltar
		{
			if (e.x == 1) //Salta derecha
			{
				p.action = 	JUMP_RIGHT;
				Log::t("CLIENTE: Saltar derecha");
			}
			else if (e.x == -1) // Saltar izquierda
			{
				p.action = 	JUMP_LEFT;
				Log::t("CLIENTE: Saltar izquierda");
			} 
			else 
			{
				p.action = 	JUMP;
				Log::t("CLIENTE: Saltar");
			}
			/*
			if (weaponSelected == BAZOOKA && 
				weaponSelected == GRENADE && 
				weaponSelected == HMISSILE && 
				weaponSelected == HOLY)
			{
				Log::i("CLIENTE: No salto porque tengo un arma con mira");
				return;
			}*/
		}
		else if (e.x == 1) // derecha
		{
			p.action = 	MOVE_RIGHT;
		}
		else if (e.x == -1) // izquierda
		{
			p.action = 	MOVE_LEFT;
		} 
		else if (e.x == 0) // quieto
		{
			p.action = 	MOVE_STOP;
		}
		//if(this->isAlive(wormIdSelected))
		//	updater.addLocalMovementFromView(p);//Esta linea me pincha el server by ERIK
		this->ActionResult(CALL_MOVE, &p, NULL);


	}

	
}


void GameActivity::OnAction(ActionEvent e){
	//Log::i("ASD: %d", (int)e.action);
	ActionWorm actionWorm;
	GameView* gameView = static_cast<GameView*>(this->aView);
	switch(e.action){
		case MENU: 
			this->actionMenu();
			break;
		case SHOOT:
			{  
				if(aimView->isShootMouse()){
					return;//no puedo disparar con shootEnter
				}
				
				if (this->wormIdSelected>0 && this->idWeapon!=NO_WEAPON) {

					if(this->idWeapon == HMISSILE){
					//TODO: @Ari terminalo
						if(this->isObjetive()){
							/*updater.doShoot(this->wormIdSelected, 
								HMISSILE, 
								this->xHmissile, 
								this->yHmissile, 
								e.factor);
							updater.doUnselectWapon(wormIdSelected, HMISSILE);*/
							deselectPreviewsWeapon();
							afterShoot = true;
							this->aimView->unAim();
						}
						this->iniHmissile();
						return; //proceso y me voy
					}


					
					WormView * aWormView = gameView->findWormById(this->wormIdSelected);
					int factor = e.factor;
					int xMira= e.xAim;
					int yMira= e.yAim;

					if(aimView->isShootEnter()){
						std::pair<int, int> data = this->aimView->getData();
						int angle = this->aimView->getAngle();
						xMira = yMira = angle;
						aimView->unAim();
					} 
					Log::i("\nShoot 2: x %d, y %d, factor %d",xMira,yMira,factor);

					if (this->idWeapon == DYNAMITE || this->idWeapon == SHEEP)
					{
						if (aWormView->getDirection() == D_LEFT) {
						xMira = -1;
						} else {
							xMira = 1;
						}
					}
					//updater.doShoot(this->wormIdSelected, this->idWeapon, xMira, yMira, factor);
					//updater.doUnselectWapon(wormIdSelected, this->idWeapon);
					actionWorm.x = xMira;
					actionWorm.y = yMira;
					//actionWorm.angle = ???;
					actionWorm.factor = factor;

					this->ActionResult(CALL_SHOOT, NULL, &actionWorm);

					//this->ActionResult(CALL_UNWEAPON, NULL, NULL);  // Esto no esta funcionando, ya lo hace el modelo
					
					deselectPreviewsWeapon();
					afterShoot = true;
					this->iniHmissile();
				}
			}
			break;
		default: ;
	}
}

void GameActivity::actionMenu(){
	GameView* gameView = static_cast<GameView*>(this->aView);
	gameView->actionMenu();
}

void GameActivity::offMenu(){
	GameView* gameView = static_cast<GameView*>(this->aView);
	gameView->offMenu();
}


bool GameActivity::isObjetive(){
	return ((this->xHmissile != -1)
		&&(this->yHmissile != -1));
}

void GameActivity::iniHmissile(){
	this->xHmissile =
	this->yHmissile = -1;
}



void GameActivity::ActionResult(CallClient call, Playable* p, ActionWorm *aw){
	//if(validateWormBeforeCall()){
		//Se loguea las acciones del worm contra el server
		this->ActionResultLog(call, p, aw);
		switch(call){
		case CALL_MOVE:
			if (p->action == MOVE_LEFT || p->action == MOVE_RIGHT) {
				try {
					GameView* gameView = static_cast<GameView*>(this->aView);
					WormView* wormView = gameView->findWormById(this->getWormIdSelected());
					if (wormView->isJumping()) {
						return;
					}
				} catch (GameElement & e) {
					Log::e("GameActivity::ActionResult() Worm view no encontrado %d", this->getWormIdSelected());			
				}
			}
			updater.addLocalMovementFromView(*p);
			break;
		case CALL_SHOOT:
			updater.doShoot(this->wormIdSelected, this->idWeapon, aw->x, aw->y, aw->factor);
			break;
		case CALL_UNWEAPON:
			updater.doUnselectWapon(wormIdSelected, this->idWeapon, aw->dim);
			break;
		case CALL_WEAPON:
			updater.doSelectWapon(wormIdSelected, this->idWeapon, aw->dim);
			break;
		case CALL_STOPWORM:
			updater.doStopWorm(aw->id);
			break;
		case CALL_MOVEVIEW:
			this->updater.notify(this->wormIdSelected, aw->moveView, this->idWeapon);
			break;
		}

		/*if(!this->validateWormAlive()){
			GameView* gameView = static_cast<GameView*>(this->aView);
			WormView * aWormView = gameView->findWormById(this->wormIdSelected);	
			aWormView->setLastWords(false);
		}*/
	//}
	/*else{
		
	}
*/
}

bool GameActivity::validateWormBeforeCall(){
	return(this->validateWormAlive()
		|| this->validateWormLastWords());
}

bool GameActivity::validateWormAlive(){
	GameView* gameView = static_cast<GameView*>(this->aView);
	try {
		WormView * aWormView = gameView->findWormById(this->wormIdSelected);
		return aWormView->isAlive();
	} catch (GameException & e) {
		Log::e(e.what());
		return false;
	}
	
}

bool GameActivity::validateWormLastWords(){
	GameView* gameView = static_cast<GameView*>(this->aView);
	WormView * aWormView = gameView->findWormById(this->wormIdSelected);
	return aWormView->isLastWords();
}


void GameActivity::ActionResultLog(CallClient call, Playable* p, ActionWorm *aw){
	char *msj = NULL;
	switch(call){
		case CALL_MOVE:
			msj = "MOVER";
			break;
		case CALL_SHOOT:
			msj = "DISPARAR";
			break;
		case CALL_UNWEAPON:
			msj = "QUTAR SU ARMA";
			break;
		case CALL_WEAPON:
			msj = "EQUIPAR SU ARMA";
			break;
		}
	if(this->auxCallLog != call){
		this->auxCallLog = call;
		Log::i(GAME_ACTIVITY,"El worm con id=%2d ejecutar la accion de %s sobre el servidor",
			this->wormIdSelected, msj);
	}
}


bool GameActivity::isWeaponWithOutPower(){
	return (this->idWeapon == AIRATTACK
		|| this->idWeapon == BURRO
		|| this->idWeapon == HMISSILE
		|| this->idWeapon == DYNAMITE
		|| this->idWeapon == SHEEP
		|| this->idWeapon == SUICIDE);
}