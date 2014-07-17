#include "PlayerProgressView.h"


PlayerProgressView::PlayerProgressView(std::map<Player,int> * playersLife, std::map<Player,std::pair<StateConn,int>> * playersPlaying)
	: View(0, 0), refPlayersLife(playersLife), refPlayersPlaying(playersPlaying)
{

}


PlayerProgressView::~PlayerProgressView(void)
{
}

void PlayerProgressView::update()
{

}


void PlayerProgressView::clean()
{

}

void PlayerProgressView::draw(SDLScreen & screen){
	
		int margin = 5;
		int countOfPlayer = 5;
		int heightBarProgress = 15;
		SDL_Rect rect;
		rect.x = this->getX();
		rect.y = screen.getHeight() - countOfPlayer * heightBarProgress;
		rect.w = 0;
		rect.h = heightBarProgress - margin;

		int x = rect.x - 100;

		std::map<Player, std::pair < StateConn, int > >::iterator it;

		int indexPlayer = 0;
		for (it = this->refPlayersPlaying->begin(); it != this->refPlayersPlaying->end(); ++it)
		{
			Player aPlayer = it->first;
			std::pair<StateConn,int> value = it->second;

			rect.w = calcWidth((*this->refPlayersLife)[aPlayer]);
			rect.y = screen.getHeight() - (countOfPlayer - indexPlayer) * heightBarProgress; // apilar barras
			SDL_Rect rectBar = rect;
			rectBar.x = rectBar.x + 80;
			SDL_Color color = Util::geColorTeam((TeamColors)value.second);
			TextureManager::Instance().drawFillRect(screen.getRenderer(), rectBar, color.r, color.g, color.b, color.a);
			TextureManager::Instance().drawRect(screen.getRenderer(), rectBar, 0, 0, 0, 255);
			
			indexPlayer++;

			labelUser.setText((std::string)aPlayer, Util::geColorTeam((TeamColors)value.second));
			labelUser.draw(screen.getRenderer(), rect.x, rect.y - 5);
		}
}


int PlayerProgressView::calcWidth(int life) 
{
	int w=0;
	w = (int)((float)life / 4);

	if (w<0) {
		w = 0;
	}
	return  w;
}

