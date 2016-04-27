#pragma once

#include "Res.h"
#include "map.h"
#include "Items.h"
#include "CreatureController.h"

struct tile;
class Container;
class CreatureController;

enum races{  RACE_OTHER, RACE_HUMAN, RACE_DWARF, RACE_ELF, RACE_ORC, RACE_TROLL, RACE_GOBLIN, RACE_UNDEAD, RACE_DEMON, RACE_GOLEM, RACE_DOG, RACE_CAT, RACE_WOLF, RACE_BEAR, RACE_PIG, RACE_PIGMAN, RACE_CENTAUR, RACE_DRAGON };
enum types{ T_OTHER,T_WARRIOR,T_BARBARIAN,T_SCAVENGER,T_MINER,T_RECRUIT,T_CIVILIAN,T_ARCHER,T_HUNTER,T_RANGER,T_ROGUE,T_THIEF,T_ASSASIN,T_KNIGHT,T_PALLADIN,T_PRIEST,T_SHAMAN,T_DRUID,T_MAGE,T_ARCANIST,T_WARLOCK,T_NECROMANCER};
enum evtypes{ NOTHING, LEFT, RIGHT, UP, DOWN, SHOW_INV, USE, PICK, RETURN};
class Creature
{
public:
	int x, y;		// coordinates
	bool AI;		// is it AI controlled, might need to add AI type too, once AI acutaly is implemented
	//base stats
	int strength;
	int agility;
	int intellect;
	int vitality;
	bool female;

	int speed;
	int crtick;
	bool shouldAct;

	int maxhp;
	int hp;
	int maxmp;
	int mp;

	char* name;		// unique or generic name
	int race;		// race, affects graphics, and maybe stats, eventualy
	int type;		// the "class" of the creature
	int faction;	// kinda like teams

	tile* parentTile;
	Container* inventory;
	CreatureController* controller;

	Creature();
	Creature(int s, int a, int i, int v, char* n, int r, int t,bool sx, int f, bool isAi, Map* map);
	~Creature();
	void Setup(int s, int a, int i, int v, char* n, int r, int t,bool sx, int f);
	void Update(int evtype);
	//void Battle(Creature* target);
};



