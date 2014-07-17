#include "GameEngine.h"
#include <list>
#include "Box2D/Collision/Shapes/b2Shape.h"
#include "Box2D/Collision/b2Collision.h"
#include "Exceptions\ContourException.h"
#include "..\..\utils\ParserYaml.h"


#define UPDATE_STEPS 3
#define WATER_VELOCITY -2
#define WEAPON_STARTING_ID 100
#define BLAST_RADIUS 15
#define BLAST_FORCE 600

class b2Collision;


GameEngine::GameEngine() {
	this->gameLevel = new GameLevel();
	this->weaponUniquedId = WEAPON_STARTING_ID;
	this->myTimer.start();
	this->didWeShoot = false;
	this->amountOfMissils = 0;
}

void GameEngine::destroyWorld(){

	delete this->gameLevel;
	delete this->myWorld;
	delete this->aTerrainProcessor;
	delete this->gameBodies;
	delete this->gameWeapons;

	this->mapExplosions.clear();

	this->weaponUniquedId = WEAPON_STARTING_ID;
	this->myTimer.start();
	this->didWeShoot = false;
	this->amountOfMissils = 0;

}

int GameEngine::getWeaponUniqueId(){
	int id = this->weaponUniquedId;
	this->weaponUniquedId = this->weaponUniquedId + 1;
	return id;
}

GameEngine::~GameEngine() {

}

bool GameEngine::initWorld(){

	this->getLevel()->updateStep = 0;

	this->gameBodies = new map<int,Body*>;
	//Crea mundo en base a defaults (Gravity y otros coeficientes)
	animateWorld();

	//Carga nivel (desde el YAML)
	this->gameLevel->createLevel(this->gameLevel);
	

	this->floodWorld();

	//Create terrain from BMP
	ParserYaml* aParser=ParserYaml::getInstance();

	this->timeStep = 1.0 / TIME_STEP;//Util::string2float(aParser->getMetaTime());
	Log::i("TimeStep: %f",this->timeStep);

	//try{
		/*aTerrainProcessor=new TerrainProcessor();
		aTerrainProcessor->process(this->myWorld,(char*)aParser->getEscenarioTierra().c_str(),atof(aParser->getMetaEps().c_str()),atoi(aParser->getMetaSca().c_str()),atoi(aParser->getEscenarioAgua().c_str()));*/
	//}
	//catch(ContourExp e){
	//	Log::e("SE CARGA TERRENO POR DEFECTO, res/images/terrain1.png, TEMPANOS DE HIELO");
	//	aParser->setTerrain("res/images/terrain1.png");
	//	aParser = ParserYaml::getInstance(aParser->getFilePath().c_str());
	//	aTerrainProcessor=new TerrainProcessor(this->myWorld,(char*)aParser->getEscenarioTierra().c_str(),atof(aParser->getMetaEps().c_str()),atoi(aParser->getMetaSca().c_str()),atoi(aParser->getEscenarioAgua().c_str()));
	//}
	
	this->gameLevel->setTerrain(this->myWorld,(char*)aParser->getEscenarioTierra().c_str(),atof(aParser->getMetaEps().c_str()),atoi(aParser->getMetaSca().c_str()),atoi(aParser->getEscenarioAgua().c_str()));

	
	//Crea cuerpos en base a elementos del nivel (la logica de posicionamiento primero en el modelo puro de objetos)
	this->animateBodies();

	this->animateContacts();
	Log::i("End animation");
	return true;
}

bool GameEngine::getExplosion( Explosion e ){
	
	if ( !this->lastExplosions.empty() ){
		e = this->lastExplosions.front();
		this->lastExplosions.pop();
		return true;
	}
	return false;
}


void GameEngine::floodWorld(){

	Log::d("Creando nivel de agua");
	Water* myWater = new Water( this->gameLevel->getWaterLevel(),
								this->myWorld);
	this->water = myWater;

}



void GameEngine::animateWorld() {
	//ToDo: hardcoded gravity
	this->myWorld = new b2World(b2Vec2(0,-10.0));
	this->myWorld->SetGravity(b2Vec2(0,-10));
	//this->myContactListener = new ContactListener();
	this->myContactListener = ContactListener();
	this->myWorld->SetContactListener(&this->myContactListener);

}


