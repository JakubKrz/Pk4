#pragma once

#include <SFML/Graphics.hpp>
#include "Terrain.h"

class Lander
{
private:
	sf::Sprite sprite;
	sf::Texture LanderTexture;

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
	float getX();
	float getLowestPoint();
	bool checkCollision(std::vector<sf::Vector2f> vertices);
};

