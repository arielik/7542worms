#include "MissileSheep2d.h"

MissileSheep2d::MissileSheep2d()
{

}

MissileSheep2d::MissileSheep2d(ElementType type, float posX, float posY, float angle_x, float angle_y, float fuerzaDisparo, b2World *myWorld, GameElement *modelElement){
	
	this->myWorld = myWorld;
	this->left = false;
	this->right = false;
	this->detention = false;

	/* Importantisimo! lo seteo como weapon!! */
	this->type = type;

	b2BodyDef myBodyDef;
	myBodyDef.type = b2_dynamicBody;

	b2FixtureDef myFixtureDef;
   	myFixtureDef.filter.categoryBits = MISSIL_CAT;
	myFixtureDef.filter.maskBits = WORM_CAT | WATER_CAT | TERRAIN_CAT;
	b2CircleShape circleShape;
	circleShape.m_radius = 2;
	circleShape.m_p.Set(0,0);

	myFixtureDef.shape = &circleShape;
    myFixtureDef.density = 1;
	myFixtureDef.friction = 0.4;
	myFixtureDef.restitution = 0;
	myFixtureDef.userData = (void*)UD_MISSIL;
	
	if ( angle_x > 0 ){
		//printf("\nDejo del lado derecho");
		this->right = true;
		myBodyDef.position.Set(posX + 3, posY);
		this->setPosition(posX + 3, posY,0);

	}else {
		this->left = true;
		//printf("\nDejo del lado Izquierdo");
		myBodyDef.position.Set(posX - 3, posY);
		this->setPosition(posX - 3, posY,0);
	}
	

	//myBodyDef.position.Set(posX, posY);
    b2Body* body = this->myWorld->CreateBody(&myBodyDef);

	body->CreateFixture(&myFixtureDef);

	//printf("\nCreating weapon at: %f, %f",posX,posY);

	body->SetFixedRotation(true);


	this->body = body;
	this->body->SetUserData(modelElement);
		
	//velocidad inicial
	if ( angle_x > 0 ){
		//this->body->SetLinearVelocity( b2Vec2(SHEEP_SPEED,0) );
		this->body->ApplyForce( b2Vec2(SHEEP_FORCE , 0),this->body->GetWorldCenter() );
	}else{
		//this->body->SetLinearVelocity( b2Vec2(-SHEEP_SPEED,0) );
		this->body->ApplyForce( b2Vec2(-SHEEP_FORCE ,0 ),this->body->GetWorldCenter() );
	}
	
	modelElement->myLastAction = CREATE_MISSIL;
	modelElement->setAlive(true);

	/* Defino radio de explosion */
	this->explosion.radio = EXPLODE_RSMALL;
	
	//printf("\n Ovejita lanzada");
}

MissileSheep2d::~MissileSheep2d(){}

void MissileSheep2d::animate( float time ){

	//Use userdata to reflect changes in physics to model
	GameElement* myWeapon = static_cast<GameElement*>(this->body->GetUserData());

	if ( static_cast<Missile*>(myWeapon)->hasDelayedExplosion() ){
		static_cast<Missile*>(myWeapon)->updateExplode( time );
	}

	if ( static_cast<Missile*>(myWeapon)->hasExploded() ){
		myWeapon->setAction(EXPLOSION);
	} else{

		if ( myWeapon->myLastAction == CREATE_MISSIL ){
			myWeapon->setAction(CREATE_MISSIL);
			if (this->right){
				myWeapon->myLastAction = MISSIL_FLYING_RIGHT;
			}else
				myWeapon->myLastAction = MISSIL_FLYING_LEFT;
		}else{
			if (this->right){
				myWeapon->setAction(MISSIL_FLYING_RIGHT);
			}else
				myWeapon->setAction(MISSIL_FLYING_LEFT);
		}

	}
	float nx = static_cast<GameElement*>(this->body->GetUserData())->getNormalX();
	float ny = static_cast<GameElement*>(this->body->GetUserData())->getNormalY();


	//vario la velocidad basado en la normal
	if ( myWeapon->isGrounded()  ){
		////printf("\navanzo");
		if ( this->right ) {
			//this->body->SetLinearVelocity( b2Vec2 (ny*SHEEP_SPEED,-nx*SHEEP_SPEED) );
			this->body->ApplyForce( b2Vec2(ny*SHEEP_FORCE ,-nx*SHEEP_FORCE ),this->body->GetWorldCenter() );
		}

		if (this->left){
			//this->body->SetLinearVelocity( b2Vec2 (-ny*SHEEP_SPEED,nx*SHEEP_SPEED) );
			this->body->ApplyForce( b2Vec2(-ny*SHEEP_FORCE ,nx*SHEEP_FORCE ),this->body->GetWorldCenter() );
		}

		this->detention = false;

	}else if ( !this->detention ) {
		////printf("\ndetengo");
		this->body->SetLinearVelocity( b2Vec2(0,0) );
		this->body->SetAngularVelocity( 0 );
		this->detention = true;
	}


	//Actualizo la posicion
	b2Vec2 f = this->body->GetPosition();
	myWeapon->setPosition(std::make_pair( f.x,f.y) );
	myWeapon->changed = true;

	//Actualizo tiempo restante
	myWeapon->setLife( static_cast<Missile*>(myWeapon)->remainingTime(time) );


}


void MissileSheep2d::explode( ){





}