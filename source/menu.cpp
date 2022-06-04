#include <SDL.h>
#include <SDL_image.h>
#include <SDL2_gfxPrimitives.h>
#include <SDL_ttf.h>
#include <vector>
#include <iostream>

#include "Menu.hpp"
#include "Math.hpp"
#include "RenderWindow.hpp"
#include "Cursor.hpp"
#include "Input.hpp"



SDL_Point getsize(SDL_Texture* texture) {
	SDL_Point size;
	SDL_QueryTexture(texture, NULL, NULL, &size.x, &size.y);
	return size;
}

Menu::Menu(RenderWindow pWindow)
{
    window = pWindow;

    //Create texture
    tTitle = window.loadString("PayloadReboot");
    chdir("romfs:/");
    tExit = window.loadTexture("gfx/exit.png");
    tInfo = window.loadTexture("gfx/info.png");
    tHekate = window.loadTexture("gfx/hekate.png");
    tAMS = window.loadTexture("gfx/fusee.png");
    tLockpick = window.loadTexture("gfx/lockpick.png");
    tLakka = window.loadTexture("gfx/lakka.png");

    //Create rect
    /*rectHekate = { 107, 0, 258, 258};
    rectHekate.y = vertical / 2 - rectHekate.w / 2 - 20;

    rectAms = { rectHekate.x + rectHekate.w + 14, 0, 258, 258};
    rectAms.y = vertical / 2 - rectAms.w / 2 - 20;

    rectLockpick = { rectAms.x + rectAms.w +14, 0, 258, 258};
    rectLockpick.y = vertical / 2 - rectLockpick.w / 2 - 20;

    rectLakka = { rectLakka.x + rectLakka.w +  14, 0, 258, 258};
    rectLakka.y = vertical / 2 - rectLakka.w / 2 - 20;*/

    rectTemplate = {105, vertical / 2 - 258 / 2 - 20, 258, 258};
}


void Menu::printMenu()
{
    std::vector<Entity> vEntity {};
    std::vector<Entity> vEntityCursor {};

    SDL_Point size = getsize(tTitle);
    vEntity.push_back(Entity  (Vector2f(horizontal / 2 - size.x / 2, 0), tTitle, size.x, size.y, 0, 0));

    /*REBOOT TEMPLATE*/
    for (int i = 0; i < 4; ++i)
    {
        window.fillRect(rectTemplate, 80, 80, 80);
        rectTemplate.x += rectTemplate.w + 14;
    }
    rectTemplate.x = 105;

    /*ICONS HEKATE AMS...*/
    vEntityCursor.push_back(Entity (Vector2f(rectTemplate.x, rectTemplate.y), tHekate, 258, 258, 0, 0));
    vEntityCursor.push_back(Entity (Vector2f(rectTemplate.x + rectTemplate.w + 14, rectTemplate.y), tAMS, 258, 258, 0, 0));
    vEntityCursor.push_back(Entity (Vector2f(rectTemplate.x + (rectTemplate.w + 14) * 2, rectTemplate.y), tLockpick, 258, 258, 0, 0));
    //vEntityCursor.push_back(Entity (Vector2f(rectTemplate.x + (rectTemplate.w + 14) * 3, rectTemplate.y), tLakka, 258, 258, 0, 0));

    /*CIRCLE BEHIND SMALL ICONS*/
    window.drawCircleBehindIcons();

    /*BUTTON UNDER ICONS*/
    size = getsize(tExit);
    vEntity.push_back(Entity (Vector2f(horizontal / 2 - size.x * 1.5, 550), tExit, size.x, size.y, 0, 0));

    size = getsize(tInfo);
    vEntity.push_back(Entity (Vector2f(horizontal / 2 + size.x * 0.5, 550), tInfo, size.x, size.y, 0, 0));


    for (auto i : vEntity)
    {
        window.render(i, 1);
    }

    for (auto i : vEntityCursor)
    {
        window.render(i, 1);
    }

}

void Menu::printAbout(){
    bool isOpen = true;
    SDL_Event eventAbout;
    std::vector<Entity> vEntity {};

    SDL_Rect rect {320, 180, 640, 360};
    window.fillRect(rect, 80, 80, 80);

    //The code is disgusting but idk how to do better because \n doesn't work 

    SDL_Texture* tCredit = window.loadString("Thanks to :");
    SDL_Texture* tSciresM = window.loadString("- SciresM for fusee");
    SDL_Texture* tCTCaer = window.loadString("- CTCaer for hekate");
    SDL_Texture* tshchmue = window.loadString("- shchmue for lockpick");
    SDL_Texture* tpressA = window.loadString("- PRESS A TO EXIT !");

    SDL_Point size = getsize(tCredit);
    vEntity.push_back(Entity(Vector2f(340, 200), tCredit, size.x, size.y , 0, 0));
    size = getsize(tSciresM);
    vEntity.push_back(Entity(Vector2f(340, 230), tSciresM, size.x, size.y , 0, 0));
    size = getsize(tCTCaer);
    vEntity.push_back(Entity(Vector2f(340, 260), tCTCaer, size.x, size.y , 0, 0));
    size = getsize(tshchmue);
    vEntity.push_back(Entity(Vector2f(340, 290), tshchmue, size.x, size.y , 0, 0));
    size = getsize(tpressA);
    vEntity.push_back(Entity(Vector2f(340, 350), tpressA, size.x, size.y , 0, 0));

    for (auto i : vEntity){
            window.render(i, 1);
    }

    window.display();

    while (isOpen){
        while (SDL_PollEvent(&eventAbout)){
            if (eventAbout.type == SDL_JOYBUTTONDOWN){
                if (eventAbout.jbutton.button == 0) //button A
                {
                    return;
                }
            }
        }
    }
}