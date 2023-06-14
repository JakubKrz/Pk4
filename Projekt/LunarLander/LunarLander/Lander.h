#pragma once

#include <SFML/Graphics.hpp>

class Lander
{
private:
	sf::Sprite sprite;
	sf::Texture texture;

	float speed_x, speed_y;
	float rotationAngle;
	float fuel;

	void initVariables();
	void initSprite();
public:
	Lander(float x = 100.f, float y = 100.f);
	~Lander();

	void update(sf::RenderTarget* target);
	void updateInput();
	void render(sf::RenderTarget* target);
};

