#include "WaitActivity.h"


WaitActivity::WaitActivity(SDLScreen & screen):Activity(screen)
{
	waitView = new WaitView("waitting","gameover","winner","alert");
	waitView->setStateWait();
	ViewGroup* viewGroup = new ViewGroup(0, 0, screen.getWidth(), screen.getHeight());
	viewGroup->add(waitView);
	this->setContentView(viewGroup);
}

WaitActivity::~WaitActivity(void)
{
	delete this->aView;
}

void WaitActivity::stop()
{
}

void WaitActivity::clear()
{
}

void WaitActivity::update()
{
	waitView->update();
}

void WaitActivity::setMessageView(std::string msg)
{
	waitView->setMessage(msg);
}

void WaitActivity::showMessageError(std::string msg)
{
	waitView->setMessage(msg);
}

void WaitActivity::showMessageInfo(std::string msg)
{
	waitView->setMessage(msg);
}

void WaitActivity::showGameOver()
{
	waitView->setStateGameOver();
}
void WaitActivity::showWinner()
{
	waitView->setStateWinner();
}
void WaitActivity::showAlert()
{
	waitView->setStateAlert();
}
void WaitActivity::showWaitting()
{
	waitView->setStateWait();
}

