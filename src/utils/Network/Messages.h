#ifndef MESSAGES_H_
#define MESSAGES_H_
#include <cstdint>


enum Messages {
	INIT=0,
	LOGIN,
	UPDATE,
	CONF,
	REJECT,
	KEEPALIVE,
	DISCONNECT,
	PLAYER_UPDATE,  // Actualiza el estado del jugador
	TURN_CHANGE,
	ALREADY_EXIST_USER,
	LOGIN_OK,
	LOGOUT,
	MAP_UPDATE,		// Actualiza mapa por explosiones 
	LIFE_UPDATE,	// Actualiza vida de cada jugador
	GAME_UPDATE,	//Indica quien gano
	REINIT_SRV,
	TIME_UPDATE
};


#endif 
