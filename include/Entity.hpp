#pragma once
#include <SDL.h>
#include <SDL_image.h>

#include "Math.hpp"

class Entity
{
private:
	Vector2f pos = Vector2f(50, 50);

	bool animated = false;
	int frames = 0;
	int speed = 100;
	SDL_Rect currentFrame;
	SDL_Texture* tex;
	int t_x = 0;
	int p_x = 0;
	int p_y = 0;

public:
	Entity(Vector2f p_pos, SDL_Texture* p_tex, int w, int h, int x, int y);

	Entity(Vector2f p_pos, SDL_Texture* p_tex, int w, int h, int x, int y, int nFrames, int mSpeed);

	Vector2f& getPos();

	Vector2f& addPos();

	SDL_Texture* getTex();
	SDL_Rect getCurrentFrame();
};
