#include "Worm2d.h"


Worm2d::Worm2d(ElementType type, float posX, float posY, float h, 
	float w, float masa, float angle, b2World *myWorld, GameElement *modelElement, bool fixed)
{

	this->myWorld = myWorld;
	this->center = b2Vec2( posX+(w/2), posY+(h/2) );
	this->angle = angle;
	this->masa = masa;
	this->type = type;
	this->width = w;
	this->height = h;


	this->myWorld = myWorld;
	this->center = b2Vec2( posX, posY );
	this->angle = angle;
	this->masa = masa;
	this->type = type;


	//body definition
    b2BodyDef myBodyDef;
    if (!fixed){
		myBodyDef.type = b2_dynamicBody;
	}else{
		myBodyDef.type = b2_staticBody;
	}
    
    ////hexagonal shape definition
    //b2PolygonShape polygonShape;
    //b2Vec2 vertices[6];
    //for (int i = 0; i < 6; i++) {
    //  float angle = -i/6.0 * 360 * DEGTORAD;
    //  vertices[i].Set((w/2)*sinf(angle), (h/2)*cosf(angle));
    //} 
    //polygonShape.Set(vertices, 6);
    //myFixtureDef.shape = &polygonShape;


    //fixture definition
    b2FixtureDef myFixtureDef;
   
	myFixtureDef.filter.categoryBits = WORM_CAT;
    myFixtureDef.filter.maskBits = WORM_CAT | MISSIL_CAT | TERRAIN_CAT | WATER_CAT;
	b2CircleShape circleShape;
	circleShape.m_radius = 1;
	circleShape.m_p.Set(0,0);

	myFixtureDef.shape = &circleShape;
    myFixtureDef.density = 1;
	myFixtureDef.friction = 0.999;
	myFixtureDef.restitution = 0;
	myFixtureDef.userData = (void*)UD_WORMS;

    //create dynamic body
    myBodyDef.position.Set(posX, posY);
    b2Body* body = this->myWorld->CreateBody(&myBodyDef);
    

	body->CreateFixture(&myFixtureDef);
	circleShape.m_p.Set(0,1);
	body->CreateFixture(&myFixtureDef);

	body->SetTransform( body->GetPosition(), angle*DEGTORAD );
	body->SetFixedRotation(true);

	this->body = body;
	this->damaged = false;
	this->body->SetUserData(modelElement);

	b2Vec2 v = this->body->GetWorldPoint(b2Vec2( 0,0));
	Log::d("Posicion Inicial: %.3f, %.3f", v.x, v.y);




	aWormActions = new WormActions(this);
	//this->ox = static_cast<GameElement*>(this->body->GetUserData())->getPosition().first;
	//this->oy = static_cast<GameElement*>(this->body->GetUserData())->getPosition().second;
	this->ox = this->body->GetPosition().x;
	this->oy = this->body->GetPosition().y;
	
}
void Worm2d::jump()
{
	aWormActions->jump();
}

void Worm2d::jumpRight()
{
	aWormActions->jumpRight();
}

void Worm2d::jumpLeft()
{
	aWormActions->jumpLeft();
}

void Worm2d::moveLeft()
{
	aWormActions->moveLeft();
}

void Worm2d::moveRight()
{
	aWormActions->moveRight();
}

void Worm2d::makeTumb(){


	for (b2Fixture* f = this->body->GetFixtureList(); f; f = f->GetNext()){

		b2Filter filter = f->GetFilterData();
		filter.categoryBits = TUMB_CAT;
		filter.maskBits = TERRAIN_CAT;
		f->SetFilterData(filter);
	}


}

