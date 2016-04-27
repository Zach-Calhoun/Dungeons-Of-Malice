#include "InventoryManager.h"

InventoryManager::InventoryManager()
{
	inventory = NULL;
	target = NULL;
	crState = 0;
}

InventoryManager::InventoryManager(int slots, Container* target)
{
	inventory = NULL;
	crState = 0;
	if (target)
	{
		target->maxItems = slots;
		target->nrItems = 0;
		target->itemList = new Item*[slots];
	}
}


void InventoryManager::showInventory(Container* target, int evtype)
{
	if (this->target == target)
	{
		invMenu.reset("Inventory");
		//invMenu.numOptions = target->nrItems;
		for (int i = 0; i < target->nrItems; i++)
		{
			invMenu.addOption(target->itemList[i]->name);
		}
	}
	else
	{
		invMenu.reset("Container");
		//invMenu.numOptions = target->nrItems;
		for (int i = 0; i < target->nrItems; i++)
		{
			invMenu.addOption(target->itemList[i]->name);
		}
	}
	

	//invMenu.subMenu = new InventoryManager;
}
void InventoryManager::update(int evtype)
{
	invMenu.update(evtype);
	if (invMenu.inSubMenu)
	{
		switch (invMenu.subMenu->message)
		{
		case MENU_NOTHING:
		{
			break;
		}
		case MENU_ACTIVATE:
		{
			switch (invMenu.subMenu->crSelection)
			{
			case 3:
			{
				//target->dropItem(,)
			}
			}
			break;
		}
		case MENU_RETURN:
		{
			break;
		}
	}
	
	}
}
