#ifndef CC
#define CC 1

#include "Creature.h"
#include "map.h"

class Map;
class Creature;
class CreatureController
{
public:
	bool AI;
	Creature* slave;
	Map* map;
	CreatureController();
	CreatureController(Creature* nc, Map* nm, bool isai);
	~CreatureController();
	virtual void Control(int evtype, Creature* player) = 0;
};

class PlayerController : public CreatureController
{
public:
	PlayerController();
	PlayerController(Creature* nc, Map* nm, bool isai);
	virtual void Control(int evtype, Creature* player);
};

class MobController : public CreatureController
{
	
public:
	MobController();
	MobController(Creature* nc, Map* nm, bool isai);
	virtual void Control(int evtype, Creature* player);
};

#endif