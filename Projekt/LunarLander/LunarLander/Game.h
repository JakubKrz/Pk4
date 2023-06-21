#pragma once
#include <iostream>
#include "Lander.h"
#include "Terrain.h"
#include "UI.h"

class Game
{
private:

	sf::RenderWindow* window;
	sf::VideoMode video;
	sf::Event event;

	Lander lander;
	Terrain terrain;
	UI text;

	void initVariables();
	void initWindow();

public:

	Game();
	~Game();

	const bool windowIsOpen() const;

	void render();
	void update();
	void updateEvents();
	void gameOver();
};

