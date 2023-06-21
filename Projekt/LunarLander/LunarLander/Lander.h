#pragma once

#include <SFML/Graphics.hpp>
#include "Terrain.h"

class Lander
{
private:
	sf::Sprite sprite;
	sf::Texture LanderTexture;

	float speed_x, speed_y;
	int rotationAngle;
	float fuel;
	float maxFuel;

	float acceleration;
	float gravity;
	float fuelConsuption;

	void initVariables();
	void initSprite();
public:
	Lander();
	~Lander();

	void update(sf::RenderTarget* target);
	void updateInput();
	void render(sf::RenderTarget* target);

	bool checkCollision(std::vector<sf::Vector2f> vertices) const;
	void resetPosition(float x = 10.f, float y = 50.f);

	float getLowestPoint() const;
	float getHeight(std::vector<sf::Vector2f> groundPoints) const;//groundpoints prze referencje i const
	float getX() const;
	float getSpeedX() const;
	float getSpeedY() const;
	float getFuel() const;
	int getRotationAngle() const;
	float getMaxFuel() const;
};

