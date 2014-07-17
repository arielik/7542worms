#include "MissileDynamite2d.h"

MissileDynamite2d::MissileDynamite2d()
{

}



void MissileDynamite2d::explode( ){





}





MissileDynamite2d::MissileDynamite2d(ElementType type, float posX, float posY, float angle_x, float angle_y, float fuerzaDisparo, b2World *myWorld, GameElement *modelElement){
	
	//printf("\nCreando dinamita");
	this->myWorld = myWorld;
	

	/* Importantisimo! lo seteo como weapon!! */
	this->type = type;

	b2BodyDef myBodyDef;
	myBodyDef.type = b2_dynamicBody;

	b2FixtureDef myFixtureDef;
   	myFixtureDef.filter.categoryBits = MISSIL_CAT;
	myFixtureDef.filter.maskBits = WORM_CAT | WATER_CAT | TERRAIN_CAT;
	b2CircleShape circleShape;
	circleShape.m_radius = BULLET_RADIUS;
	circleShape.m_p.Set(0,0);

	myFixtureDef.shape = &circleShape;
    myFixtureDef.density = 1;
	myFixtureDef.friction = 1;
	myFixtureDef.restitution = 0;
	myFixtureDef.userData = (void*)UD_MISSIL;

	

	if ( angle_x > 0 ){
		//printf("\nDejo del lado derecho");
		myBodyDef.position.Set(posX + 1.5f, posY);
		this->setPosition(posX + 1.5f, posY,0);

	}else {
		//printf("\nDejo del lado Izquierdo");
		myBodyDef.position.Set(posX - 1.5f, posY);
		this->setPosition(posX - 1.5f, posY,0);
	}
	
	b2Body* body = this->myWorld->CreateBody(&myBodyDef);
	body->CreateFixture(&myFixtureDef);
	body->SetFixedRotation(true);

	this->body = body;
	this->body->SetUserData(modelElement);


	modelElement->myLastAction = CREATE_MISSIL;
	modelElement->setAlive(true);

	/* Defino radio de explosion */
	this->explosion.radio = EXPLODE_RMEDIUM;
	
	//printf("\n Dinamita Impulsada");
}

MissileDynamite2d::~MissileDynamite2d(){}

void MissileDynamite2d::animate( float time ){

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
			myWeapon->myLastAction = MISSIL_FLYING;
		}else{
			myWeapon->setAction(MISSIL_FLYING);
		}

	}

	//Actualizo la posicion
	b2Vec2 f = this->body->GetPosition();
	myWeapon->setPosition(std::make_pair( f.x,f.y) );
	myWeapon->changed = true;

	//Actualizo tiempo restante
	myWeapon->setLife( static_cast<Missile*>(myWeapon)->remainingTime(time) );


}