void GameEngine::animateBodies() {

	// Recorro todos los elementos del nivel y por cada uno de ellos armo el cuerpo de box2d		
	std::map<int, GameElement*> mmap = this->gameLevel->getEntities();
	std::map<int, GameElement*>::iterator elems = mmap.begin();
	Log::d("Creando %d cuerpos",mmap.size());
	for ( ; elems != mmap.end(); elems++) {
		
		switch ((*elems).second->getType()){
			// Match de tipos y creacion de elementos en base a ello.
			case SQUARE:
				{
					Cuadrado* sq = new Cuadrado(SQUARE, 
											(*elems).second->getPosition().first , 
											(*elems).second->getPosition().second, 
											(*elems).second->getHeight(), 
											(*elems).second->getWidth(), 
											(*elems).second->getMass(),
											(*elems).second->getRotation(), 
											this->myWorld, 
											((*elems).second),
											(*elems).second->isFixed());
					(*elems).second->setBody(sq);
					Log::t("Puntero cuadrado: %p",sq); 
					this->gameBodies->insert(std::pair<int,Body*>((*elems).second->getId(),sq) );
				}
				break;
			case CIRCLE:
				{
					Circle* sq = new Circle(CIRCLE, 
							(*elems).second->getPosition().first , 
							(*elems).second->getPosition().second,
							(*elems).second->getRadius(), 
							(*elems).second->getScale(), 
							(*elems).second->getMass(),
							this->myWorld, 
							(*elems).second,
							(*elems).second->isFixed());

					(*elems).second->setBody(sq);

					Log::t("Puntero circulo: %p",sq); 
					this->gameBodies->insert(std::pair<int,Body*>((*elems).second->getId(),sq) );
				}
				break;
			case HEXAGON:
				{
					Hexagon* sq = new Hexagon(HEXAGON, 
							(*elems).second->getPosition().first , 
							(*elems).second->getPosition().second,
							(*elems).second->getScale(), 
							(*elems).second->getMass(),
							(*elems).second->getRotation(),
							this->myWorld, 
							(*elems).second,
							(*elems).second->isFixed());

					(*elems).second->setBody(sq);

					Log::t("Puntero hexagono: %p",sq); 
					this->gameBodies->insert(std::pair<int,Body*>((*elems).second->getId(),sq) );
				}
				break;
			case TRIANGLE:
				{
					Triangle* sq = new Triangle(TRIANGLE, 
							(*elems).second->getPosition().first , 
							(*elems).second->getPosition().second,
							(*elems).second->getScale(), 
							(*elems).second->getMass(),
							(*elems).second->getRotation(),
							this->myWorld, 
							(*elems).second,
							(*elems).second->isFixed());

					(*elems).second->setBody(sq);

					Log::t("Puntero TRIANGULO: %p",sq); 
					this->gameBodies->insert(std::pair<int,Body*>((*elems).second->getId(),sq) );
				}
				break;
			case PENTA:
				{
					Pentagon* sq = new Pentagon(PENTA, 
							(*elems).second->getPosition().first , 
							(*elems).second->getPosition().second,
							(*elems).second->getScale(), 
							(*elems).second->getMass(),
							(*elems).second->getRotation(),
							this->myWorld, 
							(*elems).second,
							(*elems).second->isFixed());

					(*elems).second->setBody(sq);

					Log::t("Puntero PENTAGONO: %p",sq); 
					this->gameBodies->insert(std::pair<int,Body*>((*elems).second->getId(),sq) );
				}
				break;
		}


	}

}

void GameEngine::animateWormsFromPlayer(std::string playerID){

	std::map<int, GameElement*> mmap = this->gameLevel->getEntities();
	std::map<int, GameElement*>::iterator elems = mmap.begin();
	//Log::d("Creando cuerpos del player %s",playerID.c_str() );
	//printf("\nCreando cuerpos del player %s",playerID.c_str() );
	for ( ; elems != mmap.end(); elems++) {
		if ( !elems->second->getPlayerID().compare(playerID) ){
			Worm2d* gus = new Worm2d(WORM,
								elems->second->getPosition().first,
								elems->second->getPosition().second,
								MODEL_WORM_HEIGHT,
								MODEL_WORM_WIDTH,
								elems->second->getMass(),
								0,
								this->myWorld,
								((*elems).second),
								false
								);

			(*elems).second->setBody(gus);
			//printf("\nPuntero Gusano: %p",gus); 
			this->gameBodies->insert(std::pair<int,Body*>((*elems).second->getId(),gus) );
		}
	}
}

bool GameEngine::registerPlayer(std::string playerID){

	PlayerAccounting retval = this->gameLevel->acceptPlayer(playerID);
	
	if (retval == NEW_PLAYER){
		//Now animate new worms into the world
		animateWormsFromPlayer(playerID);
		return true;
	}

	if ( retval == EXISTING_PLAYER){
		
		return true;
	}
	return false;
	
}





float GameEngine::getTimeStep () {
	return timeStep;
}


