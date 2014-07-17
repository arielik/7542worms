#include "GameViewBuilder.h"




GameViewBuilder::GameViewBuilder(GameDomain* domain, SDLScreen * screen)
	: domain(domain), screen(screen)
{
	gameView = NULL;
}



GameViewBuilder::~GameViewBuilder(void)
{
	if (gameView) delete gameView;

}


void GameViewBuilder::buildContainer()
{

	std::pair<int, int> dimension = TextureManager::Instance().getDimension("eart");
	gameView = new GameView(0,0,dimension.first, dimension.second);
	gameView->setProjectileContainer(new ProjectileViewGroup(0,0));
}

void GameViewBuilder::buildExplosionContainter()
{
	gameView->setExplosionContainer(new ExplosionViewGroup(0,0));
}


void GameViewBuilder::buildProjectileContainer()
{
	gameView->setProjectileContainer(new ProjectileViewGroup(0,0));
}

void GameViewBuilder::buildSky()
{
	SkyView* skyView = new SkyView("sky");
	try {
		skyView->sprites["nuve"] = SpriteConfigurator::Instance().get("nuve");
	} 
	catch (GameException & e) 
	{
		Log::e(e.what());
	}
	gameView->setSky(skyView);
}

void GameViewBuilder::buildEart()
{
	gameView->setEart(new EartView("eart"));
}

void GameViewBuilder::buildFigures()
{
	std::map<int,GameElement>::iterator it;
	Log::d(VIEW_BUILDER,"Construyendo Figuras. Cantidad = %d", this->domain->getDomainElements()->size() );

	ParserYaml* aParser = ParserYaml::getInstance();

	for (it = this->domain->getDomainElements()->begin(); it != this->domain->getDomainElements()->end(); ++it)
	{
		GameElement domainElement = it->second;
		FigureView* aFigure = 0;
		std::string color= aParser->getColorById(Util::int2string(domainElement.getId()));
		if (domainElement.getType() == CIRCLE) 
		{
			Log::d("Creando CIRCULO");


			float radius = domainElement.getRadiusScaled();
			Log::t("Radio: %f", radius);

			EllipseView* aCircle = new EllipseView(color);
			aCircle->updateRadius(radius);
			aCircle->updatePositions(domainElement.getPosition());
			aCircle->setId(domainElement.getId());
			aFigure = aCircle;

		} 
		else if (domainElement.getType() == SQUARE) 
		{
			Log::d("Creando RECTANGULO");
			RectangleView* aRectangle = new RectangleView(color);
			aRectangle->updateVertex(domainElement.getVertex());
			aRectangle->setId(domainElement.getId());
			aFigure = aRectangle;
		}
		else if (domainElement.getType() == TRIANGLE) 
		{
			Log::d("Creando TRIANGULO");
			TriangleView* aTriangle = new TriangleView(color);
			aTriangle->updateVertex(domainElement.getVertex());
			aTriangle->setId(domainElement.getId());
			aFigure = aTriangle;
		}
		else if (domainElement.getType() == PENTA) 
		{
			Log::d("Creando PENTAGONO");
			PentagonView* aPentagon = new PentagonView(color);
			aPentagon->updateVertex(domainElement.getVertex());
			aPentagon->setId(domainElement.getId());
			aFigure = aPentagon;
		}
		else if (domainElement.getType() == HEXAGON) 
		{
			Log::d("Creando HEXAGONO");
			HexagonView* aHexagon = new HexagonView(color);
			aHexagon->updateVertex(domainElement.getVertex());
			aHexagon->setId(domainElement.getId());
			aFigure = aHexagon;
		}
		if (aFigure) 
		{
			this->gameView->putFigure(aFigure->getId(), aFigure);
			aFigure = 0;
		}

	}
}

void GameViewBuilder::buildWater()
{
	ParserYaml* aParser = ParserYaml::getInstance();
	std::string color = aParser->getEscenarioColorAgua();
	
	int scale = ESCALA_UL2PX;
	
	int heigth = (int)( Util::string2float( aParser->getEscenarioAgua() ) * scale);
	
	gameView->setWater(new WaterView(heigth, color));
}

