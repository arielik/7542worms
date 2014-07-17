#pragma once

#ifndef __PLAYER_PROGRESS_VIEW_H__
#define __PLAYER_PROGRESS_VIEW_H__
#include "TextureManager.h"
#include "View.h"
#include "TextView.h"
#include "../../utils/Constantes/Colors.h"
class PlayerProgressView: public View
{
private:

	std::map<Player,int> * refPlayersLife;

	std::map<Player,std::pair<StateConn,int>> * refPlayersPlaying;

	TextView labelUser;

public:
	PlayerProgressView(std::map<Player,int> * refPlayersLife, std::map<Player,std::pair<StateConn,int>> * refPlayersPlaying);

	void clean();
	
	void update();

	void draw(SDLScreen & screen);

	~PlayerProgressView(void);

	int calcWidth(int life);

};

#endif /** __PLAYER_PROGRESS_VIEW_H__ **/