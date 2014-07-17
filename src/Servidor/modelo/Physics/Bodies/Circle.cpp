#include <Box2D/Box2D.h>
#include <math.h>
#include "Circle.h"
#include "../../../../utils/Log.h"

Circle::Circle(	ElementType type, float posX, float posY, float radius, float scale, 
				float masa, b2World *myWorld, GameElement* modelElement, bool fixed)
{

	//ToDo: escalar
	this->myWorld = myWorld;
	this->center = b2Vec2( posX+(radius/2), posY+(radius/2) );
	this->angle = angle;
	this->masa = masa;
	this->type = type;


	//b2BodyDef myBodyDef;

	//if (fixed){
	//	myBodyDef.type = b2_dynamicBody;
	//}else{
	//	myBodyDef.type = b2_staticBody;
	//}
	//myBodyDef.position.Set(posX, posY); //starting position (at center)


	//b2Body* dynamicBody = this->myWorld->CreateBody(&myBodyDef);
	//this->body = dynamicBody;
	//this->body->SetUserData(modelElement);


	//b2CircleShape  circleShape;
	//
	//circleShape.m_p.Set(posX, posY);
	//circleShape.m_radius = radius*scale;

	//b2FixtureDef circleFixtureDef;
	//circleFixtureDef.shape = &circleShape;
	//circleFixtureDef.density = 1;
	//dynamicBody->CreateFixture(&circleFixtureDef);
	//b2Vec2 v = this->body->GetWorldPoint(b2Vec2( 0,0));
	//Log::d("Posicion Inicial: %.3f, %.3f", v.x, v.y);

	b2CircleShape shape;
	shape.m_radius = radius * scale;

	b2FixtureDef fd;
	fd.shape = &shape;
	fd.density = 1.0f;

	b2BodyDef bd;
	if (!fixed){
		bd.type = b2_dynamicBody;
	}else{
		bd.type = b2_staticBody;
	}

	bd.position.Set(posX, posY);
	b2Body* body = this->myWorld->CreateBody(&bd);
	body->CreateFixture(&fd);

	this->body = body;
	this->body->SetUserData(modelElement);

	b2Vec2 v = this->body->GetWorldPoint(b2Vec2( 0,0));
	Log::d("Posicion Inicial: %.3f, %.3f", v.x, v.y);

	//this->GetVertex();

}



//At each step links current box2d with model data
void Circle::animate(){
	//Use userdata to reflect changes in physics to model
	//ToDo @aliguo
	GameElement* ge = static_cast<GameElement*>(this->body->GetUserData());
	//b2Vec2 f = this->body->GetWorldPoint(b2Vec2(0,0));
	b2Vec2 f = this->body->GetPosition();
	Log::d("Nueva posicion (Physics): %.3f, %.3f", f.x, f.y);

	ParserYaml* aParser = ParserYaml::getInstance();
	float x = f.x;
	float y = f.y;
	ge->setPosition(std::make_pair( x,y) );
	Log::d("Nueva posicion (Modelo): %.3f, %.3f", x,y);


}

void Circle::touch(Body* touchingWith, b2World* mundo) {

}

Circle::~Circle() {
	// Destroy from model first
	// ToDo @aliguo
}

void Circle::setPosition(float x, float y,float rot){
	this->body->SetTransform(b2Vec2(x,y),0);
	//this->body->SetLinearVelocity( b2Vec2( 0, 0 ) );
	this->body->SetAngularVelocity( 0 );
	this->body->SetAwake(true);
}