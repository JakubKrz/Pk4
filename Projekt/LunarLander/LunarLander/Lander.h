#pragma once

#include <SFML/Graphics.hpp>
#include "Terrain.h"

class Lander
{//TO DO: animacje silnika ,  ustawic model ktorego nogi nie wykraczaja poza reszte
private:
	sf::Sprite sprite;
	sf::Texture LanderTexture;

	float speed_x, speed_y;
	int rotationAngle;
	int rotationValue;
	float maxFuel;

	float fuel;
	int points;

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
	bool outOfScreen();
	void resetPosition(float x = 30.f, float y = 150.f);
	bool landingUpdate(std::vector<std::pair<size_t, size_t>> landingPads);
	void reset();
//	TO DO : gettery & i const
	float getLowestPoint() const;
	float getHeight(std::vector<sf::Vector2f> groundPoints) const;//groundpoints prze referencje i const
	float getX() const;
	float getSpeedX() const;
	float getSpeedY() const;
	float getFuel() const;
	int getRotationAngle() const;
	float getMaxFuel() const;
	int getPoints() const;
};

