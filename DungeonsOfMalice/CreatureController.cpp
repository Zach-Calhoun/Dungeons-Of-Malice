#include "CreatureController.h"

CreatureController::CreatureController()
{
	AI = false;
	slave = NULL;
	map = NULL;
}
CreatureController::CreatureController(Creature* nc, Map* nm, bool isai)
{
	AI = isai;
	slave = nc;
	map = nm;

}
CreatureController::~CreatureController()
{
	
}

PlayerController::PlayerController()
{
	AI = false;
	slave = NULL;
	map = NULL;
}

PlayerController::PlayerController(Creature* nc, Map* nm, bool isai)
{
	AI = isai;
	slave = nc;
	map = nm;
}

MobController::MobController()
{
	AI = true;
	slave = NULL;
	map = NULL;	
}

MobController::MobController(Creature* nc, Map* nm, bool isai)
{
	AI = isai;
	slave = nc;
	map = nm;
}

void PlayerController::Control(int evtype, Creature* player)
{
	switch (evtype)
	{
	case(LEFT) :
	{
		if (map->map_tiles[slave->y][slave->x - 1].passable)
			slave->x--;
		break;
	}
	case(RIGHT) :
	{
		if (map->map_tiles[slave->y][slave->x + 1].passable)
			slave->x++;
		break;
	}
	case(UP) :
	{
		if (map->map_tiles[slave->y - 1][slave->x].passable)
			slave->y--;
		break;
	}
	case(DOWN) :
	{
		if (map->map_tiles[slave->y + 1][slave->x].passable)
			slave->y++;
		break;
	}
	}
}



void MobController::Control(int evtype, Creature* player)
{
	evtype = 1 + rand() % 4;
	switch (evtype)
	{
	case(LEFT) :
	{
		if (map->map_tiles[slave->y][slave->x - 1].passable)
			slave->x--;
		break;
	}
	case(RIGHT) :
	{
		if (map->map_tiles[slave->y][slave->x + 1].passable)
			slave->x++;
		break;
	}
	case(UP) :
	{
		if (map->map_tiles[slave->y - 1][slave->x].passable)
			slave->y--;
		break;
	}
	case(DOWN) :
	{
		if (map->map_tiles[slave->y + 1][slave->x].passable)
			slave->y++;
		break;
	}
	}
}