#include "Weapon2d.h"


Weapon2d::Weapon2d(ElementType type, float posX, float posY, float angle_x, float angle_y, float fuerzaDisparo, b2World *myWorld, GameElement *modelElement){
	
	this->myWorld = myWorld;
	this->center = b2Vec2( posX+(BULLET_RADIUS/2), posY+(BULLET_RADIUS/2) );

	b2BodyDef myBodyDef;
	myBodyDef.type = b2_dynamicBody;

	b2FixtureDef myFixtureDef;
   
	b2CircleShape circleShape;
	circleShape.m_radius = BULLET_RADIUS;
	circleShape.m_p.Set(0,0);

	myFixtureDef.shape = &circleShape;
    myFixtureDef.density = 1;
	myFixtureDef.friction = 0.01;
	myFixtureDef.restitution = 0;
	myFixtureDef.userData = (void*)UD_MISSIL;
	myBodyDef.position.Set(posX, posY);
    b2Body* body = this->myWorld->CreateBody(&myBodyDef);

	body->CreateFixture(&myFixtureDef);

	body->SetTransform( body->GetPosition(), 0.0 );
	body->SetFixedRotation(false);

	this->body = body;
	this->body->SetUserData(modelElement);

	//TODO @Bauti Aplicale impulso que consideres necesario
	this->body->ApplyLinearImpulse( b2Vec2 ( angle_x * 10, angle_y * 10 ),this->body->GetWorldCenter() );

}

Weapon2d::~Weapon2d(){}

void Weapon2d::animate( float time ){

	//Use userdata to reflect changes in physics to model
	GameElement* myWeapon = static_cast<GameElement*>(this->body->GetUserData());

	if ( static_cast<WeaponModel*>(myWeapon)->hasDelayedExplosion() ){
		static_cast<WeaponModel*>(myWeapon)->updateExplode( time );
	}
	
	if ( static_cast<WeaponModel*>(myWeapon)->hasExploded() ){
		myWeapon->setAction(EXPLOSION);
	} else{
		myWeapon->setAction(MISSIL_FLYING);
	}

	//Actualizo la posicion
	b2Vec2 f = this->body->GetPosition();

	myWeapon->setPosition(std::make_pair( f.x,f.y) );
	myWeapon->changed = true;


}