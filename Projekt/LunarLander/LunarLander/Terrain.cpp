#include "Terrain.h"


void Terrain::initVariables()
{
	this->groundPoints = { sf::Vector2f(0, 1075), sf::Vector2f(400, 700), sf::Vector2f(800, 900),sf::Vector2f(1200, 900),sf::Vector2f(1600, 400), sf::Vector2f(1925,1075)};
	this->groundColor = sf::Color::White;
}

void Terrain::initShape()
{
    this->groundShape.setPrimitiveType(sf::LineStrip);
    this->groundShape.resize(this->groundPoints.size());

    for (size_t i = 0; i < this->groundPoints.size(); ++i)
    {
        this->groundShape[i].position = groundPoints[i];
        this->groundShape[i].color = groundColor;
    }
}

Terrain::Terrain()
{
	this->initVariables();
	this->initShape();
}

Terrain::~Terrain()
{
}

void Terrain::render(sf::RenderTarget* target)
{
    target->draw(this->groundShape);
}
