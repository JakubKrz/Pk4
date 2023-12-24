#include "Game.h"

//Private
void Game::initVariables()
{
    this->window = nullptr;
    this->currentState = GameState::Menu;
    this->input = "";
}

void Game::initWindow()
{
    this->video = sf::VideoMode::getDesktopMode();

    this->window = new sf::RenderWindow(this->video, "Lunar Lander", sf::Style::Titlebar | sf::Style::Close | sf::Style::Fullscreen);
    this->window->setFramerateLimit(60);
    this->window->setMouseCursorVisible(false);
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
        this->UI.renderMenu(this->window);
        
        break;

    case GameState::Playing:
        this->terrain.render(this->window);
        this->lander.render(this->window);
        this->UI.render(this->window);

        break;

    case GameState::ShowScores:
        this->UI.renderScores(this->window);
       
        break;

    case GameState::GameOver:
        this->UI.renderGameOver(this->window, this->input,this->lander.getPoints());
        this->lander.render(this->window);
        this->terrain.render(this->window);

        break;
    }


    this->window->display();
}

void Game::update()
{
    switch (this->currentState) 
    {

    case GameState::Menu:
        this->updateEventsMenu();

            break;

    case GameState::Playing:
        this->updateEventsGame();
        this->lander.update(this->window);
        this->UI.update(this->window, lander, terrain.GetGroundPoints());

        if (this->lander.outOfScreen())//Reset position if out of screen
        {
            this->lander.resetPosition();
        }

        if (this->lander.checkCollision(this->terrain.GetGroundPoints()))//checking for collision
        {
            if (!lander.landingUpdate(this->terrain.getLandingPads()))
            {
                this->window->clear();
                this->UI.crash(this->window);
                this->UI.render(this->window);
                this->lander.render(this->window);
                this->terrain.render(this->window);
                this->window->display();
                sf::sleep(sf::Time(sf::seconds(2.0f)));
            }
            else
            {
                this->UI.succesfullLanding(this->window);
                this->window->display();
                sf::sleep(sf::Time(sf::seconds(2.0f)));
            }

            if (this->lander.getFuel() > 0)
            {
                this->lander.resetPosition();
                this->terrain.generateGround();
            }
            else
            {
                this->input.clear();
                this->changeGameState(GameState::GameOver);
            }
        }

        break;

    case GameState::ShowScores:
        this->updateEventScore();
  
        break;

    case GameState::GameOver:
        this->updateGameOver();
       
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
            {
                this->changeGameState(GameState::Menu);
            }

            break;
        }
    }
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

//Select item form menu
void Game::select(int item)
{
    switch (item)
    {
    case 0:
        this->terrain.generateGround();
        this->lander.reset();
        this->changeGameState(GameState::Playing);
        break;
    case 1:
        this->UI.loadScores(this->fileManager.readScore());
        this->changeGameState(GameState::ShowScores);
        break;
    case 2:
        this->window->close();
    }
}

//Change state back to menu if esc is pressed
void Game::updateEventScore()
{
    while (this->window->pollEvent(this->event))
    {
        switch (this->event.type)
        {
        case sf::Event::Closed:
            this->window->close();
            break;
        case sf::Event::KeyPressed:
            if (this->event.key.code == sf::Keyboard::Escape || this->event.key.code == sf::Keyboard::Enter)
                this->changeGameState(GameState::Menu);
            break;
        }
    }
}

//display gameoverUI and checks for valid name
void Game::updateGameOver()
{
    while (this->window->pollEvent(this->event))
    {
        switch (this->event.type)
        {
        case sf::Event::Closed:
            this->window->close();
            break;

        case sf::Event::TextEntered:
            if (this->event.text.unicode == '\b')
            {
                if (!this->input.empty())
                {
                    this->input.pop_back();
                }
            }
            else if (this->event.text.unicode == '\r')
            {
            }
            else
            {
                this->input += event.text.unicode;
            }
            break;

        case sf::Event::KeyPressed:
            if (this->event.key.code == sf::Keyboard::Escape)
            {
                this->UI.setWrongNick("");
                this->changeGameState(GameState::Menu);
            }
            else if (this->event.key.code == sf::Keyboard::Enter)
            {
                if (this->fileManager.checkName(this->input))
                {
                    this->fileManager.writeScore(this->input, this->lander.getPoints());
                    this->input = "";
                    this->UI.setWrongNick("");
                    this->changeGameState(GameState::Menu);
                }
                else
                {
                   this->input = "";
                   this->UI.setWrongNick("Wrong nick");
                }
            }
            break;

        }
    }
}

void Game::changeGameState(Game::GameState newState)
{
    this->currentState = newState;
}