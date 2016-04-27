#include "Creature.h"

Creature::Creature()
{
	AI = false;
	strength = 5;
	agility = 5;
	intellect = 5;
	vitality = 5;
	name = NULL;
	race = 0;
	type = 0;
	faction = 0;

	maxhp = strength * 3 + vitality * 5;
	maxmp = intellect * 3;
	hp = maxhp;
	mp = maxmp;

	speed = agility;
	crtick = 100;

	controller = NULL;
}
Creature::Creature(int s, int a, int i, int v, char* n, int r, int t,bool sx, int f, bool isAi, Map* map)
{
	AI = isAi;
	strength = s;
	agility = a;
	intellect = i;
	vitality = v;
	name = new char[strlen(n) + 1];
	strcpy(name, n);
	race = r;
	type = t;
	faction = f;
	female = sx;

	maxhp = strength * 3 + vitality * 5;
	maxmp = intellect * 3;
	hp = maxhp;
	mp = maxmp;

	
	if (isAi)
	{
		controller = new MobController(this, map, true);
	}
	else
	{
		controller = new PlayerController(this, map, true);
	}
	
	
}
Creature::~Creature()
{
	if (name)
		delete[] name;
	name = NULL;
	
	if (controller)
	{
		delete controller;
	}
	
}
void Creature::Setup(int s, int a, int i, int v, char* n, int r, int t,bool sx, int f)
{
	strength = s;
	agility = a;
	intellect = i;
	vitality = v;
	if (n != NULL)
	{
		name = new char[strlen(n) + 1];
		strcpy(name, n);
	}
	//name = new char[strlen(str_races[race] + str_types[type] + 2)];
	race = r;
	type = t;
	faction = f;
	female = sx;

	maxhp = strength * 3 + vitality * 5;
	maxmp = intellect * 3;
	hp = maxhp;
	mp = maxmp;
}


void Creature::Update(int evtype)
{
	if (!shouldAct)
	{
		crtick -= agility;
	}
	
	if (crtick <= 0)
	{
		
		//ac there
		if (AI)
		{
			
			shouldAct = true;
		}
		else
		{
			shouldAct = true;
			
		}

	}
}