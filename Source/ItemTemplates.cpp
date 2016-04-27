#include "ItemTemplates.h"

/*
Item itemWeaponSword;
Item itemWeaponMagicSword;
Item itemArmorBreastplate;
Item itemArmorCap;
Item itemPotionHealth;
*/
void ItemTemplates::InitItems()
{

	basicSword = new weaponComponent(W_SWORD, 4, 6, false, false);
	magicStat = new statComponent;
	magicStat->rarity = MAGIC;
	magicStat->bonuses[STR] = 2;
	
	breastPlate = new armorComponent(A_CHEST, 10, -2, 0);
	headCap = new armorComponent(A_HEAD, 4, 0, 0);

	healthPot = new consumableComponent(3, 10, 0);

	itemWeaponSword.wComp = basicSword;
	itemWeaponSword.name = "Shord Sword";

	itemWeaponMagicSword.wComp = basicSword;
	itemWeaponMagicSword.sComp = magicStat;
	itemWeaponMagicSword.name = "Magic Sword";
	itemWeaponMagicSword.descriptor = "This is a magic sword";

	itemArmorBreastplate.aComp = breastPlate;
	itemArmorCap.aComp = headCap;
	itemArmorBreastplate.name = "Breast Plate";


	itemPotionHealth.cComp = healthPot;
	itemPotionHealth.name = "Health Vial";
}

void ItemTemplates::DumpItems()
{
	delete basicSword;
	delete magicStat;
	delete breastPlate;
	delete headCap;
	delete healthPot;
}

ItemTemplates::~ItemTemplates()
{
	delete basicSword;
	delete magicStat;
	delete breastPlate;
	delete headCap;
	delete healthPot;
}