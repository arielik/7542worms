#ifndef __ACTIONEVENT__
#define __ACTIONEVENT__

enum ActionKey{NONE, SHOOT, MENU};
class ActionEvent{
	public:
		ActionEvent(void);
		~ActionEvent(void);
		ActionKey action;
		int xAim, yAim, factor;
};

#endif
