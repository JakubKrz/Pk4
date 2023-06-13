#include "Game.h"

int main()
{
    Game game;

    while (game.windowIsOpen())
    {
        //update
        game.update();
        //render           
        game.render();
        
    }

    return 0;
}