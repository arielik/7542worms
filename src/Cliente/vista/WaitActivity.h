#ifndef __WAIT_ACTIVITY_H_
#define __WAIT_ACTIVITY_H_
#include "Activity.h"
#include "WaitView.h"
#include "TextView.h"
#include "ViewGroup.h"

#include "TextureManager.h"

#include "../../utils/Util.h"


class WaitActivity : public Activity
{
private:

	WaitView * waitView;

public:

	WaitActivity(SDLScreen & screen);

	~WaitActivity(void);

	void stop();

	void clear();

	void update();

	void setMessageView(std::string msg);

	void showMessageError(std::string msg);

	void showMessageInfo(std::string msg);

	void showGameOver();	
	void showWinner();
	void showAlert();
	void showWaitting();
};

#endif /* defined(__WAIT_ACTIVITY_H_) */