void Worm2d::animate(){

	//Use userdata to reflect changes in physics to model
	GameElement* myWorm = static_cast<GameElement*>(this->body->GetUserData());

	if ( !myWorm->isAlive() ){
		myWorm->changed = true;
		myWorm->action = DEAD;
		//printf("\nSending dead");
		return;
	}

	this->aWormActions->updateJumpTimeout();

	bool noEstabaSatando =  ( myWorm->myLastAction != JUMP && myWorm->myLastAction != JUMP_RIGHT && myWorm->myLastAction != JUMP_LEFT );

	//si el Worm esta saltando y no estaba saltando
	if(static_cast<Worm*>(myWorm)->isJumping() && noEstabaSatando )
	{
		this->jump();
		myWorm->myLastAction = JUMP;

	} 

	if(static_cast<Worm*>(myWorm)->isJumpingRight() && noEstabaSatando )
	{
		this->jumpRight();
		myWorm->myLastAction = JUMP_RIGHT;

	} 

	if(static_cast<Worm*>(myWorm)->isJumpingLeft() && noEstabaSatando )
	{
		this->jumpLeft();
		myWorm->myLastAction = JUMP_LEFT;

	} 

	//si el Worm se esta moviendo a la izquierda, moverlo a izquierda
	if(static_cast<Worm*>(myWorm)->isMovingLeft() && noEstabaSatando )
	{
		this->moveLeft();
		myWorm->myLastAction = MOVE_LEFT;
	}

	//si el Worm se esta moviendo a la derecha, moverlo a derecha
	if(static_cast<Worm*>(myWorm)->isMovingRight() && noEstabaSatando )
	{
		this->moveRight();
		myWorm->myLastAction = MOVE_RIGHT;
	}


	if(static_cast<Worm*>(myWorm)->action == MOVE_STOP && noEstabaSatando ){
		////printf("\nLo detengo 1");
		this->body->SetLinearVelocity(b2Vec2(0,0));
		static_cast<Worm*>(myWorm)->action = MOVELESS;

	}

	if ( !noEstabaSatando ){
		if ( myWorm->isGrounded() ){
			myWorm->myLastAction = MOVE_STOP;
		}
	}


	b2Vec2 f = this->body->GetPosition();


	if ( this->ox != f.x || this->oy != f.y)   // cambio posicion en mundo
	{

		//Matar cuando pasa el agua TODO

		//Mata el worm (desactiva el cuerpo de Box2D)
		if (f.x < -15 || f.y < -15){
			this->body->SetActive(false);
			myWorm->changed = false;
			this->ox = f.x;
			this->oy = f.y;
			static_cast<Worm*>(myWorm)->setAlive(false);
			if ( myWorm->getAction() != NOT_CONNECTED || 
				 myWorm->getAction() != NOT_CONNECTED_LEFT ||
				 myWorm->getAction() != NOT_CONNECTED_RIGHT  )
				(myWorm)->myLastAction = MOVELESS;
			
		}else{

			//Actualiza la posicion en el modelo
			myWorm->setPosition(std::make_pair( f.x,f.y) );
			myWorm->changed = true;
			this->ox = f.x;
			this->oy = f.y;
			

		}
	}
	else{

		bool cambieDeEstado = myWorm->getAction() !=  myWorm->getMyLastAction();
		bool estoyConectado = (myWorm->getAction() != NOT_CONNECTED) && (myWorm->getAction() != NOT_CONNECTED_LEFT) && (myWorm->getAction() != NOT_CONNECTED_RIGHT);
		if ( cambieDeEstado &&  estoyConectado )
		{

			Log::t("\nModificando worm %d of %s", myWorm->getId(), myWorm->playerID.c_str());
			if ( myWorm->getAction()  ==  MOVE_RIGHT ) {
				myWorm->setAction(MOVELESS_RIGHT);
			}
			
			if ( myWorm->getAction()  ==  MOVE_LEFT){
				myWorm->setAction(MOVELESS_LEFT);
			}
			
			if ( myWorm->getAction()  ==  WITH_WEAPON_LEFT){
				myWorm->setAction(WITH_WEAPON_LEFT);
			}

			if ( myWorm->getAction()  ==  WITH_WEAPON_RIGHT){
				myWorm->setAction(WITH_WEAPON_RIGHT);
			}

			if ( myWorm->getAction()  ==  MOVELESS){
				myWorm->setAction(MOVELESS);
				myWorm->myLastAction = MOVELESS;
			}

			if ( myWorm->getAction()  ==  MOVELESS_RIGHT){
				myWorm->setAction(MOVELESS_RIGHT);
				myWorm->myLastAction = MOVELESS_RIGHT;
			}

			if ( myWorm->getAction()  ==  MOVELESS_LEFT){
				myWorm->setAction(MOVELESS_LEFT);
				myWorm->myLastAction = MOVELESS_LEFT;
			}



			myWorm->changed = true;
		}else{
			myWorm->changed = false;
		}
	}

}


Worm2d::~Worm2d()
{
	delete aWormActions;
}



void Worm2d::animate(bool update){

	////Use userdata to reflect changes in physics to model
	//GameElement* myWorm = static_cast<GameElement*>(this->body->GetUserData());

	////si el Worm esta saltando, saltar
	//if(static_cast<Worm*>(myWorm)->isJumping())
	//{
	//	this->jump();
	//} 

	////si el Worm se esta moviendo a la izquierda, moverlo a izquierda
	//if(static_cast<Worm*>(myWorm)->isMovingLeft())
	//{
	//	this->moveLeft();
	//}

	////si el Worm se esta moviendo a la derecha, moverlo a derecha
	//if(static_cast<Worm*>(myWorm)->isMovingRight())
	//{
	//	this->moveRight();

	//}

	//b2Vec2 f = this->body->GetPosition();

	//if ( this->ox != f.x || this->oy != f.y){
	//	//printf("distinto X %f to %f, Y %f to %f",this->ox,this->oy,f.x,f.y);
	//	//this->ox = f.x;
	//	//this->oy = f.y;

	//	//TODO lo desactivo al pasar el agua


	//	//Mata el worm (desactiva el cuerpo de Box2D)
	//	if (f.x < -15 || f.y < -15){
	//		this->body->SetActive(false);
	//		if ( update){
	//			myWorm->changed = false;
	//			myWorm->setPosition(std::make_pair( f.x,f.y) );
	//		}
	//		static_cast<Worm*>(myWorm)->setAlive(false);
	//		//TODO: Chequear si aca lo puedo eliminar de box2d

	//	}else{

	//		//Actualiza la posicion en el modelo
	//		
	//		if ( update){
	//			myWorm->setPosition(std::make_pair( f.x,f.y) );
	//			myWorm->changed = true;
	//			this->ox = f.x;
	//			this->oy = f.y;
	//		}
	//	}
	//}
	//else{
	//	if ( update)
	//		myWorm->changed = false;
	//}

}