#include "GameController.h"
#include "..\..\utils\Log.h"

GameController::GameController(){
	rg = RunGame::getInstance();
}
GameController::~GameController(){}

void GameController::handlerEvent(){
	rg->addCallFromSDL();
	rg->addCallFromOver();
	rg->call();
}

bool GameController::isQuit(){
	return rg->isQuit();
}


void GameController::destroy(){
	//rg->destroy();
	
	Click* ck = Click::getInstance();
	ck->removeAll();
	
	Move* mv = Move::getInstance();
	mv->removeAll();

	Over* o = Over::getInstance();
	o->removeAll();

	Zoom* zm = Zoom::getInstance();
	zm->removeAll();

	Action* at = Action::getInstance();
	at->removeAll();

	Change* ch = Change::getInstance();
	ch->removeAll();

}

void GameController::addListener(OnClickListener* c){
	Click* ck = Click::getInstance();
	ck->add(c);
}
void GameController::addListener(OnMovementListener* m){
	Move* mv = Move::getInstance();
	mv->add(m);
	
}
void GameController::addOnScrollListener(OnScrollListener* s){
	Over* o = Over::getInstance();
	o->add(s);
}
void GameController::addOnZoomListener(OnZoomListener* z){
	Zoom* zm = Zoom::getInstance();
	zm->add(z);
}
void GameController::addOnActionListener(OnActionListener* a){
	Action* at = Action::getInstance();
	at->add(a);
}
void GameController::remuveListener(OnClickListener* c){
	Click* ck = Click::getInstance();
	ck->remuve(c);
}
void GameController::remuveListener(OnMovementListener* m){
	Move* mv = Move::getInstance();
	mv->remuve(m);
}
void GameController::remuveListener(OnScrollListener* s){
	Over* o = Over::getInstance();
	o->remuve(s);
}
void GameController::remuveListener(OnZoomListener* z){
	Zoom* zm = Zoom::getInstance();
	zm->remuve(z);
}
void GameController::remuveOnActionListener(OnActionListener* a){
	Action* at = Action::getInstance();
	at->remuve(a);
}
void GameController::addOnClickListener(OnClickListener* c)
{
	Click* ck = Click::getInstance();
	ck->add(c);
}
void GameController::addOnMovementListener(OnMovementListener* m)
{
	Move* mv = Move::getInstance();
	mv->add(m);
}
void GameController::remuveOnMovementListener(OnMovementListener* m)
{
	Move* mv = Move::getInstance();
	mv->remuve(m);
}
void GameController::remuveOnClickListener(OnClickListener* c)
{
	Click* ck = Click::getInstance();
	ck->remuve(c);
}

void GameController::addOnChangeListener(OnChangeListener* coord){
	Change* ch = Change::getInstance();
	ch->add(coord);
}
void GameController::remuveOnChangeListener(OnChangeListener* coord){
	Change* ch = Change::getInstance();
	ch->remuve(coord);
}