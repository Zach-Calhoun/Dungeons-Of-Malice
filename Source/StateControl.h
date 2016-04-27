#pragma once
#include "Creature.h"
#include "InventoryManager.h"
#include "map.h"

class StateControl
{
public:
	int ticks;
	int numMobs;
	bool viewInventory;
	bool pickInventory;
	Creature *thisPlayer;
	Map* thisMap;
	Creature** creatureList;
	InventoryManager invMan;

	StateControl();
	~StateControl();
	StateControl(Creature* Master, Map* thisMap);
	void update(int evtype);

};