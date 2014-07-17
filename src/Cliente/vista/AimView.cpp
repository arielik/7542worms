#include "AimView.h"
#include "TextureManager.h"

AimView::AimView():View(30,30){
	bShootMouse = 
	bShootEnter = 
	bRight =
	bLeft = false;
	createPositionAimEnter();
	it = aimEnter.begin();
}

AimView::~AimView(){}


void AimView::aimBuild(){
	switch(this->weapon->getId()){
		case BURRO:
		case AIRATTACK:
		case HMISSILE:
			aimBuildMouse();
			break;
		case BAZOOKA:
		case GRENADE:
		case HOLY:
		case BANANA:
		case SHEEP:
			aimBuildEnter();
			break;
		default:;
	}
}

void AimView::setWorm(WormView* aWorm, Weapon* aWeapon){

	this->worm = aWorm;
	this->weapon = aWeapon;
}
void AimView::aimBuildEnter(){
	this->centerPoint();
	this->generatePoint();
	this->xDraw = this->x + this->xRelative; 
	this->yDraw = this->y + this->yRelative;

	bShootEnter = true;
	bShootMouse = false;

	if(this->worm->getDirection() == D_LEFT){
		this->renderAimLeft();
	}
	else{
		this->renderAimRight();
	}
}

void AimView::aimBuildMouse(){
	bShootMouse = true;
	bShootEnter = false;
	SDL_ShowCursor(0);
}

bool AimView::isShootMouse(){
	return bShootMouse;
}

bool AimView::isShootEnter(){
	return bShootEnter;
}

void AimView::unAim(){
	bShootMouse = 
	bShootEnter = false;
	SDL_ShowCursor(1);
}

void AimView::OnChange(ChangeEvent e){
	/*if(e.isStateBar()){
		Log::i("Factor: %d", e.factor);
	}*/
	if(bShootMouse && e.isCoordenate()){
		this->xDraw = e.x - 30;
		this->yDraw = e.y - 30;
		this->updateWormSide();
	} 
	if(bShootEnter && e.isAimEnter()){   
		if(e.aimMove == M_ANTICLOCK){
			this->pointUp();
		}
		else if(e.aimMove == M_SHEDULE){ 
			this->pointUnder();
		}
		this->centerPoint();
		this->generatePoint();
		this->xDraw = this->x + this->xRelative; 
		this->yDraw = this->y + this->yRelative;
		this->updateWormSide();
	}
}

void AimView::OnMovement(MovementEvent e){
	if(bShootEnter){
		if(e.y == -1){
			
		}
		else if(e.y == 1){
			
		}
		else if((e.x == -1) && (!this->bLeft)){
			this->renderAimLeft();
		}
		else if((e.x == 1) && (!this->bRight)){
			this->renderAimRight();
		}

	}
}

int AimView::getAngle(){
	return it->first;
}

void AimView::updateWormSide(){
	if(this->x <= this->xDraw){
		if(!bRight){
			bRight = true;
			bLeft = false;
		}
	}
	else if (this->x > this->xDraw){
		if(!bLeft){
			bLeft = true;
			bRight = false;
		}
	}
}

bool AimView::isRightSide(){
	return bRight;
}

bool AimView::isLeftSide(){
	return bLeft;
}

pair<int, int> AimView::getData(){
	return pair<int, int>(this->worm->getId(), this->weapon->getId());
}

void AimView::pointUp(){
	int angle = it->first;
	if((360 - angle) < PASO){
		it = aimEnter.begin();
	} 
	for(int i = 0; i < PASO; i++){
		it++;
	}
}

void AimView::pointUnder(){
	int angle = it->first;
	if((angle) < PASO){
		it = aimEnter.end();
	}
	for(int i = 0; i < PASO; i++){
		it--;
	}
}

void AimView::renderAimLeft(){
	it = aimEnter.begin();
	int max = 180/PASO;
	for(int i = 0; i < max; i++){
		this->pointUp();
	} 
	//this->centerPoint();
	//this->generatePoint();
	//this->xDraw = this->x + this->xRelative; 
	//this->yDraw = this->y + this->yRelative;
}

void AimView::renderAimRight(){
	it = aimEnter.begin();
	this->centerPoint();
	this->generatePoint();
	this->xDraw = this->x + this->xRelative; 
	this->yDraw = this->y + this->yRelative;
}

void AimView::generatePoint(){
	pair<float,float> factor = it->second;
	this->xRelative = RADIO * factor.first;
	this->yRelative = RADIO * factor.second * -1;
}

void AimView::centerPoint(){
	this->x = this->worm->getXCenter();
	this->y = this->worm->getYCenter();
}



void AimView::draw(SDLScreen & screen){
	if(bShootMouse){
		TextureManager::Instance().drawFrame(
						"aim", this->xDraw, this->yDraw, 60, 57, 
						0, 0, screen.getRenderer(),
						false, SDL_FLIP_NONE);
		}
	else if(bShootEnter){
		this->centerPoint();
		this->generatePoint();
		this->xDraw = this->x + this->xRelative; 
		this->yDraw = this->y + this->yRelative;
		TextureManager::Instance().drawFrame(
						"aim", this->xDraw, this->yDraw, 60, 57, 
						0, 0, screen.getRenderer(),
						false, SDL_FLIP_NONE, true);
	}
}





