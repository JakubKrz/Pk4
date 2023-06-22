#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Lander.h"
//TO DO :przeniesc wartosci w odpowiednie miejsce na ekranie (ewentualnie stopien nachylenia zrobic
//game ui
class UI
{
private:
//font
	sf::Font font;
	//in game
	std::vector<sf::Text> gameTexts;
	sf::RectangleShape LanderFuelBar;
	sf::RectangleShape LanderFuelBarBack;
	//menu
	sf::Text menuOptions[3];
	int selectedItem;

	void initMenuOptions();
	void initGameUI();

public:
	UI();
	~UI();

	void renderMenu(sf::RenderTarget* target);
	void moveUp();
	void moveDown();
	int getSelectedItem();

	void render(sf::RenderTarget* target);
	void update(sf::RenderTarget* target, const Lander& lander,const std::vector<sf::Vector2f>& groundPoints);

};

