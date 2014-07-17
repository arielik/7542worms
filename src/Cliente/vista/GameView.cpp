#include "GameView.h"


GameView::GameView(int x, int y, int width, int height)
								: ViewGroup(x, y,width, height)
{
	eart = NULL; 
	sky = NULL;
	water = NULL;
}


GameView::~GameView(void)
{

}

void GameView::putFigure(int id, FigureView* figure)
{
	figures[id] = figure;
	this->add(figure);
}

void GameView::setWormContainer(WormViewGroup * wormViewGroup)
{
	this->wormViewGroup = wormViewGroup;
	this->add(wormViewGroup);
}

void GameView::setProjectileContainer(ProjectileViewGroup * projectileViewGroup)
{
	this->projectileViewGroup = projectileViewGroup;
	this->add(projectileViewGroup);
}

void GameView::setExplosionContainer(ExplosionViewGroup * explosionViewGroup) {
	this->explosionViewGroup = explosionViewGroup;
	this->add(explosionViewGroup);
}

void GameView::setEart(EartView* eart)
{
	this->eart = eart;
	this->add(eart);
	this->waterImg->initialize(5,0.5, true);
}
void GameView::setSky(SkyView* sky)
{
	this->sky = sky;
	this->add(sky);
}
void GameView::setWater(WaterView* water)
{
	this->water = water;
	this->add(water);
}

void GameView::setTerrain(TerrainView* terrain) 
{
	this->terrain = terrain;
	this->add(water);
}

void GameView::allowPower(){
	this->powerView->allow();
}

void GameView::denyPower(){
	this->powerView->deny();
}

void GameView::setStateBar(StateBarView* stateBar)
{
	this->stateBar = stateBar;
	this->add(stateBar);
}

void GameView::setMenuWeapon(MenuWeaponView* menuWeapon)
{
	this->menuWeapon = menuWeapon;
	this->add(menuWeapon);
}

void GameView::setWaterImg(WaterViewImg* waterImg){
	this->waterImg = waterImg;
	this->add(waterImg);
}
void GameView::setWaterSurfImg(std::list<WaterViewImg*> l){
	std::list<WaterViewImg*>::iterator it;
	for(it = l.begin(); it != l.end(); it++){
		this->add(*it);
	}

}

FigureView* GameView::findFigureById(int idElement)
	
{
	if (figures.find(idElement) != figures.end())
	{
		return figures[idElement];
	} 
	else 
	{
		std::stringstream msg;
		msg<<"GameView: not found figure view by id: "<<idElement;
		throw GameException(msg.str());
	}
}
ProjectileView* GameView::findProjectileById(int idElement)
{
	return this->projectileViewGroup->findById(idElement);
}
WormView* GameView::findWormById(int idElement)
{
	return this->wormViewGroup->findById(idElement);
}

void GameView::getDestroyEart(int x, int y, int radio)
{
	this->eart->drawExplotion(x, y, radio);
}

void GameView::actionMenu(){
	this->menuWeapon->actionMenu();
}

void GameView::offMenu(){
	this->menuWeapon->offMenu();
}

bool GameView::hasClickedMenu(SDL_Point clickPoint){
	return this->menuWeapon->hasClickedMenu(clickPoint);
}

bool GameView::hasClickedWeapon(SDL_Point clickPoint){
	return this->menuWeapon->hasClickedWeapon(clickPoint);
}

Weapon* GameView::retrieveWeaponClicked(SDL_Point clickPoint){
	return this->menuWeapon->retrieveWeaponClicked(clickPoint);
}

Weapon* GameView::findWeaponById(int idWeapon){
	return this->menuWeapon->findWeaponById(idWeapon);
}

void GameView::freeProjectileView(int id) {
	try {
		ProjectileView* aView = this->projectileViewGroup->removeItem(id);
		delete aView;
	} catch (GameException & e){
		Log::e("Estoy intentando elimiar un projectile en la vista que no exite");
	}
}

void GameView::freeWormView(int id) {
	try {
		WormView* aView = this->wormViewGroup->removeItem(id);
		delete aView;
	} catch (GameException & e){
		Log::e("Estoy intentando elimiar un projectile en la vista que no exite");
	}
}



void GameView::printTimer(int second){
	this->timerView->printTimer(second);
}

void GameView::setPlayerProgressView(PlayerProgressView * pProgressView){
	this->pProgressView = pProgressView;
	this->add(pProgressView);
}

void GameView::setTimerView(TimerView * timerView)
{
	this->timerView = timerView;
	this->add(timerView);
}

void GameView::setPowerView(PowerView * powerView)
{
	this->powerView = powerView;
	this->add(powerView);
}

