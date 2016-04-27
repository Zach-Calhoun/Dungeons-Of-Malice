#pragma once
#include "Res.h"
#include "map.h"
class Creature;
struct tile;

class Item;
class weaponComponent;
class armorComponent;
class consumableComponent;
class statComponent;
class Container;
class Object;



//typedef enum itype{MISC, SWORD, MACE, AXE, STAFF, SHIELD, BOW, CROSSBOW, WAND, SCROLL, POTION, FOOD, BOOK}itemType;
typedef enum wtype{W_MISC, W_SWORD, W_MACE, W_AXE, W_STAFF, W_SHIELD, W_BOW, W_CROSSBOW}weaponType;
typedef enum atype{A_MISC, A_HEAD,A_CHEST,A_LEGS,A_BOOTS,A_RING,A_NECK,A_BELT}armorType;
//typedef enum islot {NONE, ONEHAND, TWOHAND, CHEST, BELT, PANTS, BOOTS, HAT, RING, AMULET}itemSlot;
typedef enum irarity { COMMON, MAGIC, RARE, UNIQUE }itemRarity;
enum ibonus{ STR, AGI, INT, HLEALTH, MANA, HREGEN, MREGEN };

//add magic component

class weaponComponent
{
public:
	weaponComponent();
	weaponComponent(weaponType type, int minDamage, int maxDamage, bool twoHand, bool ranged);
	weaponType type;
	int minDamage;
	int maxDamage;
	bool twoHand;
	bool ranged;
};

class armorComponent
{
public:
	armorComponent();
	armorComponent(armorType type, int armor, int speed, int dodge);
	armorType type;
	int armor;
	int speed;
	int dodge;
};

class statComponent
{
public:
	statComponent();
	itemRarity rarity;
	int bonuses[7];
};

class consumableComponent
{
public:
	consumableComponent();
	consumableComponent(int charges, int hprestore, int manarestore);
	int charges;
	int hprestore;
	int manarestore;
};

class Item
{
public:
	char* name;
	char* descriptor;

	Container* parentContainer;
	tile* parentTile;

	weaponComponent* wComp;
	armorComponent* aComp;
	statComponent* sComp;
	consumableComponent* cComp;
	
	Item();
	Item(Item& itemTemplate);
	~Item();
};






class Object
{
	tile* parentTile;
	Container* inventory;
};