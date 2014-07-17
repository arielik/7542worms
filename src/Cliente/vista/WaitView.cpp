#include "WaitView.h"


WaitView::WaitView(std::string imageWaitId, std::string imageGameOverId, std::string imageWinnerId, std::string imageAlertId)
				: View(0, 0), imageWaitId(imageWaitId), imageGameOverId(imageGameOverId), imageWinnerId(imageWinnerId), imageAlertId(imageAlertId), state(WAIT_VIEW_WAIT)
{
}


WaitView::~WaitView(void)
{
}


void WaitView::clean()
{

}
	
void WaitView::update() 
{
	
	if (this->state == WAIT_VIEW_WAIT)
	{
		imageId = imageWaitId;
	}
	else if (this->state == WAIT_VIEW_GAMEOVER) 
	{
		imageId = imageGameOverId;
	}
	else if (this->state == WAIT_VIEW_WINNER) 
	{
		imageId = imageWinnerId;
	}
	else if (this->state == WAIT_VIEW_ALERT) 
	{
		imageId = imageAlertId;
	}
	else
	{
		imageId = imageAlertId;
	}
}

void WaitView::draw(SDLScreen & screen)
{
	TextureManager::Instance().drawBackground(imageId.c_str(),
								screen.getRenderer());

	if (this->state == WAIT_VIEW_ALERT) 
	{
		this->text.draw(screen.getRenderer(), 250,300, 0, 0);
	}

}

void WaitView::setMessage(std::string msg)
{
	SDL_Color color;
	color.a = 0xFF;
	color.r = 0xFF;
	color.g = 0xFF;
	color.b = 0xFF;
	this->text.setText(msg, color);
}
