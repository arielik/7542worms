
#include "RunGame.h"
#include "..\..\utils\ParserYaml.h"
#include "..\..\utils\Constantes\Constantes.h"

RunGame* RunGame::runGame = NULL;

RunGame::RunGame(void){
	quit = false;
	this->loadQuadrantFactory();
	m_keys = SDL_GetKeyboardState(NULL);
	oldTime = newTime = factor = 0;
	isTimerRun = false;
}

RunGame::~RunGame(void){}

void RunGame::addCallFromOver(){
	SDL_PumpEvents();
	this->detectMouse();
	this->detectChange();
}


void RunGame::call(){
	listEvent.notify();
	listEvent.clear();
}

RunGame* RunGame::getInstance(){
	if(!runGame){
		runGame = new RunGame();
	}
	return runGame;
}

void RunGame::addCallFromSDL(){
	SDL_Event* ev = new SDL_Event();
	SDL_StartTextInput();
	while(SDL_PollEvent( ev ))
	{
		handleEvents(ev);
	}
	delete ev;
}

void RunGame::handleEvents(SDL_Event* e){
	SDL_PumpEvents();
	if(this->isValidKey(e)){
		execute(e, m_keys);
	}
	else if(e->type == SDL_QUIT){
		quit = true;
	}
}

bool RunGame::isQuit(){
	return quit;
}

bool RunGame::isValidKey(SDL_Event* e){
	return ((e->type == SDL_KEYDOWN) 
		||  (e->type == SDL_KEYUP)
		||  (e->type == SDL_MOUSEWHEEL)
		||  (e->type == SDL_MOUSEBUTTONDOWN)	);
}


void RunGame::execute(SDL_Event* e, const Uint8* keys){
	this->detectWheel(e);
	this->detectClick();
	this->detectMovem(e);
	//this->detectMovementAim(e);
}

Side RunGame::GetCursorLook(int xr, int yr){
	if(xr >= 0)
		return S_RIGHT;
	else if(xr < 0)
		return S_LEFT;
	else if(yr >= 0)
		return S_DOWN;
	else
		return S_UP;
}

void RunGame::detectChange(){
	Change* ch = Change::getInstance();
	int x, y = 0;
	SDL_GetMouseState(&x, &y);
	ch->setEvent(x,y);
	if(this->isTimerRun){
		ch->setStateBar(true);
		ch->setFactor(getFactor(timer.elapsed()));
	}
	else{
		ch->setStateBar(false);
	}
	if(ch->newEvent()){
		ch->setCoordenate(true);
	}
	else{
		ch->setCoordenate(false);
	}

	
	this->detectMovementAim();
	listEvent.add(ch);
}

void RunGame::detectWheel(SDL_Event* e){
	Zoom* z = Zoom::getInstance();
	if(e->wheel.type == SDL_MOUSEWHEEL){
		z->setEvent(e->wheel.y);
		listEvent.add(z);
	}
}

void RunGame::detectClick(){
	detectClickLeft();
	detectClickRight();
}

void RunGame::detectClickLeft(){
	Click* c = Click::getInstance();
	int x, y = 0;
	Uint32 button = SDL_GetMouseState(&x, &y);
	if(button & SDL_BUTTON(1)){
		c->setEvent(x, y);
		listEvent.add(c);
	}
}

void RunGame::detectClickRight(){
	Action* at = Action::getInstance();
	int x, y = 0;
	Uint32 button = SDL_GetMouseState(&x, &y);
	if(button & SDL_BUTTON(3)){
		at->setEvent(MENU);
		listEvent.add(at);
	}
}


void RunGame::detectMovementAim(){
	Change* ch = Change::getInstance();
/*	//if(e->type == SDL_KEYDOWN){
		if((e->type == SDL_KEYDOWN) &&
			this->isKeyPress(e, SDL_SCANCODE_UP)){
			ch->setAimMove(M_ANTICLOCK);
			ch->setAimEnter(true);
			//listEvent.add(ch);
		}
		else if((e->type == SDL_KEYDOWN) &&
			this->isKeyPress(e, SDL_SCANCODE_DOWN)){
			ch->setAimMove(M_SHEDULE);
			ch->setAimEnter(true);
			//listEvent.add(ch);
		}
		else{
			ch->setAimEnter(false);
		}*/


	if(m_keys[SDL_SCANCODE_UP]){
		ch->setAimMove(M_ANTICLOCK);
		ch->setAimEnter(true);	
	}
	else if(m_keys[SDL_SCANCODE_DOWN]){
		ch->setAimMove(M_SHEDULE);
		ch->setAimEnter(true);
	}
	else if(m_keys[SDL_SCANCODE_RIGHT]){
		ch->setAimMove(M_RIGHT);
		ch->setAimEnter(true);
	}
	else if(m_keys[SDL_SCANCODE_LEFT]){
		ch->setAimMove(M_LEFT);
		ch->setAimEnter(true);
	}
	else{
		ch->setAimEnter(false);
	}

	listEvent.add(ch);
	//}
}


