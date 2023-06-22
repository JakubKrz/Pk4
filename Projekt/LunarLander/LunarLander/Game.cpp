#include "Game.h"

//Private
void Game::initVariables()
{
    this->window = nullptr;
    this->currentState = GameState::Playing;
}

void Game::initWindow()
{
    this->video = sf::VideoMode::getDesktopMode();

    this->window = new sf::RenderWindow(this->video, "Lunar Lander", sf::Style::Titlebar | sf::Style::Close | sf::Style::Fullscreen);
    this->window->setFramerateLimit(60);
}

//Public
Game::Game()
{
    this->initVariables();
    this->initWindow();
}

Game::~Game()
{
    delete this->window;
}

const bool Game::windowIsOpen() const
{
    return this->window->isOpen();
}


void Game::render()
{
    this->window->clear();

    switch (this->currentState)
    {
    case GameState::Menu:
        // Render menu UI elements
        this->UI.renderMenu(this->window);
        break;

    case GameState::Playing:
        // Render in-game UI elements
        //
        this->terrain.render(this->window);
        this->lander.render(this->window);//przesylanie window zeby sprawdzic czy nie wyszedl za okno
        this->UI.render(this->window);

        break;

    case GameState::GameOver:
        // Render game over UI elements
       // 
        break;
    }


    this->window->display();
}

void Game::update()
{
//zmienic odpowidnie dla kadzdego stanu

    switch (this->currentState) 
    {
    case GameState::Menu:
        this->updateEventsMenu();
            break;

    case GameState::Playing:
        this->updateEventsGame();
        this->lander.update(this->window);
        this->UI.update(this->window, lander, terrain.GetGroundPoints());
        if (this->lander.outOfScreen())//Reset positionif out of screen
        {
            this->lander.resetPosition();
        }
        //Reset position if crashed and fuel>0
        //TO DO: check if landing was succesful and add points
        if (this->lander.checkCollision(this->terrain.GetGroundPoints()))
        {
            lander.landingUpdate(this->terrain.getLandingPads());
            if (this->lander.getFuel() > 0)
            {
                //TO DO : czy teren jest plaski?
                this->lander.resetPosition();
                this->terrain.generateGround();
                //TO DO: Pasue for some time and show text
            }
            else
            {
                //TO DO : Game over
                //zapisac punkty a nastepnie ustawic na 0
                this->gameOver();
            }
        }
        break;

    case GameState::GameOver:
        //
        break;
    }

}

void Game::updateEventsGame()
{

    while (this->window->pollEvent(this->event))
    {
        switch (this->event.type)
        {
        case sf::Event::Closed:
            this->window->close();
            break;
        case sf::Event::KeyPressed:
            if (this->event.key.code == sf::Keyboard::Escape)
                this->window->close();
            break;
        }
    }
}

void Game::gameOver()//TO DO: dopisac reszte zpisywanie do pliku , filesystem, przejscei do menu
{
    //save score
    //wyswietlic game over , your score:xxxx  (to moze w stanie gry gmaeover)
    // wait for any acction 
    //set score to 0 , reset lander
    //set gamestate to menu
    this->changeGameState(GameState::Menu);// tymczasowe
   // this->window->close();//remove
}

void Game::changeGameState(Game::GameState newState)
{
   this->currentState = newState;
    
}

void Game::updateEventsMenu()
{
    while (this->window->pollEvent(this->event))
    {
        switch (this->event.type)
        {
        case sf::Event::Closed:
            this->window->close();
            break;

        case sf::Event::KeyPressed:
            switch (this->event.key.code)
            {
            case sf::Keyboard::Escape:
                this->window->close();
                break;

            case sf::Keyboard::Up:
                this->UI.moveUp();
                break;

            case sf::Keyboard::Down:
                this->UI.moveDown();
                break;
            case sf::Keyboard::Enter:
                this->select(this->UI.getSelectedItem());
                break;
            }

        }
    }
}

void Game::select(int item)
{
    switch (item)
    {
    case 0:
        this->lander.reset();//TO DO: generate terrain random
        this->changeGameState(GameState::Playing);
        break;
    case 1:
        //tutaj wyswietlac wyniki
        break;
    case 2:
        this->window->close();
    }
}
