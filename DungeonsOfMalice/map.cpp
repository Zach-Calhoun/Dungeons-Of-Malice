#include "map.h"
#include "Res.h"
#include <queue>

// commenting this big daddy will be a big pain in the fucking ass

Map::Map()				// the basics constructors, nothing too fancy here
{
	entrance_x = 0;
	entrance_y = 0;
	w = 0;
	h = 0;
	map_tiles = NULL;
	name = NULL;
	numRooms = 0;
	map_rooms = NULL;
}
Map::Map(SDL_Surface* Context, int newh, int neww, char* newname)
{
	entrance_x = 0;
	entrance_y = 0;
	h = newh;
	w = neww;
	name = new char[strlen(newname) + 1];
	strcpy(name, newname);
	map_tiles = new tile*[h];
	for (int i = 0; i < h; i++)
	{
		map_tiles[i] = new tile[w];
	}
	numRooms = 0;
	map_rooms = NULL;
}
Map::~Map()
{
	if (name)
		delete[] name;
	if (map_tiles)
	{
		for (int i = 0; i < h; i++)
		{
			delete[] map_tiles[i];
		}
		delete[] map_tiles;
	}
	delete[] map_rooms;

}

void Map::clearTiles(tile** tar)			// function to clear tiles to default state
{
	for (int i = 0; i < h; i++)
		for (int j = 0; j < w; j++)
		{
		tar[i][j].x = j;
		tar[i][j].y = i;
		tar[i][j].type = 0;
		tar[i][j].passable = false;
		tar[i][j].parent = NULL;
		tar[i][j].id = 0;
		tar[i][j].cost = 0;
		tar[i][j].dist = 0;
		tar[i][j].crCreature = NULL;
		tar[i][j].crItem = NULL;
		tar[i][j].crObject = NULL;
		}
}
void Map::copyTiles(tile** src, tile** dst)			// function to copy tiles from temp array to map, used for cave generation, hint, Conway's game of life
{
	for (int i = 0; i < h; i++)
		for (int j = 0; j < w; j++)
		{
		dst[i][j].x = src[i][j].x;
		dst[i][j].y = src[i][j].y;
		dst[i][j].type = src[i][j].type;
		dst[i][j].passable = src[i][j].passable;
		dst[i][j].parent = src[i][j].parent;
		dst[i][j].id = src[i][j].id;
		dst[i][j].cost = src[i][j].cost;
		dst[i][j].dist = src[i][j].dist;
		dst[i][j].crCreature= src[i][j].crCreature;
		dst[i][j].crItem = src[i][j].crItem;
		dst[i][j].crObject = src[i][j].crObject;
		}
}
void Map::BFS(int startx, int starty,int maxf)		// some kind of Breadth First Search, used to place the map exit as far away from the map entrance
{
	map_tiles[starty][startx].type = 2;				// will eventualy replace int types with enums for tiles, we make the map entrance a map entrance tile
	entrance_x = startx;
	entrance_y = starty;
	//int pos;										// i'm nt using this, but when I put it here I'm sure I had a reason, maybe
	queue <tile*> open;								// STL Queue FTW for the 'open" list
	int crdist = 1;									// i set this to one for some reason, bugs or smthing
	int x, y;										// i'm guessing theese store the current x,y coordinates of the tile being visited, why? not sure
	int visited = 0;								// number of visited tiles, for debugging reasons , to avoid infinite loops, issue might be fixed, but let it stay

	x = startx;
	y = starty;
	open.push(&map_tiles[y][x]);					// add the first tile to the list
	while (visited < maxf)							// yeah here's the infinite loop failsafe
	{
		visited++;
		open.front()->dist = crdist++;				// basic BFS stuff
		x = open.front()->x;
		y = open.front()->y;
		if (x > 0 && map_tiles[y][x - 1].passable == true && map_tiles[y][x - 1].parent == NULL && map_tiles[y][x - 1].dist == 0)  // make sure neightbours are passable and inside the array
		{
			map_tiles[y][x - 1].parent = open.front();																				// set the neighbour's parent to the current tile, 
																																	// not really using it, bot usefull for acutal pathfinding
																																	// just follow the parrent downstream from end to source
			open.push(&map_tiles[y][x - 1]);
		}
		if (x < w - 1 && map_tiles[y][x + 1].passable == true && map_tiles[y][x + 1].parent == NULL && map_tiles[y][x + 1].dist == 0)
		{
			map_tiles[y][x + 1].parent = open.front();
			open.push(&map_tiles[y][x + 1]);
		}
		if (y > 0 && map_tiles[y - 1][x].passable == true && map_tiles[y - 1][x].parent == NULL && map_tiles[y - 1][x].dist == 0)
		{
			map_tiles[y - 1][x].parent = open.front();
			open.push(&map_tiles[y - 1][x]);

		}
		if (y < h - 1 && map_tiles[y + 1][x].passable == true && map_tiles[y + 1][x].parent == NULL && map_tiles[y + 1][x].dist == 0)
		{
			map_tiles[y + 1][x].parent = open.front();
			open.push(&map_tiles[y + 1][x]);			
		}
		if (!open.empty())	// pop out this tile, it's done with, since we're not doing any fancy A* or diagonal shit
			open.pop();
		if (open.empty())	// if the open list is empty, we've visited the last tile, which should, i think, be the furthes tile yet
		{
			map_tiles[y][x].type = 3;		// set it's type to exit tile
			break;
		}
	}
	while (!open.empty())					// tehnicaly this should never execute, shoud... but just in case
		open.pop();
	
}
int Map::flood(int x, int y, int id)		// old fassion floodfill to calculate areas of cave sectors, by sector I mean individual opening not connected to others
{
	static int filled = 0;

	map_tiles[y][x].id = id;
	filled++;
	if (x > 0 && map_tiles[y][x - 1].passable == true && map_tiles[y][x - 1].id == 0)
	{
		flood(x - 1, y, id);
	}
	if (x < w - 1 && map_tiles[y][x + 1].passable == true && map_tiles[y][x + 1].id == 0)
	{
		flood(x + 1, y, id);
	}
	if (y > 0 && map_tiles[y - 1][x].passable == true && map_tiles[y - 1][x].id == 0)
	{
		flood(x, y - 1, id);
	}
	if (y < h - 1 && map_tiles[y + 1][x].passable == true && map_tiles[y + 1][x].id == 0)
	{
		flood(x, y + 1, id);
	}
	return filled;
}
void Map::GenerateCave(int cycles,int chance,int birth,int death)		// here we use Conway's Game of Life rules to generate organic cave like sturctures
{
	tile** buff = new tile*[h];											// we need a buffer array to swap between, rules are checked on old array, changes made on buffer, swap them between cycles
	for (int i = 0; i < h; i++)
		buff[i] = new tile[w];

	clearTiles(map_tiles);												//clean everything up

	srand((unsigned int)time(NULL));													//set the seed

	for (int i = 0; i < h; i++)
		for (int j = 0; j < w; j++)
		{
			if (rand() % 10 > chance)
				map_tiles[i][j].type = 1;								// "activate" random "cells" in the array, these will later develop to shape the cave
		}
	clearTiles(buff);													// clear the buffer
	for (int sn = 0; sn < cycles; sn++)									//run a certain number of cycles
	{
		int sum = 0;													// number of neighbours of each cell
		for (int i = 0; i < h; i++)
		{
			for (int j = 0; j < w; j++)									// visit neighbour number and apply the rules
			{
				for (int k = i - 1; k <= i + 1; k++)
				{
					for (int l = j - 1; l <= j + 1; l++)
					{
						if (k < 0 || k >= h || l < 0 || l >= w)
							continue;
						if (!(k == i  && l == j))
							if (map_tiles[k][l].type)
								sum++;
					}
				}
				if (map_tiles[i][j].type)
				{
					if (sum < death)
						buff[i][j].type = 0;
					else
						buff[i][j].type = 1;
				}
				else
				{
					if (sum >= birth)
						buff[i][j].type = 1;
				}
				sum = 0;
			}
		}
		copyTiles(buff, map_tiles);										//move the buffer to the actual map 
		clearTiles(buff);
	}
	for (int i = 0; i < w; i++)											// place a nice border arround the map to make sure we don't have any gaps
	{
		map_tiles[0][i].type = 1;
		map_tiles[h-1][i].type = 1;
	}
	for (int i = 0; i < h; i++)
	{
		map_tiles[i][0].type = 1;
		map_tiles[i][w-1].type = 1;
	}
		
	
	for (int i = 0; i < h; i++)
		delete[] buff[i];
	delete[] buff;

	int numfloors = 0;												// total number of floors , I think
	int foundfloors = 0;											// floors visited
	int areas[32];													// area of each sector, 32 max sectors should be fine
	int sectors=0;													// current number of discovered sectors
	int crid = 1;													// current sector ID, we give each sector an unique ID
	int x, y;														// coordinates, used for... something
	bool br = false;												// for breaking some loops

	for (int i = 0; i < h; i++)										// first do an overal pass and make sure walls are not passable and count the number of floors ( open spaces, these we count toward
																	// sector area
	{
		for (int j = 0; j < w; j++)
		{
			if (map_tiles[i][j].type == 1)
				map_tiles[i][j].passable = false;
			else
			{
				map_tiles[i][j].passable = true;
				numfloors++;
			}
		}
	}
	while (foundfloors < numfloors)									// keep searching until we checked all floors
	{
		for (int i = 0; i < h; i++)									// start looking for an open floor that is not visited ( id = 0 )
		{
			for (int j = 0; j < w; j++)
			{
				if (map_tiles[i][j].passable == true && map_tiles[i][j].id == 0)			//WTF why is this set to false? if we find it, we break and start the flood fill, rinse and repeat
				{
					y = i;
					x = j;
					br = true;
					break;
				}
			}
			if (br)break;
		}
		areas[crid] = flood(x, y, crid);						// function returns number of visited floor, so area of sector, adn we store it, we choose the largest sector as play area
		foundfloors += areas[crid];
		sectors++;
		crid++;
	}

	int maxf = 0;	// use theese variables to find the bigges sector
	int maxi = 0;
	for (int i = 1; i < sectors + 1; i++)
	{
		if(maxf < areas[i])
		{
			maxf = areas[i];
			maxi = i;
		}
	}
	int startx, starty;
	while (true)		// loop infinetiley, generate two random coordinates, check if they're in the biggest sector and on a floor, bam, set it as starting location
	{
		startx = rand() % w;
		starty = rand() % h;
		if (map_tiles[starty][startx].id == maxi-1 &&map_tiles[starty][startx].passable)
		{
			break;
		}
	}
	map_tiles[starty][startx].type = 2;
	BFS(startx, starty, areas[maxi]);		// do the BFS to place the exit

}
void Map::divide(BSP* parent,int nrdiv)			// binary space partitioning division, I heard this generates nice rooms, kinda WIP, also screw pointers and memory in general
												// I should learn java... LATER EDIT: who needs java anyway
{
	static int divs = 0;
	divs++;
	parent->l = new BSP;
	parent->r = new BSP;
	parent->l->parent = parent;
	parent->r->parent = parent;
	parent->l->l = NULL;
	parent->l->r = NULL;
	parent->r->r = NULL;
	parent->r->l = NULL;
	if (parent->h <= 10)
	{
		parent->hor = true;
	}
	else if (parent->w <= 10)
	{
		parent->hor = false;
	}
	else
	{
		parent->hor = rand() % 2;
	}
	

	if (parent->hor)
	{
		parent->pos = 5 + rand() % (parent->h - 10);		
		parent->l->x = parent->x;
		parent->l->y = parent->y;
		parent->l->h = parent->pos;
		parent->l->w = parent->w;
		parent->r->x = parent->x;
		parent->r->y = parent->pos;
		parent->r->h = parent->h - parent->pos;
		parent->r->w = parent->w;
	}
	else
	{
		parent->pos = 5 + rand() % (parent->w - 10);
		parent->l->x = parent->x;
		parent->l->y = parent->y;
		parent->l->h = parent->h;
		parent->l->w = parent->pos;
		parent->r->x = parent->pos;
		parent->r->y = parent->y;
		parent->r->h = parent->h;
		parent->r->w = parent->w - parent->pos;
	}
	if (divs < nrdiv)
	{
		divide(parent->l,nrdiv);
		divide(parent->r,nrdiv);
	}
	

	
}

