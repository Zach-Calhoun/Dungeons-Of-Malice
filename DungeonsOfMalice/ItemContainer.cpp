#include "ItemContainer.h"

Container::Container()
{

	nrItems = 0;
	maxItems = 10;
	itemList = NULL;
	parentObject = NULL;
	parentCreature = NULL;

	itemList = new Item*[maxItems];
	for (int i = 0; i < maxItems; i++)
	{
		itemList[i] = NULL;
	}
}

Container::~Container()
{

}
void Container::takeItem(Item* newItem, Container* container) // takes an item from somewhere else
{
	if (newItem)
	{
		if (nrItems < maxItems)
			for (int i = 0; i < maxItems; i++)
			{
				if (itemList[i] == NULL)
				{
					itemList[i] = newItem;
					nrItems++;
					if (container)
					for (int j = 0; j < container->maxItems; j++)
					{
						if (container->itemList[j] == newItem)
						{
							container->itemList[j] = NULL;
							break;
						}
					}
					newItem->parentContainer = this;

					if (newItem->parentTile)
					{
						newItem->parentTile->crItem = NULL;
						newItem->parentTile = NULL;
					}

					break;
				}
			}
	}
} 

void Container::addItem(Item* newItem) //creates a completely new item, duplicates a template
{
	if (newItem)
	{
		if (nrItems < maxItems)
			for (int i = 0; i < maxItems; i++)
			{
				if (itemList[i] == NULL)
				{
					itemList[i] = new Item(*newItem);
					itemList[i]->parentContainer = this;
					nrItems++;	
					break;
				}
			}
	}
}

void Container::dropItem(Item* selItem, Map* map)
{
	if (selItem)
	{
		for (int i = 0; i < maxItems; i++)
		{
			if (itemList[i] == selItem)
			{
				itemList[i] = NULL;
				selItem->parentContainer = NULL;
				nrItems--;
				selItem->parentTile = &map->map_tiles[parentCreature->y][parentCreature->x];
				break;
			}
		}
	}
}