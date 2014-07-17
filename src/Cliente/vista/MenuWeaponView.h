#ifndef __MENU_WEAPON_VIEW__
#define __MENU_WEAPON_VIEW__

#include "View.h"
#include "Weapon.h"
#include <map>

using namespace std;

class MenuWeaponView : public View{

public:
	MenuWeaponView(int x, int y);
	~MenuWeaponView();
	void buildWeapon();
	void actionMenu();
	void offMenu();
	void draw(SDLScreen & screen);
	void allowWeapon(list<WeaponId> items);
	bool hasClickedMenu(SDL_Point clickPoint);
	bool hasClickedWeapon(SDL_Point clickPoint);
	Weapon* retrieveWeaponClicked(SDL_Point clickPoint);
	Weapon* findWeaponById(int idWeapon);
private:
	map<WeaponId, Weapon*> mapa;
	Weapon* menu;
};


#endif
