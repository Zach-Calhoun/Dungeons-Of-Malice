#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include "Res.h"
#include "Creature.h"
#include "Items.h"

class Creature;
class Item;
class Object;
struct tile									// basic map tile, not so basic
{
	int x, y;								//x and y coordinates of the tile, useful in pathfinding, i think
	char type;								// the type of the tile, floor, wall, grass , etc
	bool passable; 
	tile* parent;							// for BFS
	int id;									// sector ID for caves
	int cost; 
	int dist;
	Creature* crCreature;						// useless for now
	Item* crItem;
	Object* crObject;
};

struct room									// no use for now, will be used in dungeon generation
{
	int x, y;
	int w, h;

};

struct BSP									// Binary Space Partition structure for use in dungeon generation
{
	int x, y;								// Top left corner of the partition
	int w, h;								// Width, height
	bool hor;								// is the division horizontal or vertical
	int pos;								// random position on which to split
	BSP* parent;							// parent of the leaf, might be relevant to generation
	BSP* l;									// left and right children
	BSP* r;
};

class Map									// the Map class, this holds the level, what a monster
{
public:
	int entrance_x;							// Level entrance position
	int entrance_y;
	int h;
	int w;
	char *name;
	int numRooms;
	tile** map_tiles;
	room* map_rooms;
	

	Map();
	Map(SDL_Surface* Context,int newh, int neww, char* newname);
	~Map();

	void clearTiles(tile** tar);		// function to reset all tiles to default
	void copyTiles(tile** src, tile** dst);			//copy tiles from one array to another, since I was lazy and tiles are structs not classes, i couldn't just do it with a 
													// copy constructor, or could I?
	int flood(int x, int y, int id);				// flood fill algorithm to calculate cave division area
	void BFS(int startx, int starty,int maxf);		// breadth first search in order to place the exit as far away from the entrance
	void divide(BSP* parent,int nrdiv);				// division for the BSP
	void GenerateCave(int cycles,int chance, int birth, int death);		// this generates organic caves using cellular automata
	void GenerateDungeon(int nrdiv); // this will eventaly generate dungeons, eventualy
	void GenerateRooms();


};
