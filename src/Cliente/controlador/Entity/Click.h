#ifndef __CLICK__
#define __CLICK__
#include <list>
#include "..\Contracts\OnClickListener.h"
#include "ClickEvent.h"
#include "..\Contracts\Notifiable.h"

using namespace std;


class Click : public Notifiable{
	public:
		static Click* getInstance();
		void add(OnClickListener * obj);
		void remuve(OnClickListener * obj);
		void notify();
		void setEvent(int x, int y);
		void removeAll();

	private:
		Click(void);
		~Click(void);
		static Click* click;
		list<OnClickListener*> objects;
		int x, y;
		bool isRegistered(OnClickListener * obj);
};

#endif