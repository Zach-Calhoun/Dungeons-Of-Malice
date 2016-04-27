#pragma once
#include "Items.h"

class ItemTemplates
{
public:
	weaponComponent* basicSword;
	statComponent* magicStat;
	armorComponent* breastPlate;
	armorComponent* headCap;
	consumableComponent* healthPot;

	Item itemWeaponSword;
	Item itemWeaponMagicSword;
	Item itemArmorBreastplate;
	Item itemArmorCap;
	Item itemPotionHealth;

	void InitItems();
	void DumpItems();
	
	~ItemTemplates();
};

