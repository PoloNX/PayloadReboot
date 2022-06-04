#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "Entity.hpp"
#include "Cursor.hpp"
#include "Input.hpp"
#include "RenderWindow.hpp"
#include "Reboot.hpp"

Cursor::Cursor()
{
    posX = 105;
    posY = 720 / 2 - 258 / 2 - 20;
}

void Cursor::moveCursorX(bool right)
{
    if (right){
        ++column;
    }

    else{
        --column;
    }
}

int Cursor::checkInputCursor(int value)
{
    std::cout << "dans check input\n";

    if (value == 14 or value == 18) //HidNpadButton_Right and HidNpadButton_StickLRight
    {
        moveCursorX(true);
        std::cout << "dans move right\n";
    }

    else if (value == 12 or value == 16) //HidNpadButton_Left and HidNpadButton_StickLLeft
    {
        moveCursorX(false);
        std::cout << "dans move left\n";
    }

    else if (value == 13 or value == 15 or value == 17 or value == 19) //HidNpadButton_Up and HidNpadButton_Down and HidNpadButton_StickLUp and HidNpadButton_StickLDown
    {
        if (line == 0){
            posY = 537; //Cuz it's cool 
            if (column > -1 and column < 2){   //for ams and hekate
                posX = 1280 / 2 - 75;
                column = 0;
            }
            else{   //other
                posX = 1280 / 2;
                column = 1;
            }
            cursorWandH = 76;
            line = 1;
        }
            
        else{
            if (column == 0){   //for exit
                column = 1;
            }
            else{   //for about
                column = 2;
            }
            posY = 720 / 2 - 258 / 2 - 20;
            cursorWandH = 258;
            line = 0;
        }
    } 

    else if (value == 0) //HidNpadButton_A (reboot)
    {
        std::cout << "dans a\n";
        if (line == 0){
            Reboot reboot;
            reboot.rebootNow(column);
        }

        else if (line == 1 and column == 1){
            return 1;
        }

        else if (line == 1 and column == 0){
            return 2;
        }

    }    

    return false;
}

void Cursor::cursorRecenter()
{
    if (line == 0){
        if (column > 3){
            column = 0;
        }
        if (column < 0){
            column = 3;
        }
    }

    if (line == 1){
        if (column > 1){
            column = 0;
        }
        if (column < 0){
            column = 1;
        }
    }
}

void Cursor::printCursor(RenderWindow render)
{
    cursorRecenter();
    refreshPos();
    if (line == 0){
        rectCursor = {posX, posY, cursorWandH, cursorWandH};
        render.renderRect(rectCursor);
    }

    else if (line == 1){
        render.renderCursorCircle(column);
    }
}

void Cursor::refreshPos(){
    if (line == 0){
        posX = 105 + column * (258 + 14);
    }

    else{
        posX = 552 + column * (100);
    }
}