void GameViewBuilder::buildTerrain()
{	//ARIEL: Comento porque esto dibujaba en base a poligonos
	//Log::d("Creando TERRENO en vista");
	//ParserYaml* aParser = ParserYaml::getInstance();
	//std::string color = aParser->getEscenarioColorTierra();

	//TerrainView* aTerrain = new TerrainView(color);

	//list< list< pair<float,float> > > * polygonsPoint = this->cLevel->getTerrain()->getListOfPolygons();
	//list< list< pair<float,float> > >::iterator itPolygons;

	//int countPolygons = 0;

	//std::list<std::list<tPoint>> polygonsToView;
	//for (itPolygons = polygonsPoint->begin(); itPolygons!=polygonsPoint->end(); ++itPolygons) 
	//{
	//	countPolygons++;
	//	Log::t("Creando polygono nro: %d", countPolygons);
	//	list< pair< float, float> > ::iterator itPoints;	
	//	list< pair<float,float> > points = (*itPolygons);


	//	std::list<tPoint> pointsToView;
	//	for (itPoints = points.begin(); itPoints!=points.end(); ++itPoints) 
	//	{
	//		Log::t("----> Punto: %f %f", itPoints->first, itPoints->second);
	//		tPoint aPoint = Util::convertPointUL2PXSDL(itPoints->first, itPoints->second);
	//		
	//		pointsToView.push_back(aPoint);
	//	}
	//	polygonsToView.push_back(pointsToView);
	//}

	//delete polygonsPoint;
	//
	//std::list<std::list<tPoint>>::iterator it;

	//for (it = polygonsToView.begin(); it != polygonsToView.end(); ++it)
	//{
	//	aTerrain->buildPart((*it));
	//}

	//this->gameView->setTerrain(aTerrain);
}

//void GameViewBuilder::addElementToDomain(GameElement element){
//
//	this->domainElements.insert( std::make_pair(element.getId(),element) );
//
//}




void GameViewBuilder::buildCharacters()
{
	WormViewGroup* aWormGroup = new WormViewGroup(0,0);
	std::map<int,GameElement>::iterator it;

	for (it = this->domain->getDomainElements()->begin(); it != this->domain->getDomainElements()->end(); ++it)
	{
		GameElement domainElement = it->second;

		if (domainElement.getType() == WORM) 
		{
			WormView* aWorm = createWorm(&domainElement);
			aWormGroup->add(aWorm);
		} 
	}
	this->gameView->setWormContainer(aWormGroup);
}

void GameViewBuilder::buildStateBar()
{
	StateBarView* stateBar = new StateBarView();
	this->gameView->setStateBar(stateBar);
}

void GameViewBuilder::buildMenuWeapon(){
	MenuWeaponView* menuWeapon = new MenuWeaponView(30,20);
	menuWeapon->buildWeapon();
	int cantArmas = ParserYaml::getInstance()->getCantArm();
	list<WeaponId> allowW;

	//int indiceArmas = 0;
	//for (indiceArmas=0; indiceArmas<cantArmas; indiceArmas++)
	//{
	//	std::string tipo = ParserYaml::getInstance()->getArmaTipo(indiceArmas);
	//	std::string habilitado = ParserYaml::getInstance()->getArmaHab(indiceArmas);
	//	if (habilitado.compare("si") == 0) {
	//		if (tipo.compare("bazooka") == 0) {
	//			allowW.push_back(BAZOOKA);
	//		}
	//		if (tipo.compare("granada") == 0) {
	//			allowW.push_back(GRENADE);
	//		}
	//		if (tipo.compare("dinamita") == 0) {
	//			allowW.push_back(DYNAMITE);
	//		}
	//		if (tipo.compare("holy") == 0) {
	//			allowW.push_back(HOLY);
	//		}
	//		if (tipo.compare("burro") == 0) {
	//			allowW.push_back(BURRO);
	//		}
	//		if (tipo.compare("banana") == 0) {
	//			allowW.push_back(BANANA);
	//		}
	//		if (tipo.compare("aereo") == 0) {
	//			allowW.push_back(AIRATTACK);
	//		}
	//	}
	//}

	// tomar desde yaml y usar los siguiente. Agregar solo los permitidos
	
	allowW.push_back(BAZOOKA);
	allowW.push_back(GRENADE);
	allowW.push_back(HOLY);
	allowW.push_back(BURRO);
	allowW.push_back(DYNAMITE);
	allowW.push_back(AIRATTACK);
	allowW.push_back(BANANA);
	//allowW.push_back(HMISSILE);
	allowW.push_back(SHEEP);
	//allowW.push_back(SUICIDE);

	menuWeapon->allowWeapon(allowW);


	this->gameView->setMenuWeapon(menuWeapon);
}

