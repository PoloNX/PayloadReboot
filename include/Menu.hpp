#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "RenderWindow.hpp"

class Menu
{
private:
    const int vertical = 720;
    const int horizontal = 1280;
    SDL_Texture* tTitle;
    SDL_Texture* tInfo;
    SDL_Texture* tExit;
    SDL_Texture* tUpdate;
    SDL_Texture* tAMS;
    SDL_Texture* tHekate;
    SDL_Texture* tLockpick;
    SDL_Texture* tUdpih;
    RenderWindow window;
    SDL_Rect rectTemplate;
public:
	Menu(RenderWindow window);

    void printAbout();
    void printMenu();
};