float GameEngine::applyBlastImpulse(b2Body* body, b2Vec2 blastCenter, b2Vec2 applyPoint, float blastPower) {
	b2Vec2 blastDir = applyPoint - blastCenter;
	float distance = blastDir.Normalize();
	//ignore bodies exactly at the blast point - blast direction is undefined, but do maximum damage!
	if ( distance == 0 )
		return distance;
	float invDistance = 1 / distance;
	float impulseMag = blastPower * invDistance * invDistance ; //* invDistance;
	body->ApplyLinearImpulse( impulseMag * blastDir, applyPoint );

	return distance;

}


void GameEngine::doOndaExpansiva(b2Vec2 center, float blastRadius, float m_blastPower, int maxDamage ){
	
	int numRays = 32;
	std::vector<GameElement*> damagedBodies;
	Log::t("Proceso onda expansiva");
	for (int i = 0; i < numRays; i++) {
		float angle = (i / (float)numRays) * 360 * DEGTORAD;
		b2Vec2 rayDir( sinf(angle), cosf(angle) );
		b2Vec2 rayEnd = center + blastRadius * rayDir;
  
		// Uso un raycast callback para tener una referencia a los cuerpos que toco dentro del radio
		RayCastClosestCallbackExplosion callback;
		this->myWorld->RayCast(&callback, center, rayEnd);

		if ( callback.m_body ) {
			
			if ( callback.m_body->GetFixtureList()->GetUserData() == (void*)UD_WORMS ){

				if ( !static_cast<GameElement*>(callback.m_body->GetUserData())->damaged ){
					static_cast<Worm2d*>(callback.m_body->GetUserData())->damaged = true;
					damagedBodies.push_back( static_cast<GameElement*>(callback.m_body->GetUserData()) );

					//Impulsar
					float distance = applyBlastImpulse(callback.m_body, center, callback.m_point, m_blastPower);

					//Calcular damage en base a distancia
					float factor = (float)(BLAST_RADIUS - distance)/ (float)BLAST_RADIUS;
				
					int damage = factor * maxDamage;
					Log::i("\nDoing damage of %d to worm %d cause it's at a distance of %f",damage,
						static_cast<GameElement*>(callback.m_body->GetUserData())->getId(),distance);
					//Damage
					static_cast<GameElement*>(callback.m_body->GetUserData())->subLife(damage);
				}
			}
		}
	}

	for ( int i = 0; i < damagedBodies.size(); i++){
		damagedBodies[i]->damaged = false;
	}


}



