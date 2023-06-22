#pragma once
#include <iostream>
#include "Lander.h"
#include "Terrain.h"
#include "UI.h"

class Game
{
private:
	enum class GameState {
		Menu,
		Playing,
		GameOver
	};
	GameState currentState;
	UI UI;

	sf::RenderWindow* window;
	sf::VideoMode video;
	sf::Event event;

	Lander lander;
	Terrain terrain;

	void initVariables();
	void initWindow();

public:

	Game();
	~Game();

	const bool windowIsOpen() const;

	void render();
	void update();
	void updateEventsGame();
	void gameOver();
	void changeGameState(Game::GameState newState);
	void updateEventsMenu();
	void select(int item);
};

