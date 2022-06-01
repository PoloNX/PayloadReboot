#include <SDL.h>
#include <SDL_image.h>

#include "Entity.hpp"


Entity::Entity(Vector2f p_pos, SDL_Texture* p_tex, int w, int h, int x, int y)
	:pos(p_pos), tex(p_tex)
{
	currentFrame.x = x;
	currentFrame.y = y;
	currentFrame.w = w;
	currentFrame.h = h;
}

Entity::Entity(Vector2f p_pos, SDL_Texture* p_tex, int w, int h, int x, int y, int nFrames, int mSpeed)
	:pos(p_pos), tex(p_tex)
{
	frames = nFrames;
	speed = mSpeed;
	currentFrame.x = currentFrame.w * static_cast<int>((SDL_GetTicks() / speed) % frames);
	currentFrame.y = y;
	currentFrame.w = w;
	currentFrame.h = h;
}

SDL_Texture* Entity::getTex()
{
	return tex;
}

Vector2f& Entity::getPos()
{
	return pos;
}

SDL_Rect Entity::getCurrentFrame()
{
	return currentFrame;
}

Vector2f& Entity::addPos()
{
	pos = Vector2f(10, 10);
	return pos;
}
