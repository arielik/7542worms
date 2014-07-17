#pragma once
#include "../utils/Network/Socket.h"
#include "../utils/Network/Messages.h"
#include "../utils/Network/Thread.h"
#include "../utils/Network/Condition.h"
#include "../utils/Util.h"
#include "../utils/Log.h"
#include <string>
#include <iostream>
#include <ctime>
#include <string>
#include <vector>
#include <list>
#include <queue>
/**
* Do all operation to server
*/
class Updater
{
private:
	std::string pl;

	// Only references 
	Socket* input;
	Socket* output;

	/** Obejtos para sincronismo entre modelo y red*/
	Mutex* m;
	Mutex* n;
	Condition* somethingToTell;
	std::vector<Playable>* localChanges;

public:
	Updater(Socket* input, 
			Socket* output,
			Mutex* m,
			Mutex* n,
			Condition* somethingToTell,
			std::vector<Playable>* localChanges);

	~Updater(void);

	void setPlayerId(std::string pl) {this->pl = pl;}

	/** Realiza el login contra el servidor*/
	bool doLogin();

	/** Realiza el login contra el servidor*/
	void doLogout();

	void doStopWorm(int idWorm);

	void doSelectWapon(int wormIdSelected, int idWeapon, tDirection direction);

	void doUnselectWapon(int wormId, int idWeapon, tDirection direction);

	/** Recupera el level yaml del servidor*/
	void retrieveLevel();

	void addLocalMovementFromView(Playable p);

	/** x y cross head*/
	void doShoot(int wormId, int idWeapon, float x_aim, float y_aim, int factor);

	void notify(int wormId, Movement mov, int weaponId);

};

