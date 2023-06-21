#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Lander.h"

class UI
{
private:
	sf::Font font;
	std::vector<sf::Text> texts;
	sf::RectangleShape LanderFuelBar;
	sf::RectangleShape LanderFuelBarBack;

public:
	UI();
	~UI();
	void render(sf::RenderTarget* target);
	void update(sf::RenderTarget* target, const Lander& lander,const std::vector<sf::Vector2f>& groundPoints);
};

