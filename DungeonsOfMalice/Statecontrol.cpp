#include "StateControl.h"

StateControl::StateControl()
{
	//playerShouldAct = false;
	ticks = 0;
	thisPlayer = NULL;
	thisMap = NULL;
	creatureList = NULL;
	numMobs = 0;
	invMan.crSelection = 0;
	invMan.inventory = NULL;
	viewInventory = false;

}

StateControl::StateControl(Creature* master, Map* thisMap)
{
	//playerShouldAct = true;
	ticks = 0;
	thisPlayer = master;
	this->thisMap = thisMap;
	viewInventory = false;
	invMan.crSelection = 0;
	invMan.inventory = thisPlayer->inventory;
}

StateControl::~StateControl()
{

}

void StateControl::update(int evtype)
{
	//weeeird
	ticks++;
	thisPlayer->Update(evtype);
	if (thisPlayer->shouldAct)
	{
		if (evtype == NOTHING && !(viewInventory || pickInventory))
			return;

		if (evtype == SHOW_INV)
		{
			viewInventory = !viewInventory;
			invMan.showInventory(thisPlayer->inventory, 0);
		}
		if (evtype == PICK)
		{
			if (thisMap->map_tiles[thisPlayer->y][thisPlayer->x].crItem)
			{
				invMan.inventory->takeItem(thisMap->map_tiles[thisPlayer->y][thisPlayer->x].crItem, NULL);
			}
			else if (thisMap->map_tiles[thisPlayer->y][thisPlayer->x].crCreature)
			{
				pickInventory = !pickInventory;
				invMan.showInventory(thisMap->map_tiles[thisPlayer->y][thisPlayer->x].crCreature->inventory, evtype);
			}
			
		}

		if (viewInventory)
		{
			invMan.update(evtype);
			if (invMan.invMenu.message == MENU_RETURN)
			{
				viewInventory = false;
			}
		}
		else if (pickInventory)
		{
			invMan.update(evtype);
		}
		else
		{
			thisPlayer->crtick = 100;
			thisPlayer->shouldAct = false;
			thisPlayer->controller->Control(evtype, NULL);
		}		
	}
		//else update other stuff
	else
	{
		for (int i = 0; i < numMobs; i++)
		{
			creatureList[i]->Update(0);
			if (creatureList[i]->shouldAct)
			{
				creatureList[i]->controller->Control(0, thisPlayer);
				creatureList[i]->crtick = 100;
				creatureList[i]->shouldAct = false;
			}
			
		}
	}
}