#pragma once

#include <SFML/Graphics.hpp>

class Lander
{
private:
	sf::RectangleShape shape;

	float speed_x, speed_y;
	float rotationAngle;
	float fuel;

	void initVariables();
	void initShape();
public:
	Lander(float x = 0.f, float y = 0.f);
	~Lander();

	void update(sf::RenderTarget* target);
	void updateInput();
	void render(sf::RenderTarget* target);
};