int GameEngine::step(){

	//Simulo (1 step) - default values Box2D
	this->myWorld->Step(this->timeStep,8,3);

	//Guardo aqui los ID de los cuerpos a eliminar
	std::vector<int> bodiesToDelete;

	int retval = 0;

	//Reflect model - for every body (worm)
	std::map<int,Body*>::iterator iterator = this->gameBodies->begin();
	for(iterator = this->gameBodies->begin();
		 iterator != this->gameBodies->end();
		++iterator) {
			
		/* Animacion de worms */
		if ( iterator->second->type == WORM ){
			if ( !static_cast<Worm*>(static_cast<Worm2d*>(iterator->second)->body->GetUserData())->isAlive() ){
				//Viene muerto del ciclo anterior, lo elimino
				//static_cast<Worm2d*>(iterator->second)->makeTumb();
				bodiesToDelete.push_back( static_cast<Worm*>(static_cast<Worm2d*>(iterator->second)->body->GetUserData())->getId() );
			}else{
				Worm2d* aBody = static_cast<Worm2d*>(iterator->second);
				aBody->animate();
			}
		}

		/* Animacion de misiles */
		if ( iterator->second->type ==	WEAPON ) {
			
			/* Eliminacion de misiles */
			if ( static_cast<Missile*>(static_cast<Missile2d*>(iterator->second)->body->GetUserData())->hasExploded() && 
				 (static_cast<GameElement*>(static_cast<Missile2d*>(iterator->second)->body->GetUserData())->getWeaponId() != BAZOOKA &&
				  static_cast<GameElement*>(static_cast<Missile2d*>(iterator->second)->body->GetUserData())->getWeaponId() != AIRATTACK &&
				  static_cast<GameElement*>(static_cast<Missile2d*>(iterator->second)->body->GetUserData())->getWeaponId() != BURRO ) ){
				printf("\nElimino misil");
				// Viene explotado del ciclo anterior, lo elimino
				bodiesToDelete.push_back( static_cast<Missile*>(static_cast<Missile2d*>(iterator->second)->body->GetUserData())->getId() );


/* +BAZOOKA & AIRATTACK: Explosion de la bazooka (manejada desde el contact listener) ++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */

			}else if ( static_cast<Missile*>(static_cast<Missile2d*>(iterator->second)->body->GetUserData())->hasExploded() &&
					   (static_cast<GameElement*>(static_cast<Missile2d*>(iterator->second)->body->GetUserData())->getWeaponId() == BAZOOKA ||
					    static_cast<GameElement*>(static_cast<Missile2d*>(iterator->second)->body->GetUserData())->getWeaponId() == AIRATTACK)){

				this->addExplosion( static_cast<Missile*>(static_cast<Missile2d*>(iterator->second)->body->GetUserData())->getPosition().first,
					static_cast<Missile*>(static_cast<Missile2d*>(iterator->second)->body->GetUserData())->getPosition().second,
					static_cast<Missile2d*>(iterator->second)->getExplosion().radio 
					);

					
				// Hago agujero en Box2d
				this->doExplosion( b2Vec2( 
					static_cast<Missile*>(static_cast<Missile2d*>(iterator->second)->body->GetUserData())->getPosition().first,
					static_cast<Missile*>(static_cast<Missile2d*>(iterator->second)->body->GetUserData())->getPosition().second),
					static_cast<Missile2d*>(iterator->second)->getExplosion().radio,
					static_cast<Missile*>(static_cast<Missile2d*>(iterator->second)->body->GetUserData())->getWeaponId()
					);

				static_cast<Missile*>(static_cast<Missile2d*>(iterator->second)->body->GetUserData())->setAction(EXPLOSION);
				static_cast<Missile*>(static_cast<Missile2d*>(iterator->second)->body->GetUserData())->changed = true;

				// Marco como inactivo para borrar en el proximo ciclo
				static_cast<Missile2d*>(iterator->second)->body->SetActive(false);

				this->myTimer.reset();

				//Cambio weaponId para eliminar en el proximo ciclo
				static_cast<GameElement*>(static_cast<Missile2d*>(iterator->second)->body->GetUserData())->setWeapon(NO_WEAPON);
				static_cast<Missile*>(static_cast<Missile2d*>(iterator->second)->body->GetUserData())->drowned = true;
				retval = 1;

/* +BURRO: Explosion de la burra (manejada desde el contact listener) +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
			
			}else if (static_cast<Missile*>(static_cast<Missile2d*>(iterator->second)->body->GetUserData())->hasExploded() &&
					  static_cast<GameElement*>(static_cast<Missile2d*>(iterator->second)->body->GetUserData())->getWeaponId() == BURRO){

				// Hago agujero en Box2d
				this->doExplosion( b2Vec2( 
					static_cast<Missile*>(static_cast<Missile2d*>(iterator->second)->body->GetUserData())->getPosition().first,
					static_cast<Missile*>(static_cast<Missile2d*>(iterator->second)->body->GetUserData())->getPosition().second),
					static_cast<Missile2d*>(iterator->second)->getExplosion().radio,
					static_cast<Missile*>(static_cast<Missile2d*>(iterator->second)->body->GetUserData())->getWeaponId()
					);

				this->addExplosion( static_cast<Missile*>(static_cast<Missile2d*>(iterator->second)->body->GetUserData())->getPosition().first,
					static_cast<Missile*>(static_cast<Missile2d*>(iterator->second)->body->GetUserData())->getPosition().second,
					static_cast<Missile2d*>(iterator->second)->getExplosion().radio 
					);

				
					static_cast<Missile*>(static_cast<Missile2d*>(iterator->second)->body->GetUserData())->setAction(EXPLOSION);
					static_cast<Missile*>(static_cast<Missile2d*>(iterator->second)->body->GetUserData())->changed = true;

					// Lo freno
					(iterator->second)->body->SetLinearVelocity( b2Vec2(0,0) );
						
					//Lo hago que suba un poquito
					(iterator->second)->body->ApplyLinearImpulse( b2Vec2(0, (iterator->second)->body->GetMass()*8), (iterator->second)->body->GetWorldCenter() );
					static_cast<Missile*>(static_cast<Missile2d*>(iterator->second)->body->GetUserData())->myLastAction == EXPLOSION;
					static_cast<Missile*>(static_cast<Missile2d*>(iterator->second)->body->GetUserData())->setExploded(false);
				



/* +MISILES: Animacion de misiles y explosion de los misiles con tiempo +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
			}else{				
				Missile2d* aBody = static_cast<Missile2d*>(iterator->second);
				aBody->animate( this->myTimer.elapsed() );
					
				/* Restrinjo solo a los que tienen delayed Explosion*/
				if ( static_cast<Missile*>(static_cast<Missile2d*>(iterator->second)->body->GetUserData())->hasExploded() && 
					 (static_cast<GameElement*>(static_cast<Missile2d*>(iterator->second)->body->GetUserData())->getWeaponId() != BAZOOKA &&
					  static_cast<GameElement*>(static_cast<Missile2d*>(iterator->second)->body->GetUserData())->getWeaponId() != AIRATTACK &&
					  static_cast<GameElement*>(static_cast<Missile2d*>(iterator->second)->body->GetUserData())->getWeaponId() != BURRO) ){
					
					// Hago agujero en Box2d
					this->doExplosion( b2Vec2( 
						static_cast<Missile*>(static_cast<Missile2d*>(iterator->second)->body->GetUserData())->getPosition().first,
						static_cast<Missile*>(static_cast<Missile2d*>(iterator->second)->body->GetUserData())->getPosition().second),
						static_cast<Missile2d*>(iterator->second)->getExplosion().radio,
						static_cast<Missile*>(static_cast<Missile2d*>(iterator->second)->body->GetUserData())->getWeaponId()
						);

					this->addExplosion( static_cast<Missile*>(static_cast<Missile2d*>(iterator->second)->body->GetUserData())->getPosition().first,
						static_cast<Missile*>(static_cast<Missile2d*>(iterator->second)->body->GetUserData())->getPosition().second,
						static_cast<Missile2d*>(iterator->second)->getExplosion().radio 
						);

					
					static_cast<Missile*>(static_cast<Missile2d*>(iterator->second)->body->GetUserData())->drowned = true;
					retval = 1;

					// Marco como inactivo para borrar en el proximo ciclo
					static_cast<Missile2d*>(iterator->second)->body->SetActive(false);

/* +BANANA: Si es BANANA creo bananitas ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++]]] */
					if ( static_cast<Missile*>(static_cast<Missile2d*>(iterator->second)->body->GetUserData())->getWeaponId() == BANANA){
						this->createWeapon(BANANITA,
							static_cast<Missile*>(static_cast<Missile2d*>(iterator->second)->body->GetUserData())->getPosition().first,
							static_cast<Missile*>(static_cast<Missile2d*>(iterator->second)->body->GetUserData())->getPosition().second,
							60,60,1);
						this->createWeapon(BANANITA,
							static_cast<Missile*>(static_cast<Missile2d*>(iterator->second)->body->GetUserData())->getPosition().first,
							static_cast<Missile*>(static_cast<Missile2d*>(iterator->second)->body->GetUserData())->getPosition().second,
							90,90,1);
						this->createWeapon(BANANITA,
							static_cast<Missile*>(static_cast<Missile2d*>(iterator->second)->body->GetUserData())->getPosition().first,
							static_cast<Missile*>(static_cast<Missile2d*>(iterator->second)->body->GetUserData())->getPosition().second,
							120,120,1);

						retval = 0;
					}
					
					//this->myTimer.reset();
				}

/*FUERA DE PANTALLA: Elimino misiles que salieron de la pantalla*/
				if (static_cast<Missile*>(static_cast<Missile2d*>(iterator->second)->body->GetUserData())->getPosition().first > 400 ||
					static_cast<Missile*>(static_cast<Missile2d*>(iterator->second)->body->GetUserData())->getPosition().first < -5 || 
					static_cast<Missile*>(static_cast<Missile2d*>(iterator->second)->body->GetUserData())->getPosition().second < -15){
					//printf("\n se fue de la pantalla");

					//Cambio weaponId para eliminar en el proximo ciclo
					static_cast<GameElement*>(static_cast<Missile2d*>(iterator->second)->body->GetUserData())->setWeapon(NO_WEAPON);
					static_cast<GameElement*>(static_cast<Missile2d*>(iterator->second)->body->GetUserData())->setExploded(true);
					static_cast<Missile*>(static_cast<Missile2d*>(iterator->second)->body->GetUserData())->drowned = true;
					static_cast<Missile*>(static_cast<Missile2d*>(iterator->second)->body->GetUserData())->setAction(MISSIL_DELETED);
					static_cast<Missile*>(static_cast<Missile2d*>(iterator->second)->body->GetUserData())->changed = true;
					retval = 1;

				}
			}
		}
	}



	/* Logica del agua */
	std::set<fixturePair>::iterator it = this->myContactListener.m_fixturePairs.begin();
    std::set<fixturePair>::iterator end = this->myContactListener.m_fixturePairs.end();

	while (it != end) {
		//fixtureA = Agua
		//fixtureB = Cualquier otro cuerpo
		b2Fixture* fixtureA = it->first;
		b2Fixture* fixtureB = it->second;

		float density = fixtureA->GetDensity();
		
		std::vector<b2Vec2> intersectionPoints;
		if ( intersectionWithWater(fixtureB) ) {

			if ( !static_cast<GameElement*>(it->second->GetBody()->GetUserData())->drowned){
				/* Si es un misil lo elimino */
				if ( it->second->GetUserData() == (void*)UD_MISSIL ){

					if ( static_cast<Missile*>(it->second->GetBody()->GetUserData())->getWeaponId() != BURRO){
						printf("\nMisil al agua\n");
						//Cambio weaponId para eliminar en el proximo ciclo
						static_cast<Missile*>(it->second->GetBody()->GetUserData())->setWeapon(NO_WEAPON);
						static_cast<Missile*>(it->second->GetBody()->GetUserData())->setExploded(true);
						static_cast<Missile*>(it->second->GetBody()->GetUserData())->drowned = true;
						static_cast<Missile*>(it->second->GetBody()->GetUserData())->setAction(MISSIL_DELETED);
						static_cast<Missile*>(it->second->GetBody()->GetUserData())->changed = true;
						retval = 1;
						//bodiesToDelete.push_back( static_cast<Missile*>(it->second->GetBody()->GetUserData())->getId() );
					}
					
				}else{
					if ( !static_cast<GameElement*>(it->second->GetBody()->GetUserData())->drowned){
						/* Velocidad que toma al caer */
						printf("\nWorm al agua");
						b2Vec2 vel=b2Vec2(0,WATER_VELOCITY);
						it->second->GetBody()->SetLinearVelocity(vel);
						static_cast<Worm*>(it->second->GetBody()->GetUserData())->setLife(0);
						static_cast<Worm*>(it->second->GetBody()->GetUserData())->setAlive(true);
						static_cast<Worm*>(it->second->GetBody()->GetUserData())->drowned = true;
						static_cast<Worm*>(it->second->GetBody()->GetUserData())->setAction(WORM_DROWNED);
						static_cast<Worm*>(it->second->GetBody()->GetUserData())->changed = true;

					}
				}
			}

		}
		++it;
	}

	//Elimino todos los cuerpos que fueron marcados para eliminacion
	for ( int i=0; i < bodiesToDelete.size(); i++ ){
		this->deleteBody( bodiesToDelete[i] );
	}

	return retval;
}


