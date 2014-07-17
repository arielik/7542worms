#pragma once

#ifndef __ELEM_VIEW_GROUP_H__
#define __ELEM_VIEW_GROUP_H__
#include <list>
#include <map>
#include "View.h"
template <class T>
class ElemViewGroup : public View
{
private:
	std::map<int, T> mapElem;

	std::list<T> views;

public:

	ElemViewGroup(int x, int y);


	/**
	* Find a figure view by id
	* @return aFigureView 
	*/
	T findById(int idElement);


	/**
	* Add a view
	*/
	void add(T aView);

	/**
	* Clean every view
	*/
	void clean();

	
	/**
	* Update every wormView
	*/
	void update();


	/**
	* Draw each view
	*/
	void draw(SDLScreen & screen);

	/**
	* Just remove a item
	*/
	T removeItem(int id);

	~ElemViewGroup(void);
};



template <class T>
ElemViewGroup<T>::ElemViewGroup(int x, int y): View(x, y)
{

}


template <class T>
T ElemViewGroup<T>::findById(int idElement)
{
	if (mapElem.find(idElement) != mapElem.end())
	{
		return mapElem[idElement];
	} 
	else 
	{
		std::stringstream msg;
		msg<<"WormView: not found ElemView by id: "<<idElement;
		throw GameException(msg.str());
	}
}

template <class T>
T ElemViewGroup<T>::removeItem(int idElement)
{
	if (mapElem.find(idElement) != mapElem.end())
	{
		T aItem = mapElem[idElement];
		mapElem.erase(idElement);
		this->views.remove(aItem);
		return aItem;
	} 
	else 
	{
		std::stringstream msg;
		msg<<"WormView: not found ElemView by id: "<<idElement;
		throw GameException(msg.str());
	}
}

template <class T>
void ElemViewGroup<T>::add(T aView)
{
	this->views.push_back(aView);
	this->mapElem[aView->getId()]=aView;
}


template <class T>
void ElemViewGroup<T>::clean()
{
	std::list<T>::iterator it;
	for (it = this->views.begin(); it != this->views.end(); ++it) {
		(*it)->clean();
	}
}
	

template <class T>
void ElemViewGroup<T>::update()
{
	std::list<T>::iterator it;
	for (it = this->views.begin(); it != this->views.end(); ++it) {
		(*it)->update();
	}
}


template <class T>
void ElemViewGroup<T>::draw(SDLScreen & screen)
{
	std::list<T>::iterator it;
	for (it = this->views.begin(); it != this->views.end(); ++it) {
		(*it)->draw(screen);
	}
}

template <class T>
ElemViewGroup<T>::~ElemViewGroup(void)
{
	std::list<T>::iterator it;
	for (it = views.begin(); it != views.end(); ++it) 
	{
		delete (*it);
	}
	views.clear();
	mapElem.clear();
}

#endif /** __ELEM_VIEW_GROUP_H__ */
