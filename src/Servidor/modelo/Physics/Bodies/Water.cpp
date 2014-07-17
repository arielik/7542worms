#include "Water.h"
#include <Box2D/Box2D.h>


Water::Water(float level, b2World* myWorld){
	this->waterLevel = level;
	
	Log::t("Water Level: %f", level);
	this->myWorld = myWorld;
	
	ParserYaml* aParser = ParserYaml::getInstance();

	b2BodyDef bd;
	bd.type = b2BodyType(0);
	bd.position.Set(0,0);
	bd.angle = 0.000000000000000e+00f;
	bd.linearVelocity.Set(0.000000000000000e+00f, 0.000000000000000e+00f);
	bd.angularVelocity = 0.000000000000000e+00f;
	bd.linearDamping = 0.000000000000000e+00f;
	bd.angularDamping = 0.000000000000000e+00f;
	bd.allowSleep = bool(4);
	bd.awake = bool(2);
	bd.fixedRotation = bool(0);
	bd.bullet = bool(0);
	bd.active = bool(32);
	bd.gravityScale = 1.000000000000000e+00f;
	b2Body* waterBody = this->myWorld->CreateBody(&bd);


	b2FixtureDef waterFixtureDef;

	
	waterFixtureDef.friction = 2.000000029802322e-01f;
	waterFixtureDef.restitution = 0.000000000000000e+00f;
	waterFixtureDef.density = 2.000000000000000e+00f;
	waterFixtureDef.isSensor = bool(1);
	waterFixtureDef.filter.categoryBits = uint16(1);
	waterFixtureDef.filter.maskBits = uint16(65535);
	waterFixtureDef.filter.groupIndex = int16(0);
	
	b2PolygonShape waterShape;
	b2Vec2 vs[8];

	vs[0].Set(-100.0,0.0);
	vs[1].Set(Util::string2float(aParser->getEscenarioAnchoU()) + 100.0, 0.0);
	vs[2].Set(Util::string2float(aParser->getEscenarioAnchoU()) + 100.0, level);
	vs[3].Set(-100.0, level);
	waterShape.Set(vs, 4);

	waterFixtureDef.shape = &waterShape;
	waterBody->CreateFixture(&waterFixtureDef);
	//std::string* desc = new std::string("water");
	
	waterBody->SetUserData( (void*) UD_WATER );
	this->body = waterBody;


}


Water::~Water() {
}