// The engine will loop separately when this runs on different sockets, not now (TP1)
bool GameEngine::loop() {
	//TODO @future
	return true;
}

int GameEngine::howManyPlayers(void){
	//TODO @future - return this->gameLevel->cantidadJugadores();
	return 1;
}

GameLevel* GameEngine::getLevel(){
	return this->gameLevel;
}


void GameEngine::reInitWorld(){

	this->destroyWorld();
	this->gameLevel = new GameLevel();


}

void GameEngine::updateBodyPositions(){

	std::map<int, GameElement*> mmap = this->gameLevel->getEntities();
	std::map<int, GameElement*>::iterator elems = mmap.begin();

	for ( ; elems != mmap.end(); elems++) {
		std::map<int,Body*>::iterator it;
		it=this->gameBodies->find(elems->second->getId());
		it->second->setPosition(elems->second->getPosition().first,
								elems->second->getPosition().second,
								elems->second->getRotation()
								);
	}

}


void GameEngine::animateJoints() {
	//recorro todos los contactos que existen en el m_mundo

}

bool GameEngine::findIntersectionOfFixtures(b2Fixture* fixtureA, b2Fixture* fixtureB){

	

	return false;
}

bool GameEngine::intersectionWithWater(b2Fixture* fixture){

	//TODO @Music: hacer ruido de que cayo en el agua


	if(fixture->GetShape()->GetType() == b2Shape::e_polygon){
		//Log::t("Polygon");
		b2PolygonShape* poly = (b2PolygonShape*)fixture->GetShape();
		std::vector<b2Vec2> vertex;
	
		for (int i = 0; i < poly->GetVertexCount(); i++)
			vertex.push_back( fixture->GetBody()->GetWorldPoint( poly->GetVertex(i) ) );
		for (int j = 0; j < vertex.size() ; j++){
			if ( vertex[j].y <= this->gameLevel->getWaterLevel() )
				return true;
		}
	}
	if(fixture->GetShape()->GetType() == b2Shape::e_circle){
		//Log::t("Circle");
		b2CircleShape* circ = (b2CircleShape*)fixture->GetShape();
		
		if ( (fixture->GetBody()->GetWorldPoint(b2Vec2(0.0,0.0)).y + circ->m_radius) <= this->gameLevel->getWaterLevel() )
			return true;
	}


	return false;
}


