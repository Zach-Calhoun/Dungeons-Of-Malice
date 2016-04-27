#pragma once
#include "Res.h"
#include "Items.h"	

class Container
{
	//need tile master
public:
	int nrItems;
	int maxItems;
	Item** itemList;
	Object* parentObject;
	Creature* parentCreature;

	Container();
	Container(int maxItems);
	~Container();

	void takeItem(Item* newItem, Container* container);
	void addItem(Item* newItem);
	void dropItem(Item* selItem, Map* map);

};