void clearbsp(BSP *start)				// couldn't write this to save my life, I was close but in the end had to google it, actualy i did it mighty fine
										// but I was attemtping to delete a stack allocated variable , genius
{	
	if (start->l)
		clearbsp(start->l);
	if (start->r)
		clearbsp(start->r);
	delete start;
	start = NULL;
}

void bsptomap(BSP *start, Map* thismap)			// this interates through teh BSP leafs and generates rooms, or at least should
{
	//convers the BSP tree into acutal rooms
	static int tag;
	if (start->l)
		bsptomap(start->l,thismap);
	if (start->r)
		bsptomap(start->r,thismap);
	if (!start->r && !start->l) // if leaf
	{
		/*
		int twothird = 2 * (start->h / 3);
		thismap->map_rooms[tag].h = twothird + rand() % (start->h - twothird);
		twothird = 2 * (start->w / 3);
		thismap->map_rooms[tag].w = twothird + rand() % (start->w - twothird);

		thismap->map_rooms[tag].x = start->x + rand() % (start->w - thismap->map_rooms[tag].w);
		thismap->map_rooms[tag].y = start->y + rand() % (start->h - thismap->map_rooms[tag].h);

		*/ // <- something is wrong with this section
		thismap->map_rooms[tag].h = start->h;
		thismap->map_rooms[tag].w = start->w;
		thismap->map_rooms[tag].x = start->x;
		thismap->map_rooms[tag].y = start->y;

		tag++;


		/*
		
		for (int i = start->y; i < start->y + start->h; i++)
		{
			for (int j = start->x; j < start->x + start->w; j++)
			{
				if (i == start->y || i == start->y + start->h - 1 || j == start->x || j == start->x + start->w - 1)
				{
					thismap->map_tiles[i][j].type = 1;
					thismap->map_tiles[i][j].passable = true; //for debugging reasons
					thismap->map_tiles[i][j].id = tag;
				}
				else
				{
					thismap->map_tiles[i][j].type = 0;
					thismap->map_tiles[i][j].passable = true;
					thismap->map_tiles[i][j].id = tag;
				}
			}
		}
		
		*/
		

		//no longer filling whole BSP division with room, now that bsp works fine, we gneerate smaller rooms
		//thismap->numRooms++;

	}
	//finaly the BSP rectangles work fine, now to generate actual rooms and connect them
}

