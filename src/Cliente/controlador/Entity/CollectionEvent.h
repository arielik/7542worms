#ifndef __COLLECTION_EVENT__
#define __COLLECTION_EVENT__

#include <map>
#include "../Contracts/Notifiable.h"

using namespace std;

class CollectionEvent{
	public:
		CollectionEvent(void);
		~CollectionEvent(void);
		void add(Notifiable* obj);
		void clear();
		void notify();
	private:
		map<Notifiable*, int> objects;
};

#endif