void GameViewBuilder::buildWaterImg(){
	WaterViewImg* wvi = new WaterViewImg();
	this->gameView->setWaterImg(wvi);
}

void GameViewBuilder::buildWaterSurfImg(){
	WaterViewImg* wvi = WaterViewImg::FactoryWater(47,0.5, true);
	WaterViewImg* wvi2 = WaterViewImg::FactoryWater2(42,0.5, false);
	std::list<WaterViewImg*> listWvi;
	listWvi.push_back(wvi);
	listWvi.push_back(wvi2);
	this->gameView->setWaterSurfImg(listWvi);
}

WormView* GameViewBuilder::createWorm(GameElement * domainElement)
{
		WormView* aWorm = new WormView(	domainElement->getId());
		Log::i("Adding worm: %d, at position: %f, %f", domainElement->getId(), 
													   domainElement->getPosition().first, 
													   domainElement->getPosition().second);
		aWorm->update(domainElement);

		std::stringstream name;
		name<<domainElement->getPlayerID()<<" "<< domainElement->getId();

		aWorm->setColor((TeamColors)this->getDomain()->getPlayerColor(domainElement->getPlayerID()));
		aWorm->setPlayer(domainElement->getPlayerID());
		aWorm->setUserLabel(name.str());
		aWorm->setName(name.str());

		try 
		{

			aWorm->sprites["caminar"] = SpriteConfigurator::Instance().get("caminar");
			aWorm->sprites["bazooka"] = SpriteConfigurator::Instance().get("bazooka");
			aWorm->sprites["dinamita"] = SpriteConfigurator::Instance().get("dinamita");
			aWorm->sprites["granada"] = SpriteConfigurator::Instance().get("granada");
			aWorm->sprites["holy"] = SpriteConfigurator::Instance().get("holy");
			aWorm->sprites["radio"] = SpriteConfigurator::Instance().get("radio");
			aWorm->sprites["saltar"] = SpriteConfigurator::Instance().get("saltar");
			aWorm->sprites["morir"] = SpriteConfigurator::Instance().get("morir");
			aWorm->sprites["cripta"] = SpriteConfigurator::Instance().get("cripta");
			aWorm->sprites["oveja"] = SpriteConfigurator::Instance().get("oveja");
			aWorm->sprites["banana"] = SpriteConfigurator::Instance().get("banana");
			aWorm->sprites["explosion"] = SpriteConfigurator::Instance().get("circle25");
		} 
		catch (std::exception & e) 
		{
			Log::e(e.what());
			return NULL;
		}
		return aWorm;
}


