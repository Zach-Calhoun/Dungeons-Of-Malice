#pragma once
#include "ItemContainer.h"
#include "UI.h"
enum InvStates{INV_NAV, INV_OPT};
class InventoryManager
{
public:
	int crSelection;
	int crState;
	Container* inventory;
	Container* target;
	MenuInterface invMenu;
	

	InventoryManager();
	InventoryManager(int slots, Container* target);
	void showInventory(Container* target, int evtype);
	void update(int evtype);

};