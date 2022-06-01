#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL2_gfxPrimitives.h>
#include <iostream>

#include "Entity.hpp"

class RenderWindow
{
public:
	RenderWindow(const char* p_title, int p_w, int p_h);
	RenderWindow(){}
	
	SDL_Texture* loadTexture(const char* p_filePath);
	SDL_Texture* loadString(const char* text);

	SDL_Renderer* getRenderer(){
		return renderer;
	}

	int getRefreshRate();

	void cleanup();
	void clear();
	void render(Entity& p_entity, int multiply);
	void renderRect(SDL_Rect rect);

	void fillRect(SDL_Rect rect, int r, int g, int b)
	{
		SDL_SetRenderDrawColor(renderer, r, g, b, 255);
		SDL_RenderFillRect(renderer, &rect);
	}
	void display();
	int horizontal = 0;
	int vertical = 0;

	void drawCircleBehindIcons();

private:
	SDL_Window* window;
	SDL_Renderer* renderer;


};