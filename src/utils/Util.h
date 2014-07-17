#pragma once

#ifndef _UTIL_H_
#define _UTIL_H_

#include "ParserYaml.h"
#include <map>
#include <stdlib.h>
#include <SDL.h>

typedef std::string Player;

#define DYNAMITE_TIMEOUT 5
#define GRENADE_TIMEOUT 3

enum StateConn {CONNECTED, DISCONNECTED, RECONNECTED, WAITING_TURN};
enum GameState {STARTED, WAITING_PLAYERS, OVER, WIN};
enum UserDataPhysics { NO_UD=9, UD_TERRAIN=2, UD_WATER=0, UD_WORMS=3, UD_MISSIL=4 };

/* Explosion radius */
#define EXPLODE_RSMALL 2
#define EXPLODE_RMEDIUM 5
#define EXPLODE_RLARGE 7
#define EXPLODE_RGIANT 10

/* Damage of Weapons */
#define DAMAGE_GRENADE 25
#define DAMAGE_DYNAMITE 40
#define DAMAGE_HOLY 80
#define DAMAGE_HMISSILE 40
#define DAMAGE_BAZOOKA 23
#define DAMAGE_BURRO 33
#define DAMAGE_SUICIDE 23

#define BURRO_REPEAT 4

typedef enum{
	ARGENTINA = 0,
	BRASIL,
	ALEMANIA,
	ESPANIA
} TeamColors;


typedef enum{
	NO_WEAPON=0,
	BAZOOKA=2,
	GRENADE=4,
	HOLY=12,
	BURRO=7,
	AIRATTACK=3,
	DYNAMITE=5,
	HMISSILE=15,
	BANANA=16,
	SUICIDE=17,
	SHEEP=18,
	BANANITA=19
} WeaponId;


typedef enum{
	NEW_PLAYER=0,
	EXISTING_PLAYER,
	PLAYER_NOT_ALLOWED,
	PLAYER_ALLOWED
} PlayerAccounting;



typedef enum{
	MOVE_RIGHT=0,
	MOVE_LEFT,
	JUMP,
	JUMP_LEFT,
	JUMP_RIGHT,
	INIT_PLACEMENT,
	MOVE_STOP,
	DEAD,
	WITHOUT_WEAPON,			/* DEPRECATED */
	WITH_WEAPON,			/* DEPRECATED */
	WITH_WEAPON_LEFT,		/* Apuntando hacia la izquierda . Nestor: lo resuelvo con move and id weapon. A deprecar*/
	WITH_WEAPON_RIGHT,		/* Apuntando hacia la derecha. Nestor: lo resuelvo con move and id weapon. A deprecar */
	DO_SHOOT,				/* Disparo */
	MISSIL_FLYING,
	MISSIL_FLYING_LEFT,
	MISSIL_FLYING_RIGHT,
	NOT_CONNECTED,
	NOT_CONNECTED_LEFT,
	NOT_CONNECTED_RIGHT,
	MOVELESS,
	MOVELESS_RIGHT,
	MOVELESS_LEFT,
	CREATE_MISSIL,
	YOUR_TURN,
	TURN_OVER,
	EXPLOSION,				/* X e Y tienen el radio de la explosion en este caso */
	EXPLOSION_PARTIAL,				/* X e Y tienen el radio de la explosion en este caso */
	WORM_DROWNED,
	MISSIL_DELETED
} Movement;


typedef enum{
	PLAYING_TURN=0,
	WAITING_FOR_TURN
} Turn;

typedef enum{
	D_LEFT,
	D_RIGHT
} tDirection;





//If action is WITH_WEAPON then X and Y means angle of weapon.
// - Dynamite X,Y drops at worm position.
// - Air Attack X,Y means center of where the air attack is going to be dropped

typedef struct {
		int wormid;			// Worm identifier, unique
		Movement action;	// der, izq, salt
		int life;			// Worm health
		int weaponid;		// Worm Weapon elected
		float x;			// X coord
		float y;			// Y coord
		char level[15];		// YAML level (filename), path must be specified

} Playable;


typedef struct Explosion{
	float x;
	float y;
	int radio;	/* El arma define el radio */

	Explosion(const Explosion & aExplosion):
	x(aExplosion.x), y(aExplosion.y), radio(aExplosion.radio){}

	Explosion(float ex, float ey, int eradio){
		x = ex;
		y = ey;
		radio = eradio;
	}

	Explosion(){
		x = 0;
		y = 0;
		radio = 0;
	}


	~Explosion(){}

} Explosion;




struct s_point{
	int x;
	int y;
};
typedef struct s_point tPoint;

struct s_pointf{
	float x;
	float y;
};
typedef struct s_pointf tPointf;




class Util
{
public:
	Util(void);
	~Util(void);


	/**
	* Valid int
	* @param number a string int
	* @return true if str has a integer. 
	*/
	static bool esUnsInt(std::string str);

	/**
	* Convert std::string to int
	* @param number a string int
	* @return int 
	*/
	static int string2int(std::string number);


	/**
	* @DEPRECATE !!!!!!!!!!!!!!!!!!!!!!!!!
	* Get the scale factor in both axis x and y
	* @return std::pair<float,float> a pair of scale factor
	*/
	static std::pair<float,float> getTransformFromU2PX();


	/**
	* Convert std::string to float
	* @param number a string float
	* @return float
	*/
	static float string2float(std::string number);

	/**
	* Convert std::string witch value could be "no" or "si" to bool type
	* @param  a string value "si" or "no"
	* @return true if sino has a "si"
	*/
	static bool string2bool(std::string sino);


	/**
	* Convert std::string witch value could be "no" or "si" to bool type
	* @param  a string value "si" or "no"
	* @return true if sino has a "si"
	*/
	static std::string int2string(int number);
	


	/**
	* * @DEPREATE. USAR EL DE TEXTURE_MANAGER
	* Convert a coordinate x y to coordinate in SDL system reference
	* @param x Value of axis x in domain
	* @param y Value of axis y in domain
	* @return aPoint in SLD system reference
	*/
	static tPoint convertPointUL2PXSDL(float x, float y);

	/**
	* Property loader
	* @param file
	* @return map that contains the properties retrived from file
	*/
	static std::map<std::string, std::string> Util::loadProperteries(std::string str);



	static int getRandom(int min, int max);

	static std::string actionString(Movement action);

	static void clean(Playable & p);

	static SDL_Color geColorTeam(TeamColors teamColor);
};



#endif