void RunGame::detectMovem(SDL_Event* e){
	Move* mv = Move::getInstance();
	Action* at = Action::getInstance();

	if(e->type == SDL_KEYDOWN){

		if(e->key.keysym.scancode
		== SDL_SCANCODE_RETURN){
			if(isTimerRun == false){
				timer.start();
				isTimerRun = true;
			}
		}


		
		detectMovem(mv, 1, e);
		if(mv->newEvent()){
			listEvent.add(mv);
		}
	}
	else if(e->type == SDL_KEYUP){
		newTime = SDL_GetTicks();
		factor = newTime - oldTime;
		detectMovem(mv, 0, e);
		if(mv->newEvent()){
			listEvent.add(mv);
		}
		
		if(e->key.keysym.scancode
		== SDL_SCANCODE_RETURN){
			factor = getFactor(timer.elapsed());
			timer.reset();
			at->setEvent(SHOOT);
			at->setFactor(factor);
			listEvent.add(at);
			isTimerRun = false;
		}
	}


}



bool RunGame::isKeyPress(SDL_Event* e, SDL_Scancode sc){
	bool result = false;
	if(e->key.keysym.scancode == sc){
		result = true;
	}
	return result;
}

int RunGame::getFactor(float time){
	int result = 0;
	
	if ( time >= MAX_TIME_POWER)
		return MAX_POWER;

	result = (time / (float)MAX_TIME_POWER)*MAX_POWER;
	
	if(result <= 0)
		result = 1;

	return result;
}

void RunGame::detectMovem(Move* mv, int value, SDL_Event* e){
	SDL_Scancode sc = e->key.keysym.scancode;
	switch(sc){
		case SDL_SCANCODE_LEFT:
				mv->x = (-1)*value;
			break;
		case SDL_SCANCODE_RIGHT:
				mv->x = value;
			break;
		default:;
	}
	switch(sc){
		case SDL_SCANCODE_UP:
			mv->y = (-1)*value;
			break;
		case SDL_SCANCODE_DOWN:
			mv->y = value;
			break;
		case SDL_SCANCODE_SPACE:
			mv->y = (-1)*value;
			break;
		default:;
	}
}

void RunGame::detectMouse(){
	Over* ov = Over::getInstance();
	vector<PartialScreen*>::iterator it;
	PartialScreen* result = NULL;
	Side s;
	int x, y, xr, yr;
	SDL_GetMouseState(&x, &y);
	SDL_GetRelativeMouseState(&xr, &yr);
	s = this->GetCursorLook(xr, yr);
	for(it = this->screems.begin();
		it != this->screems.end();
		it++){
			result = (*it)->Inside(x, y, s);
			if(result != NULL){
				callScreen = result;
				callScreen->x = x;
				callScreen->y = y;
				break;
			}
	}
	callScreen->getSpeed(&x,&y);
	ov->setEvent(x,y);
	listEvent.add(ov);
}

void RunGame::destroy(){
	vector<PartialScreen*>::iterator it;
	for(it = this->screems.begin();
	it != this->screems.end();
	it++){
		delete (*it);
	}
}

