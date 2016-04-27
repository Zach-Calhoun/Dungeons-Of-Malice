#ifndef DRAWING_H_
#define DRAWING_H_
#include "Res.h"
#include "UI.h"
#include "map.h"
#define TILE_SIZE 64
double distance(int x1, int y1, int x2, int y2);
void drawLine(SDL_Surface* Screen, int startx, int starty, int tarx, int tary, Uint32 color);


class Renderer				// decided to have a special Renderer class to handle rendering, tired of blob classes that know how to do everything, also this takes care of bitmap loading
{							// and will allow me to do cool shit such as render targets and sorting, wooo
public:
	SDL_Surface * TileBitmap;			// bitmap that will hold the map tiles
	SDL_Surface * MobsBitmap;			// creatures
	SDL_Rect src, dst;					// Rects, cand blit without them

	Map* ThisMap;						// Pointer to the map
	Camera* ThisCamera;					// pointer to the camera   } these two will eventualy be moved from main in another Wolrd/Level class, or some game state manager
	SDL_Surface* Screen;				// pointer to the screen
	int SCR_W;							// hmm, why the fuck do I have these? I have them defined in res? What am I thinking? Must figure out
	int SCR_H;

	Renderer();
	Renderer(SDL_Surface* Context,Map* TargetMap,Camera* TargetCamera);
	~Renderer();

	void LoadTiles(char* file);			// Maybe should put theese two in a generic function... or not... or something
	void LoadMobs(char* file);
	void Setup(SDL_Surface* Context, Map* TargetMap, Camera* TargetCamera);
	void RenderMap();										
	void RenderCreature(Creature* target);		// might put these render functions in a super render all function in the class, maybe
};


#endif