void AimView::createPositionAimEnter(){
	if(!aimEnter.size()){
		
		aimEnter.insert(pair<int,pair<float, float>>(0,pair<float, float>(1.000,0.000)));
		aimEnter.insert(pair<int,pair<float, float>>(1,pair<float, float>(1.000,0.017)));
		aimEnter.insert(pair<int,pair<float, float>>(2,pair<float, float>(0.999,0.035)));
		aimEnter.insert(pair<int,pair<float, float>>(3,pair<float, float>(0.999,0.052)));
		aimEnter.insert(pair<int,pair<float, float>>(4,pair<float, float>(0.998,0.070)));
		aimEnter.insert(pair<int,pair<float, float>>(5,pair<float, float>(0.996,0.087)));
		aimEnter.insert(pair<int,pair<float, float>>(6,pair<float, float>(0.995,0.105)));
		aimEnter.insert(pair<int,pair<float, float>>(7,pair<float, float>(0.993,0.122)));
		aimEnter.insert(pair<int,pair<float, float>>(8,pair<float, float>(0.990,0.139)));
		aimEnter.insert(pair<int,pair<float, float>>(9,pair<float, float>(0.988,0.156)));
		aimEnter.insert(pair<int,pair<float, float>>(10,pair<float, float>(0.985,0.174)));
		aimEnter.insert(pair<int,pair<float, float>>(11,pair<float, float>(0.982,0.191)));
		aimEnter.insert(pair<int,pair<float, float>>(12,pair<float, float>(0.978,0.208)));
		aimEnter.insert(pair<int,pair<float, float>>(13,pair<float, float>(0.974,0.225)));
		aimEnter.insert(pair<int,pair<float, float>>(14,pair<float, float>(0.970,0.242)));
		aimEnter.insert(pair<int,pair<float, float>>(15,pair<float, float>(0.966,0.259)));
		aimEnter.insert(pair<int,pair<float, float>>(16,pair<float, float>(0.961,0.276)));
		aimEnter.insert(pair<int,pair<float, float>>(17,pair<float, float>(0.956,0.292)));
		aimEnter.insert(pair<int,pair<float, float>>(18,pair<float, float>(0.951,0.309)));
		aimEnter.insert(pair<int,pair<float, float>>(19,pair<float, float>(0.946,0.326)));
		aimEnter.insert(pair<int,pair<float, float>>(20,pair<float, float>(0.940,0.342)));
		aimEnter.insert(pair<int,pair<float, float>>(21,pair<float, float>(0.934,0.358)));
		aimEnter.insert(pair<int,pair<float, float>>(22,pair<float, float>(0.927,0.375)));
		aimEnter.insert(pair<int,pair<float, float>>(23,pair<float, float>(0.921,0.391)));
		aimEnter.insert(pair<int,pair<float, float>>(24,pair<float, float>(0.914,0.407)));
		aimEnter.insert(pair<int,pair<float, float>>(25,pair<float, float>(0.906,0.423)));
		aimEnter.insert(pair<int,pair<float, float>>(26,pair<float, float>(0.899,0.438)));
		aimEnter.insert(pair<int,pair<float, float>>(27,pair<float, float>(0.891,0.454)));
		aimEnter.insert(pair<int,pair<float, float>>(28,pair<float, float>(0.883,0.469)));
		aimEnter.insert(pair<int,pair<float, float>>(29,pair<float, float>(0.875,0.485)));
		aimEnter.insert(pair<int,pair<float, float>>(30,pair<float, float>(0.866,0.500)));
		aimEnter.insert(pair<int,pair<float, float>>(31,pair<float, float>(0.857,0.515)));
		aimEnter.insert(pair<int,pair<float, float>>(32,pair<float, float>(0.848,0.530)));
		aimEnter.insert(pair<int,pair<float, float>>(33,pair<float, float>(0.839,0.545)));
		aimEnter.insert(pair<int,pair<float, float>>(34,pair<float, float>(0.829,0.559)));
		aimEnter.insert(pair<int,pair<float, float>>(35,pair<float, float>(0.819,0.574)));
		aimEnter.insert(pair<int,pair<float, float>>(36,pair<float, float>(0.809,0.588)));
		aimEnter.insert(pair<int,pair<float, float>>(37,pair<float, float>(0.799,0.602)));
		aimEnter.insert(pair<int,pair<float, float>>(38,pair<float, float>(0.788,0.616)));
		aimEnter.insert(pair<int,pair<float, float>>(39,pair<float, float>(0.777,0.629)));
		aimEnter.insert(pair<int,pair<float, float>>(40,pair<float, float>(0.766,0.643)));
		aimEnter.insert(pair<int,pair<float, float>>(41,pair<float, float>(0.755,0.656)));
		aimEnter.insert(pair<int,pair<float, float>>(42,pair<float, float>(0.743,0.669)));
		aimEnter.insert(pair<int,pair<float, float>>(43,pair<float, float>(0.731,0.682)));
		aimEnter.insert(pair<int,pair<float, float>>(44,pair<float, float>(0.719,0.695)));
		aimEnter.insert(pair<int,pair<float, float>>(45,pair<float, float>(0.707,0.707)));
		aimEnter.insert(pair<int,pair<float, float>>(46,pair<float, float>(0.695,0.719)));
		aimEnter.insert(pair<int,pair<float, float>>(47,pair<float, float>(0.682,0.731)));
		aimEnter.insert(pair<int,pair<float, float>>(48,pair<float, float>(0.669,0.743)));
		aimEnter.insert(pair<int,pair<float, float>>(49,pair<float, float>(0.656,0.755)));
		aimEnter.insert(pair<int,pair<float, float>>(50,pair<float, float>(0.643,0.766)));
		aimEnter.insert(pair<int,pair<float, float>>(51,pair<float, float>(0.629,0.777)));
		aimEnter.insert(pair<int,pair<float, float>>(52,pair<float, float>(0.616,0.788)));
		aimEnter.insert(pair<int,pair<float, float>>(53,pair<float, float>(0.602,0.799)));
		aimEnter.insert(pair<int,pair<float, float>>(54,pair<float, float>(0.588,0.809)));
		aimEnter.insert(pair<int,pair<float, float>>(55,pair<float, float>(0.574,0.819)));
		aimEnter.insert(pair<int,pair<float, float>>(56,pair<float, float>(0.559,0.829)));
		aimEnter.insert(pair<int,pair<float, float>>(57,pair<float, float>(0.545,0.839)));
		aimEnter.insert(pair<int,pair<float, float>>(58,pair<float, float>(0.530,0.848)));
		aimEnter.insert(pair<int,pair<float, float>>(59,pair<float, float>(0.515,0.857)));
		aimEnter.insert(pair<int,pair<float, float>>(60,pair<float, float>(0.500,0.866)));
		aimEnter.insert(pair<int,pair<float, float>>(61,pair<float, float>(0.485,0.875)));
		aimEnter.insert(pair<int,pair<float, float>>(62,pair<float, float>(0.469,0.883)));
		aimEnter.insert(pair<int,pair<float, float>>(63,pair<float, float>(0.454,0.891)));
		aimEnter.insert(pair<int,pair<float, float>>(64,pair<float, float>(0.438,0.899)));
		aimEnter.insert(pair<int,pair<float, float>>(65,pair<float, float>(0.423,0.906)));
		aimEnter.insert(pair<int,pair<float, float>>(66,pair<float, float>(0.407,0.914)));
		aimEnter.insert(pair<int,pair<float, float>>(67,pair<float, float>(0.391,0.921)));
		aimEnter.insert(pair<int,pair<float, float>>(68,pair<float, float>(0.375,0.927)));
		aimEnter.insert(pair<int,pair<float, float>>(69,pair<float, float>(0.358,0.934)));
		aimEnter.insert(pair<int,pair<float, float>>(70,pair<float, float>(0.342,0.940)));
		aimEnter.insert(pair<int,pair<float, float>>(71,pair<float, float>(0.326,0.946)));
		aimEnter.insert(pair<int,pair<float, float>>(72,pair<float, float>(0.309,0.951)));
		aimEnter.insert(pair<int,pair<float, float>>(73,pair<float, float>(0.292,0.956)));
		aimEnter.insert(pair<int,pair<float, float>>(74,pair<float, float>(0.276,0.961)));
		aimEnter.insert(pair<int,pair<float, float>>(75,pair<float, float>(0.259,0.966)));
		aimEnter.insert(pair<int,pair<float, float>>(76,pair<float, float>(0.242,0.970)));
		aimEnter.insert(pair<int,pair<float, float>>(77,pair<float, float>(0.225,0.974)));
		aimEnter.insert(pair<int,pair<float, float>>(78,pair<float, float>(0.208,0.978)));
		aimEnter.insert(pair<int,pair<float, float>>(79,pair<float, float>(0.191,0.982)));
		aimEnter.insert(pair<int,pair<float, float>>(80,pair<float, float>(0.174,0.985)));
		aimEnter.insert(pair<int,pair<float, float>>(81,pair<float, float>(0.156,0.988)));
		aimEnter.insert(pair<int,pair<float, float>>(82,pair<float, float>(0.139,0.990)));
		aimEnter.insert(pair<int,pair<float, float>>(83,pair<float, float>(0.122,0.993)));
		aimEnter.insert(pair<int,pair<float, float>>(84,pair<float, float>(0.105,0.995)));
		aimEnter.insert(pair<int,pair<float, float>>(85,pair<float, float>(0.087,0.996)));
		aimEnter.insert(pair<int,pair<float, float>>(86,pair<float, float>(0.070,0.998)));
		aimEnter.insert(pair<int,pair<float, float>>(87,pair<float, float>(0.052,0.999)));
		aimEnter.insert(pair<int,pair<float, float>>(88,pair<float, float>(0.035,0.999)));
		aimEnter.insert(pair<int,pair<float, float>>(89,pair<float, float>(0.017,1.000)));
		aimEnter.insert(pair<int,pair<float, float>>(90,pair<float, float>( 0.000,1.000)));
		aimEnter.insert(pair<int,pair<float, float>>(91,pair<float, float>(-0.017,1.000)));
		aimEnter.insert(pair<int,pair<float, float>>(92,pair<float, float>(-0.035,0.999)));
		aimEnter.insert(pair<int,pair<float, float>>(93,pair<float, float>(-0.052,0.999)));
		aimEnter.insert(pair<int,pair<float, float>>(94,pair<float, float>(-0.070,0.998)));
		aimEnter.insert(pair<int,pair<float, float>>(95,pair<float, float>(-0.087,0.996)));
		aimEnter.insert(pair<int,pair<float, float>>(96,pair<float, float>(-0.105,0.995)));
		aimEnter.insert(pair<int,pair<float, float>>(97,pair<float, float>(-0.122,0.993)));
		aimEnter.insert(pair<int,pair<float, float>>(98,pair<float, float>(-0.139,0.990)));
		aimEnter.insert(pair<int,pair<float, float>>(99,pair<float, float>(-0.156,0.988)));
		aimEnter.insert(pair<int,pair<float, float>>(100,pair<float, float>(-0.174,0.985)));
		aimEnter.insert(pair<int,pair<float, float>>(101,pair<float, float>(-0.191,0.982)));
		aimEnter.insert(pair<int,pair<float, float>>(102,pair<float, float>(-0.208,0.978)));
		aimEnter.insert(pair<int,pair<float, float>>(103,pair<float, float>(-0.225,0.974)));
		aimEnter.insert(pair<int,pair<float, float>>(104,pair<float, float>(-0.242,0.970)));
		aimEnter.insert(pair<int,pair<float, float>>(105,pair<float, float>(-0.259,0.966)));
		aimEnter.insert(pair<int,pair<float, float>>(106,pair<float, float>(-0.276,0.961)));
		aimEnter.insert(pair<int,pair<float, float>>(107,pair<float, float>(-0.292,0.956)));
		aimEnter.insert(pair<int,pair<float, float>>(108,pair<float, float>(-0.309,0.951)));
		aimEnter.insert(pair<int,pair<float, float>>(109,pair<float, float>(-0.326,0.946)));
		aimEnter.insert(pair<int,pair<float, float>>(110,pair<float, float>(-0.342,0.940)));
		aimEnter.insert(pair<int,pair<float, float>>(111,pair<float, float>(-0.358,0.934)));
		aimEnter.insert(pair<int,pair<float, float>>(112,pair<float, float>(-0.375,0.927)));
		aimEnter.insert(pair<int,pair<float, float>>(113,pair<float, float>(-0.391,0.921)));
		aimEnter.insert(pair<int,pair<float, float>>(114,pair<float, float>(-0.407,0.914)));
		aimEnter.insert(pair<int,pair<float, float>>(115,pair<float, float>(-0.423,0.906)));
		aimEnter.insert(pair<int,pair<float, float>>(116,pair<float, float>(-0.438,0.899)));
		aimEnter.insert(pair<int,pair<float, float>>(117,pair<float, float>(-0.454,0.891)));
		aimEnter.insert(pair<int,pair<float, float>>(118,pair<float, float>(-0.469,0.883)));
		aimEnter.insert(pair<int,pair<float, float>>(119,pair<float, float>(-0.485,0.875)));
		aimEnter.insert(pair<int,pair<float, float>>(120,pair<float, float>(-0.500,0.866)));
		aimEnter.insert(pair<int,pair<float, float>>(121,pair<float, float>(-0.515,0.857)));
		aimEnter.insert(pair<int,pair<float, float>>(122,pair<float, float>(-0.530,0.848)));
		aimEnter.insert(pair<int,pair<float, float>>(123,pair<float, float>(-0.545,0.839)));
		aimEnter.insert(pair<int,pair<float, float>>(124,pair<float, float>(-0.559,0.829)));
		aimEnter.insert(pair<int,pair<float, float>>(125,pair<float, float>(-0.574,0.819)));
		aimEnter.insert(pair<int,pair<float, float>>(126,pair<float, float>(-0.588,0.809)));
		aimEnter.insert(pair<int,pair<float, float>>(127,pair<float, float>(-0.602,0.799)));
		aimEnter.insert(pair<int,pair<float, float>>(128,pair<float, float>(-0.616,0.788)));
		aimEnter.insert(pair<int,pair<float, float>>(129,pair<float, float>(-0.629,0.777)));
		aimEnter.insert(pair<int,pair<float, float>>(130,pair<float, float>(-0.643,0.766)));
		aimEnter.insert(pair<int,pair<float, float>>(131,pair<float, float>(-0.656,0.755)));
		aimEnter.insert(pair<int,pair<float, float>>(132,pair<float, float>(-0.669,0.743)));
		aimEnter.insert(pair<int,pair<float, float>>(133,pair<float, float>(-0.682,0.731)));
		aimEnter.insert(pair<int,pair<float, float>>(134,pair<float, float>(-0.695,0.719)));
		aimEnter.insert(pair<int,pair<float, float>>(135,pair<float, float>(-0.707,0.707)));
		aimEnter.insert(pair<int,pair<float, float>>(136,pair<float, float>(-0.719,0.695)));
		aimEnter.insert(pair<int,pair<float, float>>(137,pair<float, float>(-0.731,0.682)));
		aimEnter.insert(pair<int,pair<float, float>>(138,pair<float, float>(-0.743,0.669)));
		aimEnter.insert(pair<int,pair<float, float>>(139,pair<float, float>(-0.755,0.656)));
		aimEnter.insert(pair<int,pair<float, float>>(140,pair<float, float>(-0.766,0.643)));
		aimEnter.insert(pair<int,pair<float, float>>(141,pair<float, float>(-0.777,0.629)));
		aimEnter.insert(pair<int,pair<float, float>>(142,pair<float, float>(-0.788,0.616)));
		aimEnter.insert(pair<int,pair<float, float>>(143,pair<float, float>(-0.799,0.602)));
		aimEnter.insert(pair<int,pair<float, float>>(144,pair<float, float>(-0.809,0.588)));
		aimEnter.insert(pair<int,pair<float, float>>(145,pair<float, float>(-0.819,0.574)));
		aimEnter.insert(pair<int,pair<float, float>>(146,pair<float, float>(-0.829,0.559)));
		aimEnter.insert(pair<int,pair<float, float>>(147,pair<float, float>(-0.839,0.545)));
		aimEnter.insert(pair<int,pair<float, float>>(148,pair<float, float>(-0.848,0.530)));
		aimEnter.insert(pair<int,pair<float, float>>(149,pair<float, float>(-0.857,0.515)));
		aimEnter.insert(pair<int,pair<float, float>>(150,pair<float, float>(-0.866,0.500)));
		aimEnter.insert(pair<int,pair<float, float>>(151,pair<float, float>(-0.875,0.485)));
		aimEnter.insert(pair<int,pair<float, float>>(152,pair<float, float>(-0.883,0.469)));
		aimEnter.insert(pair<int,pair<float, float>>(153,pair<float, float>(-0.891,0.454)));
		aimEnter.insert(pair<int,pair<float, float>>(154,pair<float, float>(-0.899,0.438)));
		aimEnter.insert(pair<int,pair<float, float>>(155,pair<float, float>(-0.906,0.423)));
		aimEnter.insert(pair<int,pair<float, float>>(156,pair<float, float>(-0.914,0.407)));
		aimEnter.insert(pair<int,pair<float, float>>(157,pair<float, float>(-0.921,0.391)));
		aimEnter.insert(pair<int,pair<float, float>>(158,pair<float, float>(-0.927,0.375)));
		aimEnter.insert(pair<int,pair<float, float>>(159,pair<float, float>(-0.934,0.358)));
		aimEnter.insert(pair<int,pair<float, float>>(160,pair<float, float>(-0.940,0.342)));
		aimEnter.insert(pair<int,pair<float, float>>(161,pair<float, float>(-0.946,0.326)));
		aimEnter.insert(pair<int,pair<float, float>>(162,pair<float, float>(-0.951,0.309)));
		aimEnter.insert(pair<int,pair<float, float>>(163,pair<float, float>(-0.956,0.292)));
		aimEnter.insert(pair<int,pair<float, float>>(164,pair<float, float>(-0.961,0.276)));
		aimEnter.insert(pair<int,pair<float, float>>(165,pair<float, float>(-0.966,0.259)));
		aimEnter.insert(pair<int,pair<float, float>>(166,pair<float, float>(-0.970,0.242)));
		aimEnter.insert(pair<int,pair<float, float>>(167,pair<float, float>(-0.974,0.225)));
		aimEnter.insert(pair<int,pair<float, float>>(168,pair<float, float>(-0.978,0.208)));
		aimEnter.insert(pair<int,pair<float, float>>(169,pair<float, float>(-0.982,0.191)));
		aimEnter.insert(pair<int,pair<float, float>>(170,pair<float, float>(-0.985,0.174)));
		aimEnter.insert(pair<int,pair<float, float>>(171,pair<float, float>(-0.988,0.156)));
		aimEnter.insert(pair<int,pair<float, float>>(172,pair<float, float>(-0.990,0.139)));
		aimEnter.insert(pair<int,pair<float, float>>(173,pair<float, float>(-0.993,0.122)));
		aimEnter.insert(pair<int,pair<float, float>>(174,pair<float, float>(-0.995,0.105)));
		aimEnter.insert(pair<int,pair<float, float>>(175,pair<float, float>(-0.996,0.087)));
		aimEnter.insert(pair<int,pair<float, float>>(176,pair<float, float>(-0.998,0.070)));
		aimEnter.insert(pair<int,pair<float, float>>(177,pair<float, float>(-0.999,0.052)));
		aimEnter.insert(pair<int,pair<float, float>>(178,pair<float, float>(-0.999,0.035)));
		aimEnter.insert(pair<int,pair<float, float>>(179,pair<float, float>(-1.000,0.017)));
		aimEnter.insert(pair<int,pair<float, float>>(180,pair<float, float>(-1.000, 0.000)));
		aimEnter.insert(pair<int,pair<float, float>>(181,pair<float, float>(-1.000,-0.017)));
		aimEnter.insert(pair<int,pair<float, float>>(182,pair<float, float>(-0.999,-0.035)));
		aimEnter.insert(pair<int,pair<float, float>>(183,pair<float, float>(-0.999,-0.052)));
		aimEnter.insert(pair<int,pair<float, float>>(184,pair<float, float>(-0.998,-0.070)));
		aimEnter.insert(pair<int,pair<float, float>>(185,pair<float, float>(-0.996,-0.087)));
		aimEnter.insert(pair<int,pair<float, float>>(186,pair<float, float>(-0.995,-0.105)));
		aimEnter.insert(pair<int,pair<float, float>>(187,pair<float, float>(-0.993,-0.122)));
		aimEnter.insert(pair<int,pair<float, float>>(188,pair<float, float>(-0.990,-0.139)));
		aimEnter.insert(pair<int,pair<float, float>>(189,pair<float, float>(-0.988,-0.156)));
		aimEnter.insert(pair<int,pair<float, float>>(190,pair<float, float>(-0.985,-0.174)));
		aimEnter.insert(pair<int,pair<float, float>>(191,pair<float, float>(-0.982,-0.191)));
		aimEnter.insert(pair<int,pair<float, float>>(192,pair<float, float>(-0.978,-0.208)));
		aimEnter.insert(pair<int,pair<float, float>>(193,pair<float, float>(-0.974,-0.225)));
		aimEnter.insert(pair<int,pair<float, float>>(194,pair<float, float>(-0.970,-0.242)));
		aimEnter.insert(pair<int,pair<float, float>>(195,pair<float, float>(-0.966,-0.259)));
		aimEnter.insert(pair<int,pair<float, float>>(196,pair<float, float>(-0.961,-0.276)));
		aimEnter.insert(pair<int,pair<float, float>>(197,pair<float, float>(-0.956,-0.292)));
		aimEnter.insert(pair<int,pair<float, float>>(198,pair<float, float>(-0.951,-0.309)));
		aimEnter.insert(pair<int,pair<float, float>>(199,pair<float, float>(-0.946,-0.326)));
		aimEnter.insert(pair<int,pair<float, float>>(200,pair<float, float>(-0.940,-0.342)));
		aimEnter.insert(pair<int,pair<float, float>>(201,pair<float, float>(-0.934,-0.358)));
		aimEnter.insert(pair<int,pair<float, float>>(202,pair<float, float>(-0.927,-0.375)));
		aimEnter.insert(pair<int,pair<float, float>>(203,pair<float, float>(-0.921,-0.391)));
		aimEnter.insert(pair<int,pair<float, float>>(204,pair<float, float>(-0.914,-0.407)));
		aimEnter.insert(pair<int,pair<float, float>>(205,pair<float, float>(-0.906,-0.423)));
		aimEnter.insert(pair<int,pair<float, float>>(206,pair<float, float>(-0.899,-0.438)));
		aimEnter.insert(pair<int,pair<float, float>>(207,pair<float, float>(-0.891,-0.454)));
		aimEnter.insert(pair<int,pair<float, float>>(208,pair<float, float>(-0.883,-0.469)));
		aimEnter.insert(pair<int,pair<float, float>>(209,pair<float, float>(-0.875,-0.485)));
		aimEnter.insert(pair<int,pair<float, float>>(210,pair<float, float>(-0.866,-0.500)));
		aimEnter.insert(pair<int,pair<float, float>>(211,pair<float, float>(-0.857,-0.515)));
		aimEnter.insert(pair<int,pair<float, float>>(212,pair<float, float>(-0.848,-0.530)));
		aimEnter.insert(pair<int,pair<float, float>>(213,pair<float, float>(-0.839,-0.545)));
		aimEnter.insert(pair<int,pair<float, float>>(214,pair<float, float>(-0.829,-0.559)));
		aimEnter.insert(pair<int,pair<float, float>>(215,pair<float, float>(-0.819,-0.574)));
		aimEnter.insert(pair<int,pair<float, float>>(216,pair<float, float>(-0.809,-0.588)));
		aimEnter.insert(pair<int,pair<float, float>>(217,pair<float, float>(-0.799,-0.602)));
		aimEnter.insert(pair<int,pair<float, float>>(218,pair<float, float>(-0.788,-0.616)));
		aimEnter.insert(pair<int,pair<float, float>>(219,pair<float, float>(-0.777,-0.629)));
		aimEnter.insert(pair<int,pair<float, float>>(220,pair<float, float>(-0.766,-0.643)));
		aimEnter.insert(pair<int,pair<float, float>>(221,pair<float, float>(-0.755,-0.656)));
		aimEnter.insert(pair<int,pair<float, float>>(222,pair<float, float>(-0.743,-0.669)));
		aimEnter.insert(pair<int,pair<float, float>>(223,pair<float, float>(-0.731,-0.682)));
		aimEnter.insert(pair<int,pair<float, float>>(224,pair<float, float>(-0.719,-0.695)));
		aimEnter.insert(pair<int,pair<float, float>>(225,pair<float, float>(-0.707,-0.707)));
		aimEnter.insert(pair<int,pair<float, float>>(226,pair<float, float>(-0.695,-0.719)));
		aimEnter.insert(pair<int,pair<float, float>>(227,pair<float, float>(-0.682,-0.731)));
		aimEnter.insert(pair<int,pair<float, float>>(228,pair<float, float>(-0.669,-0.743)));
		aimEnter.insert(pair<int,pair<float, float>>(229,pair<float, float>(-0.656,-0.755)));
		aimEnter.insert(pair<int,pair<float, float>>(230,pair<float, float>(-0.643,-0.766)));
		aimEnter.insert(pair<int,pair<float, float>>(231,pair<float, float>(-0.629,-0.777)));
		aimEnter.insert(pair<int,pair<float, float>>(232,pair<float, float>(-0.616,-0.788)));
		aimEnter.insert(pair<int,pair<float, float>>(233,pair<float, float>(-0.602,-0.799)));
		aimEnter.insert(pair<int,pair<float, float>>(234,pair<float, float>(-0.588,-0.809)));
		aimEnter.insert(pair<int,pair<float, float>>(235,pair<float, float>(-0.574,-0.819)));
		aimEnter.insert(pair<int,pair<float, float>>(236,pair<float, float>(-0.559,-0.829)));
		aimEnter.insert(pair<int,pair<float, float>>(237,pair<float, float>(-0.545,-0.839)));
		aimEnter.insert(pair<int,pair<float, float>>(238,pair<float, float>(-0.530,-0.848)));
		aimEnter.insert(pair<int,pair<float, float>>(239,pair<float, float>(-0.515,-0.857)));
		aimEnter.insert(pair<int,pair<float, float>>(240,pair<float, float>(-0.500,-0.866)));
		aimEnter.insert(pair<int,pair<float, float>>(241,pair<float, float>(-0.485,-0.875)));
		aimEnter.insert(pair<int,pair<float, float>>(242,pair<float, float>(-0.469,-0.883)));
		aimEnter.insert(pair<int,pair<float, float>>(243,pair<float, float>(-0.454,-0.891)));
		aimEnter.insert(pair<int,pair<float, float>>(244,pair<float, float>(-0.438,-0.899)));
		aimEnter.insert(pair<int,pair<float, float>>(245,pair<float, float>(-0.423,-0.906)));
		aimEnter.insert(pair<int,pair<float, float>>(246,pair<float, float>(-0.407,-0.914)));
		aimEnter.insert(pair<int,pair<float, float>>(247,pair<float, float>(-0.391,-0.921)));
		aimEnter.insert(pair<int,pair<float, float>>(248,pair<float, float>(-0.375,-0.927)));
		aimEnter.insert(pair<int,pair<float, float>>(249,pair<float, float>(-0.358,-0.934)));
		aimEnter.insert(pair<int,pair<float, float>>(250,pair<float, float>(-0.342,-0.940)));
		aimEnter.insert(pair<int,pair<float, float>>(251,pair<float, float>(-0.326,-0.946)));
		aimEnter.insert(pair<int,pair<float, float>>(252,pair<float, float>(-0.309,-0.951)));
		aimEnter.insert(pair<int,pair<float, float>>(253,pair<float, float>(-0.292,-0.956)));
		aimEnter.insert(pair<int,pair<float, float>>(254,pair<float, float>(-0.276,-0.961)));
		aimEnter.insert(pair<int,pair<float, float>>(255,pair<float, float>(-0.259,-0.966)));
		aimEnter.insert(pair<int,pair<float, float>>(256,pair<float, float>(-0.242,-0.970)));
		aimEnter.insert(pair<int,pair<float, float>>(257,pair<float, float>(-0.225,-0.974)));
		aimEnter.insert(pair<int,pair<float, float>>(258,pair<float, float>(-0.208,-0.978)));
		aimEnter.insert(pair<int,pair<float, float>>(259,pair<float, float>(-0.191,-0.982)));
		aimEnter.insert(pair<int,pair<float, float>>(260,pair<float, float>(-0.174,-0.985)));
		aimEnter.insert(pair<int,pair<float, float>>(261,pair<float, float>(-0.156,-0.988)));
		aimEnter.insert(pair<int,pair<float, float>>(262,pair<float, float>(-0.139,-0.990)));
		aimEnter.insert(pair<int,pair<float, float>>(263,pair<float, float>(-0.122,-0.993)));
		aimEnter.insert(pair<int,pair<float, float>>(264,pair<float, float>(-0.105,-0.995)));
		aimEnter.insert(pair<int,pair<float, float>>(265,pair<float, float>(-0.087,-0.996)));
		aimEnter.insert(pair<int,pair<float, float>>(266,pair<float, float>(-0.070,-0.998)));
		aimEnter.insert(pair<int,pair<float, float>>(267,pair<float, float>(-0.052,-0.999)));
		aimEnter.insert(pair<int,pair<float, float>>(268,pair<float, float>(-0.035,-0.999)));
		aimEnter.insert(pair<int,pair<float, float>>(269,pair<float, float>(-0.017,-1.000)));
		aimEnter.insert(pair<int,pair<float, float>>(270,pair<float, float>(0.000,-1.000)));
		aimEnter.insert(pair<int,pair<float, float>>(271,pair<float, float>(0.017,-1.000)));
		aimEnter.insert(pair<int,pair<float, float>>(272,pair<float, float>(0.035,-0.999)));
		aimEnter.insert(pair<int,pair<float, float>>(273,pair<float, float>(0.052,-0.999)));
		aimEnter.insert(pair<int,pair<float, float>>(274,pair<float, float>(0.070,-0.998)));
		aimEnter.insert(pair<int,pair<float, float>>(275,pair<float, float>(0.087,-0.996)));
		aimEnter.insert(pair<int,pair<float, float>>(276,pair<float, float>(0.105,-0.995)));
		aimEnter.insert(pair<int,pair<float, float>>(277,pair<float, float>(0.122,-0.993)));
		aimEnter.insert(pair<int,pair<float, float>>(278,pair<float, float>(0.139,-0.990)));
		aimEnter.insert(pair<int,pair<float, float>>(279,pair<float, float>(0.156,-0.988)));
		aimEnter.insert(pair<int,pair<float, float>>(280,pair<float, float>(0.174,-0.985)));
		aimEnter.insert(pair<int,pair<float, float>>(281,pair<float, float>(0.191,-0.982)));
		aimEnter.insert(pair<int,pair<float, float>>(282,pair<float, float>(0.208,-0.978)));
		aimEnter.insert(pair<int,pair<float, float>>(283,pair<float, float>(0.225,-0.974)));
		aimEnter.insert(pair<int,pair<float, float>>(284,pair<float, float>(0.242,-0.970)));
		aimEnter.insert(pair<int,pair<float, float>>(285,pair<float, float>(0.259,-0.966)));
		aimEnter.insert(pair<int,pair<float, float>>(286,pair<float, float>(0.276,-0.961)));
		aimEnter.insert(pair<int,pair<float, float>>(287,pair<float, float>(0.292,-0.956)));
		aimEnter.insert(pair<int,pair<float, float>>(288,pair<float, float>(0.309,-0.951)));
		aimEnter.insert(pair<int,pair<float, float>>(289,pair<float, float>(0.326,-0.946)));
		aimEnter.insert(pair<int,pair<float, float>>(290,pair<float, float>(0.342,-0.940)));
		aimEnter.insert(pair<int,pair<float, float>>(291,pair<float, float>(0.358,-0.934)));
		aimEnter.insert(pair<int,pair<float, float>>(292,pair<float, float>(0.375,-0.927)));
		aimEnter.insert(pair<int,pair<float, float>>(293,pair<float, float>(0.391,-0.921)));
		aimEnter.insert(pair<int,pair<float, float>>(294,pair<float, float>(0.407,-0.914)));
		aimEnter.insert(pair<int,pair<float, float>>(295,pair<float, float>(0.423,-0.906)));
		aimEnter.insert(pair<int,pair<float, float>>(296,pair<float, float>(0.438,-0.899)));
		aimEnter.insert(pair<int,pair<float, float>>(297,pair<float, float>(0.454,-0.891)));
		aimEnter.insert(pair<int,pair<float, float>>(298,pair<float, float>(0.469,-0.883)));
		aimEnter.insert(pair<int,pair<float, float>>(299,pair<float, float>(0.485,-0.875)));
		aimEnter.insert(pair<int,pair<float, float>>(300,pair<float, float>(0.500,-0.866)));
		aimEnter.insert(pair<int,pair<float, float>>(301,pair<float, float>(0.515,-0.857)));
		aimEnter.insert(pair<int,pair<float, float>>(302,pair<float, float>(0.530,-0.848)));
		aimEnter.insert(pair<int,pair<float, float>>(303,pair<float, float>(0.545,-0.839)));
		aimEnter.insert(pair<int,pair<float, float>>(304,pair<float, float>(0.559,-0.829)));
		aimEnter.insert(pair<int,pair<float, float>>(305,pair<float, float>(0.574,-0.819)));
		aimEnter.insert(pair<int,pair<float, float>>(306,pair<float, float>(0.588,-0.809)));
		aimEnter.insert(pair<int,pair<float, float>>(307,pair<float, float>(0.602,-0.799)));
		aimEnter.insert(pair<int,pair<float, float>>(308,pair<float, float>(0.616,-0.788)));
		aimEnter.insert(pair<int,pair<float, float>>(309,pair<float, float>(0.629,-0.777)));
		aimEnter.insert(pair<int,pair<float, float>>(310,pair<float, float>(0.643,-0.766)));
		aimEnter.insert(pair<int,pair<float, float>>(311,pair<float, float>(0.656,-0.755)));
		aimEnter.insert(pair<int,pair<float, float>>(312,pair<float, float>(0.669,-0.743)));
		aimEnter.insert(pair<int,pair<float, float>>(313,pair<float, float>(0.682,-0.731)));
		aimEnter.insert(pair<int,pair<float, float>>(314,pair<float, float>(0.695,-0.719)));
		aimEnter.insert(pair<int,pair<float, float>>(315,pair<float, float>(0.707,-0.707)));
		aimEnter.insert(pair<int,pair<float, float>>(316,pair<float, float>(0.719,-0.695)));
		aimEnter.insert(pair<int,pair<float, float>>(317,pair<float, float>(0.731,-0.682)));
		aimEnter.insert(pair<int,pair<float, float>>(318,pair<float, float>(0.743,-0.669)));
		aimEnter.insert(pair<int,pair<float, float>>(319,pair<float, float>(0.755,-0.656)));
		aimEnter.insert(pair<int,pair<float, float>>(320,pair<float, float>(0.766,-0.643)));
		aimEnter.insert(pair<int,pair<float, float>>(321,pair<float, float>(0.777,-0.629)));
		aimEnter.insert(pair<int,pair<float, float>>(322,pair<float, float>(0.788,-0.616)));
		aimEnter.insert(pair<int,pair<float, float>>(323,pair<float, float>(0.799,-0.602)));
		aimEnter.insert(pair<int,pair<float, float>>(324,pair<float, float>(0.809,-0.588)));
		aimEnter.insert(pair<int,pair<float, float>>(325,pair<float, float>(0.819,-0.574)));
		aimEnter.insert(pair<int,pair<float, float>>(326,pair<float, float>(0.829,-0.559)));
		aimEnter.insert(pair<int,pair<float, float>>(327,pair<float, float>(0.839,-0.545)));
		aimEnter.insert(pair<int,pair<float, float>>(328,pair<float, float>(0.848,-0.530)));
		aimEnter.insert(pair<int,pair<float, float>>(329,pair<float, float>(0.857,-0.515)));
		aimEnter.insert(pair<int,pair<float, float>>(330,pair<float, float>(0.866,-0.500)));
		aimEnter.insert(pair<int,pair<float, float>>(331,pair<float, float>(0.875,-0.485)));
		aimEnter.insert(pair<int,pair<float, float>>(332,pair<float, float>(0.883,-0.469)));
		aimEnter.insert(pair<int,pair<float, float>>(333,pair<float, float>(0.891,-0.454)));
		aimEnter.insert(pair<int,pair<float, float>>(334,pair<float, float>(0.899,-0.438)));
		aimEnter.insert(pair<int,pair<float, float>>(335,pair<float, float>(0.906,-0.423)));
		aimEnter.insert(pair<int,pair<float, float>>(336,pair<float, float>(0.914,-0.407)));
		aimEnter.insert(pair<int,pair<float, float>>(337,pair<float, float>(0.921,-0.391)));
		aimEnter.insert(pair<int,pair<float, float>>(338,pair<float, float>(0.927,-0.375)));
		aimEnter.insert(pair<int,pair<float, float>>(339,pair<float, float>(0.934,-0.358)));
		aimEnter.insert(pair<int,pair<float, float>>(340,pair<float, float>(0.940,-0.342)));
		aimEnter.insert(pair<int,pair<float, float>>(341,pair<float, float>(0.946,-0.326)));
		aimEnter.insert(pair<int,pair<float, float>>(342,pair<float, float>(0.951,-0.309)));
		aimEnter.insert(pair<int,pair<float, float>>(343,pair<float, float>(0.956,-0.292)));
		aimEnter.insert(pair<int,pair<float, float>>(344,pair<float, float>(0.961,-0.276)));
		aimEnter.insert(pair<int,pair<float, float>>(345,pair<float, float>(0.966,-0.259)));
		aimEnter.insert(pair<int,pair<float, float>>(346,pair<float, float>(0.970,-0.242)));
		aimEnter.insert(pair<int,pair<float, float>>(347,pair<float, float>(0.974,-0.225)));
		aimEnter.insert(pair<int,pair<float, float>>(348,pair<float, float>(0.978,-0.208)));
		aimEnter.insert(pair<int,pair<float, float>>(349,pair<float, float>(0.982,-0.191)));
		aimEnter.insert(pair<int,pair<float, float>>(350,pair<float, float>(0.985,-0.174)));
		aimEnter.insert(pair<int,pair<float, float>>(351,pair<float, float>(0.988,-0.156)));
		aimEnter.insert(pair<int,pair<float, float>>(352,pair<float, float>(0.990,-0.139)));
		aimEnter.insert(pair<int,pair<float, float>>(353,pair<float, float>(0.993,-0.122)));
		aimEnter.insert(pair<int,pair<float, float>>(354,pair<float, float>(0.995,-0.105)));
		aimEnter.insert(pair<int,pair<float, float>>(355,pair<float, float>(0.996,-0.087)));
		aimEnter.insert(pair<int,pair<float, float>>(356,pair<float, float>(0.998,-0.070)));
		aimEnter.insert(pair<int,pair<float, float>>(357,pair<float, float>(0.999,-0.052)));
		aimEnter.insert(pair<int,pair<float, float>>(358,pair<float, float>(0.999,-0.035)));
		aimEnter.insert(pair<int,pair<float, float>>(359,pair<float, float>(1.000,-0.017)));
		aimEnter.insert(pair<int,pair<float, float>>(360,pair<float, float>(1.000,0.000)));
	}
}