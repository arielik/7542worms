#include "MissileBurro2d.h"

MissileBurro2d::MissileBurro2d()
{

}




void MissileBurro2d::explode( ){





}







MissileBurro2d::MissileBurro2d(ElementType type, float posX, float posY, float angle_x, float angle_y, float fuerzaDisparo, b2World *myWorld, GameElement *modelElement){
	
	this->myWorld = myWorld;
	

	/* Importantisimo! lo seteo como weapon!! */
	this->type = type;

	b2BodyDef myBodyDef;
	myBodyDef.type = b2_dynamicBody;

	b2FixtureDef myFixtureDef;
    myFixtureDef.filter.categoryBits = MISSIL_CAT;
	myFixtureDef.filter.maskBits = WORM_CAT | WATER_CAT | TERRAIN_CAT;
	//b2PolygonShape boxShape;
	//boxShape.SetAsBox(5,5);

	//myFixtureDef.shape = &boxShape;
	b2CircleShape circleShape;
	circleShape.m_radius = 2.5;
	circleShape.m_p.Set(0,0);

	myFixtureDef.shape = &circleShape;
    myFixtureDef.density = 1;
	myFixtureDef.friction = 0.01;
	myFixtureDef.restitution = 0.2f;
	myFixtureDef.userData = (void*)UD_MISSIL;





	
	myBodyDef.position.Set(angle_x, BURRO_Y);
	this->setPosition(angle_x, BURRO_Y,0);

    b2Body* body = this->myWorld->CreateBody(&myBodyDef);


	body->CreateFixture(&myFixtureDef);


	body->SetFixedRotation(true);

	this->body = body;
	this->body->SetUserData(modelElement);
		
	modelElement->myLastAction = CREATE_MISSIL;
	modelElement->setAlive(true);

	/* Defino radio de explosion */
	this->explosion.radio = EXPLODE_RMEDIUM;
	
	//printf("\n Lanza la burra");
}

MissileBurro2d::~MissileBurro2d(){}

void MissileBurro2d::animate( float time ){

	//Use userdata to reflect changes in physics to model
	GameElement* myWeapon = static_cast<GameElement*>(this->body->GetUserData());

	if ( myWeapon->myLastAction == CREATE_MISSIL ){
		myWeapon->setAction(CREATE_MISSIL);
		myWeapon->myLastAction = MISSIL_FLYING;
	}else if ( myWeapon->myLastAction == EXPLOSION ){
		////printf("\nreset state");
		myWeapon->setAction(MISSIL_FLYING);
		myWeapon->myLastAction = MISSIL_FLYING;
	}else{
		myWeapon->setAction(MISSIL_FLYING);
	}

	//Actualizo la posicion
	b2Vec2 f = this->body->GetPosition();
	//printf("\n y: %f",f.y);
	myWeapon->setPosition(std::make_pair( f.x,f.y) );
	myWeapon->changed = true;



}