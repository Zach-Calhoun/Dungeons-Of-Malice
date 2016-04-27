#include "UI.h"


Camera::Camera()
{
	x = 0;
	y = 0;
	w = 0;
	h = 0;
	tracking = false;
	target = NULL;
}
Camera::Camera(int nx, int ny, int nw, int nh)
{
	x = nx;
	y = ny;
	w = nw;
	h = nh;
	tracking = false;
	target = NULL;
}
Camera::~Camera()
{

}

void Camera::Track(Creature* tar)
{
	target = tar;
	tracking = true;
}


TextRenderer::TextRenderer()
{
	font_bitmap = SDL_LoadBMP("fonts.bmp");
	src.h = 20;	// height of a symbol
	src.w = 12; // width of a symbol
	dst.h = 20;
	dst.w = 12;
	SDL_SetColorKey(font_bitmap, SDL_ENABLE, 0xff00ff);
}

TextRenderer::~TextRenderer()
{
	if (font_bitmap)
		SDL_FreeSurface(font_bitmap);
}
void TextRenderer::renderText(SDL_Surface* target,int x, int y,char* input)		// wrote my own text displaying function because fuck fonts and SDL_Text														// will need to place this in a nice class wich handles memory and loading
{	
	dst.y = y;
	for (unsigned int i = 0; i < strlen(input); i++)				// for each char in the argument string
	{													// reminder! add formating options, newline at least, also transparency
		dst.x = x + (i * 12);							
		src.x = ((input[i] - 32)%32) * 12 ;				// this one is fun to explain. we calculate the source x position by substracting 32 from the ASCII code, because there are 32 characters
		src.y = ((input[i] - 32) / 32) * 20;			// that I don't need to use, so I dump them, so basicaly 32, which is, 0 I think, maps to X coordinate 0, and so on
		SDL_BlitScaled(font_bitmap, &src, target, &dst);
	}
}

void TextRenderer::renderText(SDL_Surface* target, int x, int y, int input)		// wrote my own text displaying function because fuck fonts and SDL_Text														// will need to place this in a nice class wich handles memory and loading
{
	dst.y = y;
	char buffer[10];
	int tmp = 0;
	int num = -1;
	for (int i = 0; i < 10; i++)
	{
		buffer[i] = '\0';
	}
	tmp = input;
	while (tmp > 0)
	{
		tmp = tmp / 10;
		num++;
	}
	while (input > 0)
	{
		tmp = input % 10;
		input = input / 10;
		buffer[num--] = tmp + 48;
	}
	for (unsigned int i = 0; i < strlen(buffer); i++)				// for each char in the argument string
	{													// reminder! add formating options, newline at least, also transparency
		dst.x = x + (i * 12);
		src.x = ((buffer[i] - 32) % 32) * 12;				// this one is fun to explain. we calculate the source x position by substracting 32 from the ASCII code, because there are 32 characters
		src.y = ((buffer[i] - 32) / 32) * 20;			// that I don't need to use, so I dump them, so basicaly 32, which is, 0 I think, maps to X coordinate 0, and so on
		SDL_BlitScaled(font_bitmap, &src, target, &dst);
	}
}

MenuInterface::MenuInterface()
{
	for (int i = 0; i < 100; i++)
	{
		options[i] = NULL;
	}
	menuBuffer = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 24, 0, 0, 0, 0);
	SDL_FillRect(menuBuffer, NULL, 0xff00ff);
	SDL_SetColorKey(menuBuffer, SDL_ENABLE, 0xff00ff);
	numOptions = 0;
	inSubMenu = false;
	subMenu = NULL;
	parent = NULL;
	message = 0;
}
void MenuInterface::reset(char* title)
{
	for (int i = 0; i < 100; i++)
	{
		options[i] = NULL;
	}
	SDL_FillRect(menuBuffer, NULL, 0xff00ff);
	SDL_SetColorKey(menuBuffer, SDL_ENABLE, 0xff00ff);
	numOptions = 0;
	inSubMenu = false;
	//possible memory leak with submenu here
	subMenu = NULL;
	parent = NULL;
	message = 0;
}


void MenuInterface::addSubmenu(char* title)
{
	subMenu = new MenuInterface;
	subMenu->title = title;
	subMenu->parent = this;
}
void MenuInterface::addOption(char* optionName)
{
	numOptions++;
	options[numOptions - 1] = optionName;
}
void MenuInterface::update(int ev)
{
	if (inSubMenu)
	{
		/*
		if (ev == RETURN)
		{
		inSubMenu = false;
		}
		*/
		
		subMenu->update(ev);
		subMenu->render();
	}
	else
	{
		switch (ev)
		{
		case DOWN:
		{
			crSelection = (crSelection++) % numOptions;
			break;
		}
		case UP:
		{
			crSelection = (crSelection--) % numOptions;
			break;
		}
		case USE:
		{
			if (parent == NULL)
			{
				addSubmenu("options");
				inSubMenu = true;
				subMenu->addOption("Inspect");
				subMenu->addOption("Equip");
				subMenu->addOption("Use");
				subMenu->addOption("Drop");
			}
			else
			{
				message = MENU_ACTIVATE;
			}
			break;

		}
		case RETURN:
		{
			if (parent)
			{
				if (parent->inSubMenu)
				{
					parent->inSubMenu = false;
				}
			}
			else
			{
				message = MENU_RETURN;
			}
		}
		}
	}
	render();
	
}
void MenuInterface::render()
{
	SDL_Rect tmp;
	tmp.w = SCREEN_WIDTH;
	tmp.h = 60 + 20 * numOptions;
	tmp.x = 0;
	tmp.y = 0;
	SDL_FillRect(menuBuffer, NULL, 0xff00ff);
	SDL_FillRect(menuBuffer, &tmp, 0x9900ff);
	tmp.x = 0;
	tmp.y = crSelection * 20 + 30;
	tmp.w = 20;
	tmp.h = 20;
	SDL_FillRect(menuBuffer, &tmp, 0x990000);
	for (int i = 0; i < numOptions; i++)
	{
		menuText.renderText(menuBuffer, 30, 30 + 20 * i, options[i]);
	}
}