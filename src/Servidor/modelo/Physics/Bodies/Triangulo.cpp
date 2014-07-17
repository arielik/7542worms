#include <Box2D/Box2D.h>
#include <math.h>
#include "Triangulo.h"
#include "../../../../utils/Log.h"

Triangle::Triangle(ElementType type, float posX, float posY, float scale, 
		float masa, float angle, b2World *myWorld, GameElement *modelElement, bool fixed)
{

	//ToDo: escalar
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
    
	//hexagonal shape definition
	b2PolygonShape polygonShape;
	b2Vec2 vertices[6];
	for (int i = 0; i < 3; i++) {
		float angle = -i/3.0 * 360 * DEGTORAD;
		vertices[i].Set(scale*sinf(angle), scale*cosf(angle));
	}
 
	polygonShape.Set(vertices, 3);
  
	//fixture definition
	b2FixtureDef myFixtureDef;
	myFixtureDef.shape = &polygonShape;
	myFixtureDef.density = 1;
    
	//create dynamic body
	myBodyDef.position.Set(posX, posY);
	b2Body* body = this->myWorld->CreateBody(&myBodyDef);
	body->CreateFixture(&myFixtureDef);

	body->SetTransform( body->GetPosition(), angle*DEGTORAD );
	
	this->body = body;
	this->body->SetUserData(modelElement);
	

	b2Vec2 v = this->body->GetWorldPoint(b2Vec2( 0,0));
	Log::d("Posicion Inicial: %.3f, %.3f", v.x, v.y);
	//this->GetVertex();
	
	GameElement* ge = static_cast<GameElement*>(this->body->GetUserData());
	ge->setVertexList(this->GetVertex());



}

void Triangle::setPosition(float x, float y,float rot){
	this->body->SetTransform(b2Vec2(x,y),rot*DEGTORAD);
	GameElement* ge = static_cast<GameElement*>(this->body->GetUserData());
	ge->setVertexList(this->GetVertex());
	//this->body->SetLinearVelocity( b2Vec2( 0, 0 ) );
	//this->body->SetAngularVelocity( 0 );
	this->body->SetAwake(true);
}

std::list<std::pair<float,float>> Triangle::GetVertex(){

    //Los vertices los devuelve con las coordenadas cambiadas al sistemas de SDL (0,0) arriba a la izq

	b2Vec2 v = this->body->GetWorldPoint(b2Vec2( 0,0));
	//Log::d("Posicion central 0,0: %.3f, %.3f", v.x, v.y);
	b2PolygonShape* poly = (b2PolygonShape*)this->body->GetFixtureList()->GetShape();
	std::list<std::pair<float,float>> vertexList;
	int count = poly->GetVertexCount();
	ParserYaml* aParser = ParserYaml::getInstance();

	for( int i = 0; i < count; i++ ){
		b2Vec2 verts = poly->GetVertex(i);
		b2Vec2 f = this->body->GetWorldPoint(verts);
		//Log::d("Posicion vert %d: %.3f, %.3f",i, f.x, f.y);
		float x = f.x;
		float y = f.y;
		Log::t("Posicion vert (Modelo) %d: %.3f, %.3f",i, x, y);		
		vertexList.push_back(std::make_pair(x,y));
	}

	return vertexList;

}

//At each step links current box2d with model data
void Triangle::animate(){
	//Use userdata to reflect changes in physics to model
	//ToDo @aliguo
	GameElement* ge = static_cast<GameElement*>(this->body->GetUserData());
	b2Vec2 f = this->body->GetPosition();
	//Log::d("Nueva posicion (Physics): %.3f, %.3f", f.x, f.y);
	ParserYaml* aParser = ParserYaml::getInstance();
	float x = f.x;
	float y = f.y;
	ge->setPosition(std::make_pair( x,y) );
	//Log::d("Nueva posicion (Modelo): %.3f, %.3f", x,y);
	ge->setVertexList(this->GetVertex());

}

void Triangle::touch(Body* touchingWith, b2World* mundo) {

}

Triangle::~Triangle() {
	// Destroy from model first
	// ToDo @aliguo
}

