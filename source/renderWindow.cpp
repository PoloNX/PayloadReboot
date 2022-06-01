#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>

#include "Cursor.hpp"
#include "RenderWindow.hpp"
#include "Entity.hpp"

RenderWindow::RenderWindow(const char* p_title, int p_w, int p_h)
	:window(NULL), renderer(NULL)
{
	window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, p_w, p_h, SDL_WINDOW_SHOWN);

	if (window == NULL)
	{
		std::cout << "HEY... Window failed to init. SDL_ERROR: " << SDL_GetError() << std::endl;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

int RenderWindow::getRefreshRate()
{
	int displayIndex = SDL_GetWindowDisplayIndex(window);

	SDL_DisplayMode mode;
	SDL_GetDisplayMode(displayIndex, 0, &mode);

	return mode.refresh_rate;
}

SDL_Texture* RenderWindow::loadTexture(const char* p_filePath)
{
	SDL_Texture* texture = NULL;
	texture = IMG_LoadTexture(renderer, p_filePath);

	if (texture == NULL)
		std::cout << "HEY... Window failed to load texture. SDL_ERROR: " << SDL_GetError() << std::endl;

	return texture;
}

SDL_Texture* RenderWindow::loadString(const char* text)
{
	SDL_Texture* texture = NULL;
	SDL_Surface* surface = NULL;

	chdir("romfs:/");

	TTF_Font* font = TTF_OpenFont("data/BerlinSansFB.ttf", 25);

	surface = TTF_RenderText_Blended(font, text, SDL_Color{255, 255, 255, 255});
	texture = SDL_CreateTextureFromSurface(renderer, surface);

	if (texture == NULL)
		std::cout << "HEY... Window failed to load texture. SDL_ERROR: " << SDL_GetError() << std::endl;

	return texture;
}

void RenderWindow::cleanup()
{
	SDL_DestroyWindow(window);
}

void RenderWindow::clear()
{
	SDL_SetRenderDrawColor(renderer, 41, 41, 41, 255);
	SDL_RenderClear(renderer);
}

void RenderWindow::render(Entity& p_entity, int multiply)
{
	SDL_Rect src{};
	src.x = p_entity.getCurrentFrame().x;
	src.y = p_entity.getCurrentFrame().y;
	src.w = p_entity.getCurrentFrame().w;
	src.h = p_entity.getCurrentFrame().h;

	SDL_Rect dst{};
	dst.x = p_entity.getPos().x;
	dst.y = p_entity.getPos().y;
	dst.w = p_entity.getCurrentFrame().w * multiply;
	dst.h = p_entity.getCurrentFrame().h * multiply;

	SDL_RenderCopy(renderer, p_entity.getTex(), &src, &dst);
}

void RenderWindow::display()
{
	SDL_RenderPresent(renderer);
}

void RenderWindow::renderRect(SDL_Rect rect)
{
	//SDL_SetRenderDrawColor(renderer, 25, 145, 218, 255);
	//SDL_RenderDrawRect(renderer, &rect);
	
	/*Cursor cursor;
	for (int i = 0; i < 5; ++i)
	{
		rectangleRGBA(renderer, cursor.getPosX() + 258 + i, cursor.getPosY() - i, cursor.getPosX() - i, cursor.getPosY() + 258 + i, 25, 145, 218, 255);
	}*/

	SDL_SetRenderDrawColor(renderer, 25, 145, 218, 255);
	for (int i = 0; i < 5; ++i){
		rect.w += 2;
		rect.h += 2;
		rect.x -= 1;
		rect.y -= 1;
		SDL_RenderDrawRect(renderer, &rect);
	}
	
}

void RenderWindow::drawCircleBehindIcons()
{
	filledCircleRGBA(renderer, 1280 / 2 + 50, 575, 38, 80, 80, 80, 255);
	filledCircleRGBA(renderer, 1280 / 2 - 50, 575, 38, 80, 80, 80, 255);
}