/* Initial contacts review, may impact on model Element but we will inform ;) */
void GameEngine::animateContacts(){

}


void GameEngine::deleteBody(int id){

	std::map<int,Body*>::iterator iterator;
	iterator = this->gameBodies->find(id);
	this->myWorld->DestroyBody(iterator->second->body);
	this->gameBodies->erase(iterator);
	this->gameLevel->removeEntity(id);

}


/*
id = worm_id
weaponid = id del arma
<x , y> = angulo del disparo
action = accion a ejecutar
*/
void GameEngine::applyAction2Element(int id, int weaponid, float x, float y, Movement action, int intensidad){

	std::map<int,GameElement*> copy = this->gameLevel->getEntities();
	GameElement* myWorm = copy[id];

	switch (action){
		case MOVE_RIGHT:
			static_cast<Worm*>(myWorm)->moveRight();
			break;
		case MOVE_LEFT:
			static_cast<Worm*>(myWorm)->moveLeft();
			break;
		case JUMP:
			static_cast<Worm*>(myWorm)->jump();
			break;
		case JUMP_RIGHT:
			static_cast<Worm*>(myWorm)->jumpRight();
			break;
		case JUMP_LEFT:
			static_cast<Worm*>(myWorm)->jumpLeft();
			break;
		case MOVE_STOP:
			static_cast<Worm*>(myWorm)->stop();
			break;
		case WITH_WEAPON_LEFT:
			//printf("\nweapon LEFT %d",weaponid);
			static_cast<Worm*>(myWorm)->weaponedLeft(weaponid);
			break;
		case WITH_WEAPON_RIGHT:
			//printf("\nweapon RIGHT %d",weaponid);
			static_cast<Worm*>(myWorm)->weaponedRight(weaponid);
			break;
		case WITH_WEAPON:
			//printf("\nweapon NORMAL %d",weaponid);
			static_cast<Worm*>(myWorm)->weaponedRight(weaponid);
			break;
		case DO_SHOOT:
			////printf("\n animate weapon: x %f, y %f, intensidad: %d",x,y,intensidad);
			this->didWeShoot = true;
			static_cast<Worm*>(myWorm)->shoot();
			animateWeapon(weaponid, id, x, y, intensidad);
						
			break;
	}


	return;

}


