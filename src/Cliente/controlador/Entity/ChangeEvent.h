#ifndef __CHANGEEVENT__
#define __CHANGEEVENT__

enum AimMove {M_SHEDULE, M_ANTICLOCK, M_LEFT, M_RIGHT};

class ChangeEvent{
	public:
		ChangeEvent(void);
		~ChangeEvent(void);
		int x, y;
		int factor;
		bool stateBar,
			 coordenate,
			 aimEnter;
		AimMove aimMove;
		void setFactor(int factor);
		void setStateBar(bool stateBar);
		void setAimEnter(bool aimEnter);
		void setCoordenate(bool coordenate);
		bool isStateBar();
		bool isAimEnter();
		bool isCoordenate();
};

#endif
