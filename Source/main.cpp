
#include "Drawing.h"
#include "CreatureController.h"
#include "StateControl.h"
#include "ItemTemplates.h"

SDL_Window * Window;
SDL_Surface * Screen;
SDL_Event event;

bool GameRunning = true;



int main(int argc, char **argv)
{

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return 1;
	}
	Window = SDL_CreateWindow("Dungeons of Malice", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	Screen = SDL_GetWindowSurface(Window);
	
	
	Map MyMap(Screen, 64, 64, "Penis");
	MyMap.GenerateCave(2,6,4,3);
	//MyMap.GenerateDungeon();
	Camera MyCamera(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	Renderer MyRenderer(Screen, &MyMap, &MyCamera);
	TextRenderer MyTextRenderer;
	Creature Player(5, 5, 5, 5, "Hero", RACE_HUMAN, T_WARRIOR, 0, 0, false, &MyMap);
	Creature aiOne(5, 5, 5, 5, "shit", RACE_ORC, T_BARBARIAN, 0, 0, true, &MyMap);
	Player.AI = false;
	Player.inventory = new Container;
	Player.inventory->parentCreature = &Player;
	StateControl StateController(&Player,&MyMap);


	StateController.numMobs = 1;
	StateController.creatureList = new Creature*[1];
	StateController.creatureList[0] = &aiOne;

	Player.x = MyMap.entrance_x;
	Player.y = MyMap.entrance_y;
	aiOne.x = Player.x;
	aiOne.y = Player.y;
	MyCamera.Track(&Player);
	MyCamera.tracking = true;

	ItemTemplates Items;
	Items.InitItems();

	Player.inventory->addItem(&Items.itemWeaponMagicSword);
	Player.inventory->addItem(&Items.itemWeaponMagicSword);
	Player.inventory->addItem(&Items.itemWeaponSword);
	Player.inventory->addItem(&Items.itemArmorBreastplate);
	Player.inventory->addItem(&Items.itemPotionHealth);


	while (GameRunning)
	{
		int ev = NOTHING;
		SDL_FillRect(Screen, NULL, 0x00000000);
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_KEYDOWN)
			{


				
				switch (event.key.keysym.sym)
				{
				case SDLK_LEFT:
				{
					if (MyCamera.tracking)
					{
						ev = LEFT;
						MyCamera.x = (Player.x * 64)+32 - (SCREEN_WIDTH / 2);
						MyCamera.y = (Player.y * 64)+32 - (SCREEN_HEIGHT / 2);
					}
					else
					{
						MyCamera.x -= 64;
						
					}		
					break;
				}
				case SDLK_RIGHT:
				{
					if (MyCamera.tracking)
					{
						ev = RIGHT;
						MyCamera.x = (Player.x * 64) + 32 - (SCREEN_WIDTH / 2);
						MyCamera.y = (Player.y * 64) + 32 - (SCREEN_HEIGHT / 2);
					}
					else
					{
						MyCamera.x += 64;
						
					}
					break;
				}
				case SDLK_UP:
				{
					if (MyCamera.tracking)
					{
						ev = UP;
						MyCamera.x = (Player.x * 64) + 32 - (SCREEN_WIDTH / 2);
						MyCamera.y = (Player.y * 64) + 32 - (SCREEN_HEIGHT / 2);
					}
					else
					{
						MyCamera.y -= 64;
						
					}
					break;
				}
				case SDLK_DOWN:
				{
					if (MyCamera.tracking)
					{
						ev = DOWN;
						MyCamera.x = (Player.x * 64) + 32 - (SCREEN_WIDTH / 2);
						MyCamera.y = (Player.y * 64) + 32 - (SCREEN_HEIGHT / 2);
					}
					else
					{
						MyCamera.y += 64;
						
					}
					break;
				}
				case SDLK_z:
				{
					MyCamera.tracking = !MyCamera.tracking;
					break;
				}
				case SDLK_1:
				{
					break;
				}
				case SDLK_2:
				{
					break;
				}
				case SDLK_3:
				{
					break;
				}
				case SDLK_ESCAPE:
				{
					GameRunning = false;
					break;
				}
				case SDLK_i:
				{
					ev = SHOW_INV;
					break;
				}
				case SDLK_g:
				{
					ev = PICK;
					break;
				}
				case SDLK_e:
				{
					ev = USE;
					break;
				}
				case SDLK_r:
				{
					ev = RETURN;
					break;
				}
				}
			}
			
			if (event.type == SDL_QUIT)
				GameRunning = false;
		}

		SDL_FillRect(Screen, NULL, NULL);

		MyRenderer.RenderMap();
		
		MyRenderer.RenderCreature(&Player);
		MyRenderer.RenderCreature(&aiOne);
		StateController.update(ev);
		MyTextRenderer.renderText(Screen, 30, 30, "0 123MATA");
		MyTextRenderer.renderText(Screen, 30, 200, Player.hp);
		MyTextRenderer.renderText(Screen, 30, 250, Player.crtick);
		SDL_Rect tmp;
		tmp.x = 0;
		tmp.y = 0;
		tmp.w = SCREEN_WIDTH;
		tmp.h = SCREEN_HEIGHT;
		if (StateController.viewInventory)
		{
			if (StateController.invMan.invMenu.subMenu && StateController.invMan.invMenu.inSubMenu)
			{
				SDL_BlitScaled(StateController.invMan.invMenu.subMenu->menuBuffer, NULL, Screen, NULL);
			}
			else
			{
				SDL_BlitScaled(StateController.invMan.invMenu.menuBuffer, NULL, Screen, NULL);
			}
			
		}
			

		//Text(Screen, 50, 50, StateController.ticks);
		SDL_UpdateWindowSurface(Window);
		
	}
	
	
	
	//DumpItems();
	SDL_FreeSurface(Screen);
	SDL_DestroyWindow(Window);
	SDL_Quit();

	return 0;
}

