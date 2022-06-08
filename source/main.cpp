#include <iostream>
#include <switch.h>

#include "RenderWindow.hpp"
#include "Menu.hpp"
#include "Reboot.hpp"
#include "Cursor.hpp"

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL2_gfxPrimitives.h>

void init();

int main(int argc, char *argv[])
{
    init();

	std::cout << "1\n";
  
    RenderWindow window("PayloadReboot", 1280, 720);
    Menu menu (window);
	Cursor cursor;
	Input input;

	SDL_Event event;
	int inputValue = -1;
	int inputcheck = 0;

    bool isOpen = true;

    while (isOpen)
	{
		//input.checkInput();

		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
				case SDL_JOYBUTTONDOWN:
					inputValue = event.jbutton.button;
					inputcheck = cursor.checkInputCursor(inputValue);
					if(inputcheck == 1)
					{
						menu.printAbout();
					}
					else if(inputcheck == 2)
					{
						isOpen = false;
					}
				
				default:
					inputValue = -1;
			}
		}

		window.clear();

        menu.printMenu();

		Reboot reboot;
		//reboot.rebootNow(3);

		cursor.printCursor(window);

		window.display();

		SDL_Delay(1000 / window.getRefreshRate());
	}

	SDL_Quit();
	IMG_Quit();
	TTF_Quit();
	return 0;
}

void init()
{
    socketInitializeDefault();
    nxlinkStdio();  //redirect cout/cer to tcp

    if (SDL_Init(SDL_INIT_VIDEO) > 0)
	{
		std::cout << "HEY... SDL_Init HAS FAILED. SDL_ERROR: " << SDL_GetError() << std::endl;
	}

	if (!(IMG_Init(IMG_INIT_PNG)))
	{
		std::cout << "HEY... IMG_Init HAS FAILED. SDL_ERROR: " << IMG_GetError() << std::endl;
	}

	if (!(TTF_Init()))
	{
		std::cout << "HEY... TTF_Init HAS FAILED. SDL_ERROR: " << TTF_GetError() << std::endl;
	}

    std::cout << "after ttf\n";

    SDL_InitSubSystem(SDL_INIT_EVERYTHING); //Some init 
    SDL_JoystickEventState(SDL_ENABLE); //Joystick
    SDL_JoystickOpen(0);    //Open joystick
    romfsInit();    //Init of romfs
}
