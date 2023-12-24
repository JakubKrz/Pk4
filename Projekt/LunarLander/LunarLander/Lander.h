#pragma once

#include <SFML/Graphics.hpp>

class Lander
{
private:
	sf::Sprite landerSprite;
	sf::Texture LanderTexture;

	float speed_x, speed_y;
	int rotationAngle;
	int rotationValue;
	float maxFuel;
	float fuel;
	int points;
	float acceleration;
	float gravity;
	float fuelConsumption;

	void initSprite();
public:
	Lander();

	void update(sf::RenderTarget* target);
	void updateInput();
	void render(sf::RenderTarget* target);

	bool checkCollision(const std::vector<sf::Vector2f>& vertices) const;
	bool outOfScreen();
	void resetPosition(float x = 30.f, float y = 150.f);
	bool landingUpdate(const std::vector<std::pair<size_t, size_t>>& landingPads);
	void reset();

	float getLowestPoint() const;
	float getHeight(const std::vector<sf::Vector2f>& groundPoints) const;
	float getX() const;
	float getSpeedX() const;
	float getSpeedY() const;
	float getFuel() const;
	int getRotationAngle() const;
	float getMaxFuel() const;
	int getPoints() const;
};