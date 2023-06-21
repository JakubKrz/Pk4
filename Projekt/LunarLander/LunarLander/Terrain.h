#pragma once
#include <SFML/Graphics.hpp>

class Terrain
{
private:
	std::vector<sf::Vector2f> groundPoints;
	sf::VertexArray groundShape;
	sf::Color groundColor;

	void initVariables();
	void initShape();
public:
	Terrain();
	~Terrain();

	void render(sf::RenderTarget* target);
	const std::vector<sf::Vector2f>& GetGroundPoints() const;
	const sf::VertexArray& GetGroundShape() const;
};

