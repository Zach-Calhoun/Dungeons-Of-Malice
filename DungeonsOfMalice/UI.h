#ifndef UI_H
#define UI_H
#include "Res.h"
#include "Creature.h"

enum menuMessages { MENU_NOTHING, MENU_ACTIVATE, MENU_RETURN };

class Camera
{
public:
	bool tracking;		// is the camera tracking a specific creature?
	Creature* target;	// creature to track
	int x, y, w, h;		// basic stuff
	Camera();
	Camera(int nx, int ny, int nw, int nh);
	~Camera();

	void Track(Creature* tar);
};

class TextRenderer
{
public:
	SDL_Surface* font_bitmap;
	SDL_Rect src;
	SDL_Rect dst;

	TextRenderer();
	~TextRenderer();

	void renderText(SDL_Surface* target, int x, int y, char* input);	// why the fuck is this here? oh wait, UI
	void renderText(SDL_Surface* target, int x, int y, int input);
	//void renderScrollingText(SDL_Surface* target, int x, int y, char* input);
};

class MenuInterface
{
public:
	bool inSubMenu;
	int crSelection;
	int message;
	int numOptions;
	char* title;
	char* options[100];
	MenuInterface* subMenu;
	MenuInterface* parent;
	TextRenderer menuText;
	SDL_Surface* menuBuffer;

	MenuInterface();

	void reset(char* title);
	void addSubmenu(char* title);
	void addOption(char* optionName);
	void update(int ev);
	void render();
};

#endif