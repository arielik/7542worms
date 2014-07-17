#include "GameElement.h"

GameElement::GameElement(){
}




int GameElement::getLife()
{
	return this->life;
}

void GameElement::setLife(int newLife)
{
this->life=newLife;
}

void GameElement::addLife(int moreLife)
{
 this->life= this->life+moreLife;
}

void GameElement::subLife(int lessLife)
{
	if ( !this->damaged ){
		this->life= this->life-lessLife;
		if ( this->life <= 0 ){
			this->setAlive(false);
			this->life = 0;
			this->action = DEAD;
			

			this->changed = true;
		}
		this->damaged = true;
	}
}


/* Rectangle constructor */
GameElement::GameElement(int id, ElementType type, float posX, float posY, float degrees, float h, float w, float mass, bool isFixed){
	
			this->id = id;
			this->changed = false;
			this->type = type;
			this->degrees = degrees;
			this->position = std::make_pair(posX,posY);
			this->height = h;
			this->width = w;
			this->mass = mass;
			this->fixed = isFixed;
			this->grounded = false;
}

GameElement::GameElement(int id, std::string playerID, ElementType type, float posX, float posY, float degrees, float h, float w, float mass, bool isFixed){
			
			this->playerID.assign(playerID.c_str());
			this->id = id;
			this->changed = false;
			this->type = type;
			this->degrees = degrees;
			this->position = std::make_pair(posX,posY);
			this->height = h;
			this->width = w;
			this->mass = mass;
			this->fixed = isFixed;
			this->grounded = false;
}

/* Circle constructor */
GameElement::GameElement(int id, float posX, float posY, float radius, float scale, float mass, bool fixed)
{
	this->id = id;
	this->changed = false;
	this->type = CIRCLE;
	this->position = std::make_pair(posX,posY);
	this->mass = mass;
	this->radius = radius;
	this->scale = scale;
	this->fixed = fixed;
	this->grounded = false;
}

/* Any other polygon constructor */
GameElement::GameElement(int id, ElementType type, float posX, float posY, float scale, float degrees, float mass, bool isFixed){
	
			this->id = id;
			this->changed = false;
			this->type = type;
			this->degrees = degrees;
			this->position = std::make_pair(posX,posY);
			this->scale = scale;
			this->mass = mass;
			this->fixed = isFixed;
			this->grounded = false;
}




GameElement::GameElement(const GameElement & aGameElement):
					id(aGameElement.id), playerID(aGameElement.playerID), changed(aGameElement.changed), 
					ratio(aGameElement.ratio), type(aGameElement.type),
					position(aGameElement.position), height(aGameElement.type), 
					mass(aGameElement.type), myBody(aGameElement.myBody),
					degrees(aGameElement.degrees), vertexList(aGameElement.vertexList),
					radius(aGameElement.radius), scale(aGameElement.scale),
					fixed(aGameElement.fixed), grounded(aGameElement.grounded), action(aGameElement.action),
					myLastAction(aGameElement.myLastAction), life(aGameElement.life),weaponId(aGameElement.weaponId)
{
}


void GameElement::setVertexList(std::list<std::pair<float,float>> l){
	this->vertexList = l;
}

void GameElement::setBody(void* ab){
	Log::d("Guardando: %p",ab); 
	this->myBody = ab;
}

int GameElement::getId(){
	return this->id;
}

std::list<std::pair<float,float>> & GameElement::getVertex(){
	return this->vertexList;
}

ElementType GameElement::getType(){
	return this->type;
}

float GameElement::getRotation(){
	return this->degrees;
}

float GameElement::getHeight(){
	return this->height;
}

float GameElement::getMass(){
	return this->mass;
}

float GameElement::getWidth(){
	return this->width;
}

std::pair<float,float> GameElement::getPosition(){
	return this->position;
}

void GameElement::setPosition(std::pair<float,float> p){
	this->position = p;
}

void GameElement::setAngle(float angle){
	this->degrees = angle;
}


bool GameElement::hasChanged(){
	return this->changed;
}

float GameElement::getRadius()
{
	return this->radius;
}

float GameElement::getScale()
{
	return this->scale;
}

bool GameElement::isFixed()
{
	return this->fixed;
}

bool GameElement::hasExploded()
{ 
	return this->exploded;
}