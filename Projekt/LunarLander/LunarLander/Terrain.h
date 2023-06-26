#pragma once
#include <SFML/Graphics.hpp>
#include <random>

class Terrain
{//TO DO : landing pads wyswietlanie gdzie sa i ew dodatkowe bonust
private:
	std::vector<sf::Vector2f> groundPoints;
	sf::VertexArray groundShape;
	sf::Color groundColor;
	//groundpoints
	size_t width;
	size_t size;
	//landing points
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
	~Terrain();

	void generateGround();
	void render(sf::RenderTarget* target);
	const std::vector<sf::Vector2f>& GetGroundPoints() const;
	const sf::VertexArray& GetGroundShape() const;
	std::vector<std::pair<size_t, size_t>> getLandingPads();
};