ProjectileView*  GameViewBuilder::createBullet(GameElement* domainElement, int type)
{
	ProjectileView*  aProjectile = NULL;

	try 
	{
		if (type == GRENADE) {
			aProjectile = new GrenadeView(domainElement->getId());
			aProjectile->setSpriteBullet(SpriteConfigurator::Instance().get("bullet_granada"));
			aProjectile->setSpriteExplosion(SpriteConfigurator::Instance().get("circle50"));
			aProjectile->setLifeInitial(domainElement->getLife());
		} else if (type == BAZOOKA) { 
			aProjectile = new BazookaView(domainElement->getId());
			aProjectile->setSpriteBullet(SpriteConfigurator::Instance().get("bullet_bazooka"));
			aProjectile->setSpriteExplosion(SpriteConfigurator::Instance().get("circle50"));
		} else if (type == HOLY) { 
			aProjectile = new HolyView(domainElement->getId());
			aProjectile->setSpriteBullet(SpriteConfigurator::Instance().get("bullet_holy"));
			aProjectile->setSpriteExplosion(SpriteConfigurator::Instance().get("circle100"));
			aProjectile->setLifeInitial(domainElement->getLife());
		} else if (type == DYNAMITE) { 
			aProjectile = new DynamiteView(domainElement->getId());
			aProjectile->setSpriteBullet(SpriteConfigurator::Instance().get("bullet_dinamita"));
			aProjectile->setSpriteExplosion(SpriteConfigurator::Instance().get("circle75"));
			aProjectile->setLifeInitial(domainElement->getLife());
		} else if (type == AIRATTACK) { 
			aProjectile = new AirStrikeView(domainElement->getId());
			aProjectile->setSpriteBullet(SpriteConfigurator::Instance().get("bullet_airmisl"));
			aProjectile->setSpriteExplosion(SpriteConfigurator::Instance().get("circle50"));
		} else if (type == BURRO) { 
			aProjectile = new DonkeyView(domainElement->getId(), "donkey");		
			aProjectile->setSpriteExplosion(SpriteConfigurator::Instance().get("circle100"));
		} else if (type == BANANA ) { 
			aProjectile = new BananaView(domainElement->getId());
			aProjectile->setSpriteBullet(SpriteConfigurator::Instance().get("bullet_banana"));
			aProjectile->setSpriteExplosion(SpriteConfigurator::Instance().get("circle50"));
			aProjectile->setLifeInitial(domainElement->getLife());
		} else if (type == BANANITA ) { 
			aProjectile = new BananaView(domainElement->getId());
			aProjectile->setSpriteBullet(SpriteConfigurator::Instance().get("bullet_banana"));
			aProjectile->setSpriteExplosion(SpriteConfigurator::Instance().get("circle50"));
			aProjectile->setLifeInitial(domainElement->getLife());
		}else if (type == SHEEP ) { 
			aProjectile = new SheepView(domainElement->getId());
			aProjectile->setSpriteBullet(SpriteConfigurator::Instance().get("bullet_sheep"));
			aProjectile->setSpriteExplosion(SpriteConfigurator::Instance().get("circle50"));
			aProjectile->setLifeInitial(domainElement->getLife());
		}else {
			aProjectile = new GrenadeView(domainElement->getId());
			aProjectile->setSpriteBullet(SpriteConfigurator::Instance().get("bullet_default"));
			aProjectile->setSpriteExplosion(SpriteConfigurator::Instance().get("circle25"));
			aProjectile->setLifeInitial(domainElement->getLife());
		}
	} 
	catch (std::exception & e) 
	{
		Log::e(e.what());
		return NULL;
	}
	return aProjectile;
}

ExplosionView* GameViewBuilder::createExplosion(float x, float y, int radio)
{
	tPoint pointSDL = TextureManager::Instance().convertPointUL2PXSDL(x, y);
	ExplosionView* explosionView = new ExplosionView(pointSDL.x, pointSDL.y);
	try 
	{
		explosionView->setSpriteExplosion(SpriteConfigurator::Instance().get("circle100"));
	}
	catch (std::exception & e) 
	{
		Log::e(e.what());
		return NULL;
	}
	return explosionView;
}

void GameViewBuilder::buildPlayerProgress()
{
	PlayerProgressView* pProgressView = new PlayerProgressView(this->getDomain()->getPlayersLife(), this->getDomain()->getPlayersPlaying());
	this->gameView->setPlayerProgressView(pProgressView);
}

void GameViewBuilder::buildPower(GameController* cController)
{
	int w = TextureManager::Instance().getScreenWidth();

	PowerView* powerView = new PowerView(w-100, 10);
	cController->addOnChangeListener(powerView);
	this->gameView->setPowerView(powerView);
}

void GameViewBuilder::buildTimer()
{
	TimerView* timerView = new TimerView(0, 10);
	this->gameView->setTimerView(timerView);
}