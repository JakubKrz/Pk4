#pragma once
#include <SFML/Graphics.hpp>
#include <random>

class Terrain
{
private:
	std::vector<sf::Vector2f> groundPoints;
	sf::VertexArray groundShape;
	sf::Color groundColor;
	//groundpoints variables
	size_t width;
	size_t size;
	//landing points variables
	std::vector<std::pair<size_t, size_t>> landingPads;
	size_t landingPadWidth;
	sf::Font font;
	sf::Text multiplier[3];


	void initShape();
	void generatePoints();
	void initVariables();
	void generateLandingPads();
	void initMultiplier();
public:
	Terrain();

	void generateGround();
	void render(sf::RenderTarget* target);
	const std::vector<sf::Vector2f>& GetGroundPoints() const;
	const sf::VertexArray& GetGroundShape() const;
	const std::vector<std::pair<size_t, size_t>>& getLandingPads() const;
};