#include "Game.h"

int main()
{
    Game game;
    //gettery zamieniac

    while (game.windowIsOpen())
    {
            //update
            game.update();
            //render           
            game.render();
    }

    return 0;
}