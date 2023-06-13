#pragma once
#include <iostream>
#include "Lander.h"

class Game
{
private:
	
	sf::RenderWindow* window;
	sf::VideoMode video;
	sf::Event event;

	Lander lander;

	void initVariables();
	void initWindow();

public:

	Game();
	~Game();

	const bool windowIsOpen() const;

	void render();
	void update();
	void updateEvents();
};

	