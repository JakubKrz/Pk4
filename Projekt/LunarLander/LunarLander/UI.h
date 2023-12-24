#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

#include "Lander.h"

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
	//score
	std::vector<sf::Text> results;
	//Game over
	sf::Text nickname;
	sf::Text gameOver;
	sf::Text points;
	sf::Text message;
	sf::Text wrongNick;

	sf::Text crashMessage;
	sf::Text sucessfulLandingMessage;

	void initMenuOptions();
	void initGameUI();
	void initGameOver();

public:
	UI();
	//in-Game
	void update(sf::RenderTarget* target, const Lander& lander, const std::vector<sf::Vector2f>& groundPoints);
	void render(sf::RenderTarget* target);
	void succesfullLanding(sf::RenderTarget* target);
	void crash(sf::RenderTarget* target);
	//Menu
	void renderMenu(sf::RenderTarget* target);
	void moveUp();
	void moveDown();
	int getSelectedItem();
	//Scores
	void loadScores(const std::vector<std::pair<std::string, int>>& scores);
	void renderScores(sf::RenderTarget* target);
	//Gameover
	void renderGameOver(sf::RenderTarget* target, std::string name, int score);
	void setWrongNick(std::string message);
};