void RunGame::loadQuadrantFactory(){
	PartialScreen* s1 = new PartialScreen();
	PartialScreen* s2 = new PartialScreen();
	PartialScreen* s3 = new PartialScreen();
	PartialScreen* s4 = new PartialScreen();
	PartialScreen* s5 = new PartialScreen();
	PartialScreen* s6 = new PartialScreen();
	PartialScreen* s7 = new PartialScreen();
	PartialScreen* s8 = new PartialScreen();
	PartialScreen* s9 = new PartialScreen();

	//seteo id
	s1->id = QUADRANT_1, s2->id = QUADRANT_2;
	s3->id = QUADRANT_3, s4->id = QUADRANT_4;
	s5->id = QUADRANT_5, s6->id = QUADRANT_6;
	s7->id = QUADRANT_7, s8->id = QUADRANT_8;
	s9->id = QUADRANT_9;

	//seteo rangos
	std::map<std::string,std::string> prop = Util::loadProperteries("config/client.properties");
	int w = Util::string2int(prop["ventana.ancho"]);
	int h = Util::string2int(prop["ventana.alto"]);

	this->WIDTH = w;
	this->HIGHT = h;

	s1->xFrom = 0, s1->xTo = DELTA, s1->yFrom = 0, s1->yTo = DELTA;
	s2->xFrom = WIDTH - DELTA, s2->xTo = WIDTH, s2->yFrom = 0, s2->yTo = DELTA;
	s3->xFrom = 0, s3->xTo = DELTA, s3->yFrom = HIGHT - DELTA, s3->yTo = HIGHT;
	s4->xFrom = WIDTH - DELTA, s4->xTo = WIDTH, s4->yFrom = HIGHT - DELTA, s4->yTo = HIGHT;
	s5->xFrom = DELTA, s5->xTo = WIDTH - DELTA, s5->yFrom = 0, s5->yTo = DELTA;
	s6->xFrom = DELTA, s6->xTo = WIDTH - DELTA, s6->yFrom = HIGHT - DELTA, s6->yTo = HIGHT;
	s7->xFrom = 0, s7->xTo = DELTA, s7->yFrom = DELTA, s7->yTo = HIGHT - DELTA;
	s8->xFrom = WIDTH - DELTA, s8->xTo = WIDTH, s8->yFrom = DELTA, s8->yTo = HIGHT - DELTA;
	s9->xFrom = DELTA, s9->xTo = WIDTH - DELTA, s9->yFrom = DELTA, s9->yTo = HIGHT - DELTA;

	//Seteo relaciones
	s1->dir.insert(pair<int, Side>(QUADRANT_5, S_RIGHT));
	s1->dir.insert(pair<int, Side>(QUADRANT_7, S_DOWN));
	s1->addRelationScreen(s5), s1->addRelationScreen(s7);

	s2->dir.insert(pair<int, Side>(QUADRANT_5, S_LEFT));
	s2->dir.insert(pair<int, Side>(QUADRANT_8, S_DOWN));
	s2->addRelationScreen(s5), s2->addRelationScreen(s8);

	s3->dir.insert(pair<int, Side>(QUADRANT_6, S_RIGHT));
	s3->dir.insert(pair<int, Side>(QUADRANT_7, S_UP));
	s3->addRelationScreen(s6), s3->addRelationScreen(s7);

	s4->dir.insert(pair<int, Side>(QUADRANT_6, S_LEFT));
	s4->dir.insert(pair<int, Side>(QUADRANT_8, S_UP));
	s4->addRelationScreen(s6), s4->addRelationScreen(s8);

	s5->dir.insert(pair<int, Side>(QUADRANT_1, S_LEFT));
	s5->dir.insert(pair<int, Side>(QUADRANT_2, S_RIGHT));
	s5->addRelationScreen(s1), s5->addRelationScreen(s2);

	s6->dir.insert(pair<int, Side>(QUADRANT_3, S_LEFT));
	s6->dir.insert(pair<int, Side>(QUADRANT_4, S_RIGHT));
	s6->addRelationScreen(s3), s6->addRelationScreen(s4);

	s7->dir.insert(pair<int, Side>(QUADRANT_1, S_UP));
	s7->dir.insert(pair<int, Side>(QUADRANT_3, S_DOWN));
	s7->addRelationScreen(s1), s7->addRelationScreen(s3);

	s8->dir.insert(pair<int, Side>(QUADRANT_2, S_UP));
	s8->dir.insert(pair<int, Side>(QUADRANT_4, S_DOWN));
	s8->addRelationScreen(s2), s8->addRelationScreen(s4);

	s9->dir.insert(pair<int, Side>(QUADRANT_5, S_UP));
	s9->dir.insert(pair<int, Side>(QUADRANT_6, S_DOWN));
	s9->dir.insert(pair<int, Side>(QUADRANT_7, S_LEFT));
	s9->dir.insert(pair<int, Side>(QUADRANT_8, S_RIGHT));
	s9->addRelationScreen(s5), s9->addRelationScreen(s6);
	s9->addRelationScreen(s7), s9->addRelationScreen(s8);      
									//QUADRANT						   
	//seteo las direcciones		    //+-+----------------------------------+-+ 
	s1->xDir	 = -1, s1->yDir = -1,   //|1|                5                 |2| 
	s2->xDir = -1, s2->yDir = -1,   //+-+----------------------------------+-+ 
	s3->xDir = -1, s3->yDir = -1,   //| |                                  | | 
	s4->xDir = -1, s4->yDir = -1,   //| |                                  | | 
	s5->xDir =  0, s5->yDir = -1,   //|7|                9                 |8| 
	s6->xDir =  0, s6->yDir = -1,   //| |                                  | | 
	s7->xDir = -1, s7->yDir =  0,   //| |                                  | | 
	s8->xDir = -1, s8->yDir =  0,   //+-+----------------------------------+-+ 
	s9->xDir =  0, s9->yDir =  0;   //|3|                6                 |4| 
								    //+-+----------------------------------+-+ 
	                                 
	//seteo el limite                                 
	s1->xlimit = s1->xTo,   s1->ylimit = s1->yTo,	
	s2->xlimit = s2->xFrom, s2->ylimit = s2->yTo,
	s3->xlimit = s3->xTo, 	s3->ylimit = s3->yFrom,	
	s4->xlimit = s4->xFrom, s4->ylimit = s4->yFrom,
	s5->xlimit = s5->xTo,   s5->ylimit = s5->yTo,
	s6->xlimit = s6->xFrom, s6->ylimit = s6->yFrom,
	s7->xlimit = s7->xTo,   s7->ylimit = s7->xTo,
	s8->xlimit = s8->xFrom, s8->ylimit = s8->xFrom,
	s9->xlimit =  0,        s9->ylimit =  0;
	
	//Los agrego para luego recorrerlos			
	screems.push_back(s1), screems.push_back(s2);
	screems.push_back(s3), screems.push_back(s4);
	screems.push_back(s5), screems.push_back(s6);
	screems.push_back(s7), screems.push_back(s8);
	screems.push_back(s9);
	                                              
}




