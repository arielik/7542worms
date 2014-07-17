#ifndef __OVER__
#define __OVER__
#include <list>
#include "..\Contracts\OnScrollListener.h"
#include "ScrollEvent.h"
#include "..\Contracts\Notifiable.h"

using namespace std;


class Over : public Notifiable{
	public:
		static Over* getInstance();
		void add(OnScrollListener * obj);
		void remuve(OnScrollListener * obj);
		void notify();
		void setEvent(int x, int y);
		void removeAll();

	private:
		Over(void);
		~Over(void);
		static Over* over;
		list<OnScrollListener*> objects;
		int x, y;
		bool isRegistered(OnScrollListener * obj);
};

#endif