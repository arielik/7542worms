#ifndef __ZOOM__
#define __ZOOM__
#include <list>
#include "../Contracts/OnZoomListener.h"
#include "ZoomEvent.h"
#include "../Contracts/Notifiable.h"

using namespace std;


class Zoom : public Notifiable{
	public:
		static Zoom* getInstance();
		void add(OnZoomListener* obj);
		void remuve(OnZoomListener* obj);
		void notify();
		void setEvent(int y);
		void removeAll();

	private:
		Zoom(void);
		~Zoom(void);
		static Zoom* zoom;
		list<OnZoomListener*> objects;
		int y;
		bool isRegistered(OnZoomListener * obj);
};

#endif
