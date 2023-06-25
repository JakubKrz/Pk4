#pragma once
#include <iostream>

#include "Lander.h"
#include "Terrain.h"
#include "UI.h"
#include "FileManager.h"


class Game
{
private:
	enum class GameState {
		Menu,
		Playing,
		GameOver,
		ShowScores
	};
	GameState currentState;
	UI UI;
	FileManager fileManager;

	sf::RenderWindow* window;
	sf::VideoMode video;
	sf::Event event;

	Lander lander;
	Terrain terrain;

	std::string input;

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
	void updateEventScore();
	void updateGameOver();
};

