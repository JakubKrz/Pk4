#include "Game.h"

//Private
void Game::initVariables()
{
    this->window = nullptr;
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

    this->terrain.render(this->window);
    this->lander.render(this->window);//przesylanie window zeby sprawdzic czy nie wyszedl za okno
    this->text.render(this->window);

    this->window->display();
}

void Game::update()
{
    this->updateEvents();

    this->lander.update(this->window);

    this->text.update(this->window,lander, terrain.GetGroundPoints());
    //Reset position if crashed and fuel>0
    //TO DO: check if landing was succesful and add points
    if (lander.checkCollision(terrain.GetGroundPoints()))
    {
        if (lander.getFuel() > 0)
        {
            //TO DO : game.landedSafe(); && game.addPoints();
            lander.resetPosition();
        }
        else
        {
            //TO DO : Game over
        }
    }

}

void Game::updateEvents()
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
