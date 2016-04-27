#include "Drawing.h"


double distance(int x1, int y1, int x2, int y2)
{
	return sqrt(abs(x1 - x2)+abs(y1 - y2));
}

void drawLine(SDL_Surface* Screen,int startx,int starty,int tarx,int tary,Uint32 color)
{
	int crx = startx;
	int cry = starty;
	int dx;
	int dy;
	int sx;
	int sy;
	int err;
	int e2;

		if (crx != tarx && cry != tary)
		{	
			dx = abs(tarx - startx);
			dy = abs(tary - starty);
			if (crx < tarx) sx = 1; else sx = -1;
			if (cry < tary) sy = 1; else sy = -1;
			err = dx - dy; 

			while (!(crx == tarx && cry == tary))
			{
				e2 = 2 * err;
				if (e2 > -dy)
				{
					err = err - dy;
					crx += sx;
				}
				if (e2 < dx)
				{
					err = err + dx;
					cry += sy;
				}

				putpixel(Screen, crx, cry, color);
			}
		}
		else if (startx == tarx && starty != tary) //if horizontal line, these parts are added by me
		{
			if (tary - starty > 0)
				dy = 1;
			else
				dy = -1;
			cry = starty;
			crx = startx;
			while (cry != tary)
			{
				cry += dy;
				
					
						putpixel(Screen, crx, cry, color);
					
			}
		
		}
		else if (startx != tarx && starty == tary)//if vertical line
		{
			if (tarx - startx > 0)
				dx = 1;
			else
				dx = -1;
			cry = starty;
			crx = startx;
			while (crx != tarx)
			{
				crx += dx;
				
						putpixel(Screen, crx,cry,color);
			}
		}
}		// these two are 

// ^theese two are useless atm, but they work fine, since the drawing one was ripped form wikipedia :P, with some minor modifications from yours turlly

// comment theese asap too
Renderer::Renderer()		
{
	SCR_H = SCREEN_HEIGHT;
	SCR_W = SCREEN_HEIGHT;
	Screen = NULL;
	ThisMap = NULL;
	ThisCamera = NULL;

	TileBitmap = SDL_LoadBMP("map_tiles.bmp");

	src.h = TILE_SIZE;
	src.w = TILE_SIZE;
	dst.h = TILE_SIZE;
	dst.w = TILE_SIZE;
}
Renderer::Renderer(SDL_Surface* Context, Map* TargetMap, Camera* TargetCamera)
{
	Screen = Context;
	ThisMap = TargetMap;
	ThisCamera = TargetCamera;
	SCR_H = SCREEN_HEIGHT;
	SCR_W = SCREEN_HEIGHT;

	TileBitmap = SDL_LoadBMP("map_tiles.bmp");
	MobsBitmap = SDL_LoadBMP("mob_sprites.bmp");

	src.h = 64;
	src.w = 64;
	dst.h = 64;
	dst.w = 64;
	Screen = Context;
}
Renderer::~Renderer()
{
	SDL_FreeSurface(TileBitmap);
	SDL_FreeSurface(MobsBitmap);
}

void Renderer::LoadTiles(char* file)
{
	TileBitmap = SDL_LoadBMP(file);
}
void Renderer::LoadMobs(char* file)
{
	MobsBitmap = SDL_LoadBMP(file);
}
void Renderer::Setup(SDL_Surface* Context, Map* TargetMap, Camera* TargetCamera)
{
	Screen = Context;
	ThisMap = TargetMap;
	ThisCamera = TargetCamera;
	SCR_H = SCREEN_HEIGHT;
	SCR_W = SCREEN_HEIGHT;
}
void Renderer::RenderMap()
{
	int startx, starty, endx,  endy;
	startx = ThisCamera->x / TILE_SIZE;
	starty = ThisCamera->y / TILE_SIZE;
	endx = (ThisCamera->x + ThisCamera->w) / TILE_SIZE +1;
	endy = (ThisCamera->y + ThisCamera->h) / TILE_SIZE +1;

	for (int i=starty; i < endy; i++)
	{
		for (int j = startx; j < endx; j++)
		{
			if (i >= ThisMap->h || j >= ThisMap->w || i < 0 || j < 0)
				continue;
			src.x = ThisMap->map_tiles[i][j].type * 64;
			src.y = 0;
			dst.x = (ThisMap->map_tiles[i][j].x) * 64 - ThisCamera->x;
			dst.y = (ThisMap->map_tiles[i][j].y) * 64 - ThisCamera->y;
			//dst.x = (j-startx) * TILE_SIZE -32;
			//dst.y = (i-starty) * TILE_SIZE -32;
			SDL_BlitSurface(TileBitmap, &src, Screen, &dst);
		}
	}
}

void Renderer::RenderCreature(Creature* target)
{
	dst.x = (target->x * 64)-ThisCamera->x;
	dst.y = (target->y * 64) - ThisCamera->y;
	src.x = target->type * 64;
	src.y = target->race * 64;
	SDL_BlitSurface(MobsBitmap, &src, Screen, &dst);
}