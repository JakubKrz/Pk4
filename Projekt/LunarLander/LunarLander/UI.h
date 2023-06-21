#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class UI
{
private:
	sf::Font font;
	sf::Text text;

public:
	UI();
	~UI();
	void render(sf::RenderTarget* target);
	void update(sf::RenderTarget* target, float height);
};

