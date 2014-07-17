#include "MenuWeaponView.h"
#include "TextureManager.h"
#include "..\controlador\Entity\Shape.h"
#include <list>

#define X_MENU 400
#define Y_MENU 50
#define WIDTH_WEAPON  32
#define HEIGHT_WEAPON 32
#define WIDTH_MENU_WEAPON 150
#define HEIGHT_MENU_WEAPON 70

MenuWeaponView::MenuWeaponView(int x, int y)
	:View(x,y){

}


MenuWeaponView::~MenuWeaponView(){

}

void MenuWeaponView::offMenu(){
	if(menu->findWeapon("MenuWeapon")){
		menu->removeWeapon("MenuWeapon");
	}
}

void MenuWeaponView::actionMenu(){
	if(menu->findWeapon("MenuWeapon")){
		menu->removeWeapon("MenuWeapon");
	}
	else{
		menu->setWeapon("MenuWeapon");
	}
}

void MenuWeaponView::draw(SDLScreen & screen){
	
	if(menu->findWeapon("MenuWeapon")){
		menu->draw(screen);
		map<WeaponId, Weapon*>::iterator it;
		for(it = mapa.begin(); it != mapa.end(); it++){
			it->second->draw(screen);
		}
	}
	else{

	}


}


void MenuWeaponView::allowWeapon(list<WeaponId> items){
	list<WeaponId>::iterator it;
	map<WeaponId, Weapon*>::iterator it2;

	for(it = items.begin();
		it != items.end();
		it++){
		it2 = mapa.find((*it));
		if(it2 != mapa.end()){
			it2->second->allow();
		}
	}

}


bool MenuWeaponView::hasClickedMenu(SDL_Point clickPoint){
	bool result = false;
	if(menu->findWeapon("MenuWeapon")
	&& (menu->hasClickedMenu(clickPoint))){
		result = true;
	}
	return result;
}

bool MenuWeaponView::hasClickedWeapon(SDL_Point clickPoint){
	bool result = false;
	if(menu->findWeapon("MenuWeapon")){
		map<WeaponId, Weapon*>::iterator it;
		for(it = mapa.begin(); it != mapa.end(); it++){
			if(it->second->hasClickedMenu(clickPoint)){
				result = true;
				break;
			}
		}
	}
	return result;
}


Weapon* MenuWeaponView::retrieveWeaponClicked(SDL_Point clickPoint){
	Weapon* result = NULL;
	if(menu->findWeapon("MenuWeapon")){
		map<WeaponId, Weapon*>::iterator it;
		for(it = mapa.begin(); it != mapa.end(); it++){
			if(it->second->hasClickedMenu(clickPoint)){
				result = it->second;
				break;
			}
		}
	}
	return result;
}

Weapon* MenuWeaponView::findWeaponById(int idWeapon){
	Weapon* result = NULL;
	WeaponId key = (WeaponId) idWeapon;
	map<WeaponId, Weapon*>::iterator it;
	it = mapa.find(key);
	if(it != mapa.end()){
		result = it->second;
	}
	return result;
}


void MenuWeaponView::buildWeapon(){
	int x, y,
		widthScreen, heightScreen;
	Shape *shape = NULL;
	list<string> lweapons;
	Weapon * weapon;

	widthScreen = TextureManager::Instance().getScreenWidth();
	heightScreen = TextureManager::Instance().getScreenHeight();


	x = widthScreen - WIDTH_MENU_WEAPON;
	y = HEIGHT_MENU_WEAPON;

	menu = new Weapon(NO_WEAPON,Shape(x,y,WIDTH_MENU_WEAPON,HEIGHT_MENU_WEAPON), lweapons, "");

	x += 1;	y += 2;
	lweapons.clear();
	lweapons.push_back("bazooka.1.2");
	weapon = new Weapon(BAZOOKA, Shape(x, y, WIDTH_WEAPON, HEIGHT_WEAPON), lweapons, "bazooka.1.1");
	mapa.insert(pair<WeaponId, Weapon*>(BAZOOKA,weapon));

	x += WIDTH_WEAPON - 3;
	lweapons.clear();
	lweapons.push_back("grenade.1.2");
	weapon = new Weapon(GRENADE, Shape(x, y, WIDTH_WEAPON, HEIGHT_WEAPON), lweapons, "grenade.1.1");
	mapa.insert(pair<WeaponId, Weapon*>(GRENADE,weapon));

	x += WIDTH_WEAPON - 3;
	lweapons.clear();
	lweapons.push_back("hgrenade.1.2");
	weapon = new Weapon(HOLY, Shape(x, y, WIDTH_WEAPON, HEIGHT_WEAPON), lweapons, "hgrenade.1.1");
	mapa.insert(pair<WeaponId, Weapon*>(HOLY,weapon));

	x += WIDTH_WEAPON - 3;
	lweapons.clear();
	lweapons.push_back("donkey.1.2");
	weapon = new Weapon(BURRO, Shape(x, y, WIDTH_WEAPON, HEIGHT_WEAPON), lweapons, "donkey.1.1");
	mapa.insert(pair<WeaponId, Weapon*>(BURRO,weapon));

	x += WIDTH_WEAPON - 3;
	lweapons.clear();
	lweapons.push_back("dynamite.1.2");
	weapon = new Weapon(DYNAMITE, Shape(x, y, WIDTH_WEAPON, HEIGHT_WEAPON), lweapons, "dynamite.1.1");
	mapa.insert(pair<WeaponId, Weapon*>(DYNAMITE,weapon));

	x  = widthScreen - WIDTH_MENU_WEAPON + 1;
	y  += HEIGHT_WEAPON;
	lweapons.clear();
	lweapons.push_back("airstrke.1.2");
	weapon = new Weapon(AIRATTACK, Shape(x, y, WIDTH_WEAPON, HEIGHT_WEAPON), lweapons, "airstrke.1.1");
	mapa.insert(pair<WeaponId, Weapon*>(AIRATTACK,weapon));

	x += WIDTH_WEAPON - 2;
	lweapons.clear();
	lweapons.push_back("banana.1.2");
	weapon = new Weapon(BANANA, Shape(x, y, WIDTH_WEAPON, HEIGHT_WEAPON), lweapons, "banana.1.1");
	mapa.insert(pair<WeaponId, Weapon*>(BANANA,weapon));

	x += WIDTH_WEAPON - 3;
	lweapons.clear();
	lweapons.push_back("hmissile.1.2");
	weapon = new Weapon(HMISSILE, Shape(x, y, WIDTH_WEAPON, HEIGHT_WEAPON), lweapons, "hmissile.1.1");
	mapa.insert(pair<WeaponId, Weapon*>(HMISSILE,weapon));

	x += WIDTH_WEAPON - 3;
	y = y - 5;
	lweapons.clear();
	lweapons.push_back("sheep.1.2");
	weapon = new Weapon(SHEEP, Shape(x, y, WIDTH_WEAPON, HEIGHT_WEAPON), lweapons, "sheep.1.1");
	mapa.insert(pair<WeaponId, Weapon*>(SHEEP,weapon));

	x += WIDTH_WEAPON - 3;
	y += 5;
	lweapons.clear();
	lweapons.push_back("suicide.1.2");
	weapon = new Weapon(SUICIDE, Shape(x, y, WIDTH_WEAPON, HEIGHT_WEAPON), lweapons, "suicide.1.1");
	mapa.insert(pair<WeaponId, Weapon*>(SUICIDE,weapon));

}

