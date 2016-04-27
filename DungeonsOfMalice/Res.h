#ifndef RES_H_
#define RES_H_ 1

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 400
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <SDL.h>
#include <math.h>
#include <time.h>

using namespace std;
extern bool GameRunning;
extern SDL_Window * Window;

Uint32 getpixel(SDL_Surface *surface, int x, int y);
void putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel);

//pixel acces shit



#endif