void GameEngine::stopPlayer( std::string pl){

	this->gameLevel->stopWormsFromPlayer(pl);

}



// Solo se ejecuta si recibo la accion DO_SHOOT
void GameEngine::animateWeapon(int weaponid, int wormid, float angle_x, float angle_y, int intensidad){



	//Crea el arma en el modelo
	float xworm = static_cast<Worm2d*>(this->gameLevel->getEntityByID(wormid)->myBody)->body->GetWorldCenter().x;
	float yworm = static_cast<Worm2d*>(this->gameLevel->getEntityByID(wormid)->myBody)->body->GetWorldCenter().y;
	int cantMisiles = 1;
	
	if ( weaponid == AIRATTACK ){
		cantMisiles = 4;
		/*xworm = 50;
		yworm = 80;*/
		xworm = angle_x;
		yworm = angle_y;
	}



	for (int i=0; i < cantMisiles; i++ ){
		GameElement* myWeapon;

		int elementId = this->getWeaponUniqueId(); 
		//printf("\ncreating weapon: %d",weaponid);
		Missile* aMissile = MissileFactory::getInstance()->getMissile(weaponid,elementId);
		aMissile->setPosition(pair<float,float>(xworm,yworm));
		aMissile->setStartTime(this->myTimer.elapsed());

		Missile2d* aMissile2d = Missile2dFactory::getInstance()->getMissile(weaponid,WEAPON,xworm + i*8, yworm, angle_x, angle_y, intensidad, this->myWorld, aMissile);
		aMissile->setBody(aMissile2d);

		this->gameLevel->addEntity(aMissile);
		this->gameBodies->insert(std::make_pair<int,Body*>(elementId, aMissile2d));
	}
	
}


// Solo se ejecuta si recibo la accion DO_SHOOT
void GameEngine::createWeapon(int weaponid, float posx, float posy, float angle_x, float angle_y, int intensidad){

	GameElement* myWeapon;

	int elementId = this->getWeaponUniqueId(); 
	//printf("\ncreating weapon: %d",weaponid);
	Missile* aMissile = MissileFactory::getInstance()->getMissile(weaponid,elementId);
	aMissile->setPosition(pair<float,float>(posx,posy));
	aMissile->setStartTime(this->myTimer.elapsed());

	Missile2d* aMissile2d = Missile2dFactory::getInstance()->getMissile(weaponid,WEAPON,posx, posy, angle_x, angle_y, intensidad, this->myWorld, aMissile);
	aMissile->setBody(aMissile2d);

	this->gameLevel->addEntity(aMissile);
	this->gameBodies->insert(std::make_pair<int,Body*>(elementId, aMissile2d));

	
}



