#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "Entity.hpp"
#include "Input.hpp"
#include "RenderWindow.hpp"
#include "Menu.hpp"

class Cursor{
private:
    int posX = 0;
    int posY = 0;
    int cursorWandH = 258;
    int line = 0; //line = 0 payload line   line = 1 about, close and update line
    int column = 0;
    SDL_Rect rectCursor {0, 0, 0, 0};
    void moveCursorX(bool right);

    void refreshPos();
public:
    Cursor();

    void printCursor(RenderWindow render);

    bool checkInputCursor(int value);

    int getPosX(){
        return posX;
    }

    int getPosY(){
        return posY;
    }
};