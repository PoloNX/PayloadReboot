#pragma once
#include <SDL.h>
#include <SDL_image.h>

#include "Cursor.hpp"

class Input{
private:
    SDL_Event event;
    int inputValue = -1;
public:
    Input();
    int checkInput();
    int getInputValue(){
        return inputValue;
    }

};