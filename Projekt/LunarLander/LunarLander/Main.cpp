#include "Game.h"

int main()
{
    Game game;
    //TO DO : Menu (przeniesc tutaj tworzenie okna, i stan gry po przegranej
    
    while (game.windowIsOpen())
    {
        //update
        game.update();
        //render           
        game.render();

    }

    return 0;
}