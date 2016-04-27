#include "Items.h"	

Item::Item()
{
	name = NULL;
	parentContainer = NULL;
	parentTile = NULL;

	wComp = NULL;
	aComp = NULL;
	cComp = NULL;
	sComp = NULL;
	descriptor = NULL;
}
Item::Item(Item& itemTemplate)
{
	name = itemTemplate.name;
	parentContainer = NULL;
	parentTile = NULL;
	wComp = itemTemplate.wComp;
	aComp = itemTemplate.aComp;
	cComp = itemTemplate.cComp;
	sComp = itemTemplate.sComp;
	descriptor = itemTemplate.descriptor;
}

Item::~Item()
{
	
}
weaponComponent::weaponComponent()
{
	type = W_MISC;
	minDamage = 0;
	maxDamage = 0;
	twoHand = false;
	ranged = false;
}
weaponComponent::weaponComponent(weaponType type, int minDamage, int maxDamage, bool twoHand, bool ranged)
{
	this->type = type;
	this->minDamage = minDamage;
	this->maxDamage = maxDamage;
	this->twoHand = twoHand;
	this->ranged = ranged;
}
armorComponent::armorComponent()
{
	type = A_MISC;
	armor = 0;
	speed = 0;
	dodge = 0;
}
armorComponent::armorComponent(armorType type, int armor, int speed, int dodge)
{
	this->type = type;
	this->armor = armor;
	this->speed = speed;
	this->dodge = dodge;
}
statComponent::statComponent()
{
	rarity = COMMON;
	for (int i = 0; i < 7; i++)
	{
		bonuses[i] = 0;
	}
}
consumableComponent::consumableComponent()
{
	charges = 0;
	hprestore = 0;
	manarestore = 0;
}
consumableComponent::consumableComponent(int charges, int hprestore, int manarestore)
{
	this->charges = charges;
	this->hprestore = hprestore;
	this->manarestore = manarestore;
}