void Map::GenerateRooms()
{
	clearTiles(this->map_tiles);
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			map_tiles[i][j].type = 1;
			map_tiles[i][j].passable = true; // all passable for now

		}
	}
	for (int k = 0; k < numRooms; k++)
	{
		for (int i = map_rooms[k].y; i < map_rooms[k].y + map_rooms[k].h; i++)
		{
			for (int j = map_rooms[k].x; j < map_rooms[k].x + map_rooms[k].w; j++)
			{
				if (i == map_rooms[k].y || i == map_rooms[k].y + map_rooms[k].h - 1 || j == map_rooms[k].x || j == map_rooms[k].x + map_rooms[k].w - 1)
				{
					//shit
				}
				else
				{
					map_tiles[i][j].type = 0;
				}
				map_tiles[i][j].id = k;
			}
		}
	}
	FILE* tmp;
	tmp = fopen("dungeon.txt", "w");
	{
		for (int i = 0; i < h; i++)
		{
			for (int j = 0; j < w; j++)
			{
				if (map_tiles[i][j].type == 0)
				{
					fprintf(tmp, "%c", '.');
				}
				else
				{
					fprintf(tmp, "%c", '#');
				}
			}
			fprintf(tmp, "\n");
		}

		for (int i = 0; i < numRooms; i++)
		{
			fprintf(tmp, "ROOM %i: \n X: %d \n Y: %d \n W: %d \n H: %d \n", i, map_rooms[i].x, map_rooms[i].y, map_rooms[i].w, map_rooms[i].h);
		}
	}
	fclose(tmp);
}

void Map::GenerateDungeon(int nrdiv)
{
	
	srand((unsigned int)time(NULL));
	BSP* start;
	start = new BSP;
	int divs = 0;
	start->x = 0;
	start->y = 0;
	start->w = w;
	start->h = w;
	start->parent = NULL;
	start->l = NULL;
	start->r = NULL;
	divide(start,nrdiv);

	clearTiles(map_tiles);
	numRooms = 1 << nrdiv-1; // 2^n
	map_rooms = new room[numRooms];

	bsptomap(start, this);
	GenerateRooms();
	



	clearbsp(start);


}