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

    //this->terrain.render(this->window);
    this->lander.render(this->window);//przesylanie window zeby sprawdzic czy nie wyszedl za okno

    this->window->display();
}

void Game::update()
{
    this->updateEvents();

    this->lander.update(this->window);
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
