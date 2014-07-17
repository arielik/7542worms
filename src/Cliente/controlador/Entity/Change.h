#ifndef __CHANGE__
#define __CHANGE__
#include <list>
#include "..\Contracts\OnChangeListener.h"
#include "ChangeEvent.h"
#include "..\Contracts\Notifiable.h"

using namespace std;


class Change : public Notifiable{
	public:
		static Change* getInstance();
		void add(OnChangeListener * obj);
		void remuve(OnChangeListener * obj);
		void notify();
		void setEvent(int x, int y);
		void setFactor(int factor);
		void setAimMove(AimMove aimMove);
		void setStateBar(bool stateBar);
		void setCoordenate(bool coordenate);
		void setAimEnter(bool aimEnter);
		bool newEvent();
		bool isStateBar();
		bool isCoordenate();
		bool isAimEnter();
		void removeAll();

	private:
		Change(void);
		~Change(void);
		static Change* change;
		list<OnChangeListener*> objects;
		int x, y;
		int xp, yp;
		int factor;
		bool stateBar,
			 coordenate,
			 aimEnter;
		AimMove aimMove;
		bool isRegistered(OnChangeListener * obj);
};

#endif