void GameEngine::doExplosion(b2Vec2 removalPosition, int removalRadius, int weapon){

	poly_t* explosion = new poly_t();
	*explosion = this->makeConvexRing(removalPosition, removalRadius*2, 16);
			

	list <poly_t*>* resultado = new list<poly_t*>();
	
	for(list<poly_t*>::iterator it = this->gameLevel->myPol->begin(); it != this->gameLevel->myPol->end(); it++){
			list <poly_t>* output = new list<poly_t>();
			//resto los poligonos, guardo salida en output
			boost::geometry::difference(*(*it), *explosion, *output);
			for(list<poly_t>::iterator diffIt = output->begin(); diffIt != output->end(); diffIt++){
					resultado->push_back(&(*diffIt));
			}
	}
	this->gameLevel->myPol->clear();
	this->gameLevel->myPol = resultado;

	for(std::vector<b2Body*>::iterator it = this->gameLevel->myTerrain.begin(); it != this->gameLevel->myTerrain.end(); it++){
			this->myWorld->DestroyBody(*it);
	}

	this->gameLevel->myTerrain.clear();

	//Genero nuevos bodys por cada componente conexa que quedo (chain)
	for(std::list<poly_t*>::iterator it = resultado->begin(); it != resultado->end(); it++){
			b2BodyDef* bd = new b2BodyDef();
			b2Vec2* vs = new b2Vec2[(*it)->outer().size()];
			int i = 0;

			for(vector<point>::iterator it2 = (*it)->outer().begin(); it2 != (*it)->outer().end(); it2++){
					vs[i].Set((*it2).get<0>(),(*it2).get<1>());
					i++;
			}

			b2ChainShape shape;
			shape.CreateLoop(vs,i);
			b2Body* tierra = this->myWorld->CreateBody(bd);
			
			//Defino propiedades del terreno
			b2FixtureDef myFixtureDef;
			myFixtureDef.friction=0.999;
			myFixtureDef.userData = ( (void*) UD_TERRAIN );
			myFixtureDef.shape = &shape;

			tierra->CreateFixture(&myFixtureDef);
			this->gameLevel->myTerrain.push_back(tierra);
	}

	// Podria cambiar la onda expansiva de cada arma pero tendria que pasarle al do explosion el arma que genera la explosion.
	
	switch ( weapon ){
		case GRENADE:
			this->doOndaExpansiva(removalPosition,BLAST_RADIUS,BLAST_FORCE, DAMAGE_GRENADE);
			break;
		case BAZOOKA:
			this->doOndaExpansiva(removalPosition,BLAST_RADIUS,BLAST_FORCE, DAMAGE_BAZOOKA);
			break;
		case DYNAMITE:
			this->doOndaExpansiva(removalPosition,BLAST_RADIUS,BLAST_FORCE, DAMAGE_DYNAMITE);
			break;
		case HOLY:
			this->doOndaExpansiva(removalPosition,BLAST_RADIUS,BLAST_FORCE, DAMAGE_HOLY);
			break;
		case HMISSILE:
			this->doOndaExpansiva(removalPosition,BLAST_RADIUS,BLAST_FORCE, DAMAGE_HMISSILE);
			break;
		case SUICIDE:
			this->doOndaExpansiva(removalPosition,BLAST_RADIUS,BLAST_FORCE, DAMAGE_SUICIDE);
			break;
		case BURRO:
			this->doOndaExpansiva(removalPosition,BLAST_RADIUS,BLAST_FORCE, DAMAGE_BURRO);
			break;
		case AIRATTACK:
			this->doOndaExpansiva(removalPosition,BLAST_RADIUS,BLAST_FORCE, DAMAGE_BURRO);
			break;
		default:
			this->doOndaExpansiva(removalPosition,BLAST_RADIUS,BLAST_FORCE, 10);
			break;
	}

}


poly_t GameEngine::makeConvexRing(b2Vec2 position, float radius, int vertices)
{
	poly_t convexRing;
	const float theta = boost::math::constants::two_pi<float>() / static_cast<float>(vertices);

	float c = std::cos(theta);
	float s = std::sin(theta);

	float t = 0.0f;
	float y = 0.0f;
	float x = radius;
	for (float i = 0; i < vertices; i++)
	{
		float v_x = x + position.x;
		float v_y = y + position.y;
		bg::append(convexRing, point(v_x, v_y));

		t = x;
		x = c * x - s * y;
		y = s * t + c * y;
	}

	return convexRing;
}


void GameEngine::addExplosion(float x, float y, int radio){
	Explosion* e = new Explosion(x,y,radio);

	////printf("\nadd explosion!");
	mapExplosions.push_back(e);
}

