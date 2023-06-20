#include "Terrain.h"


void Terrain::initVariables()
{
    this->groundPoints = { sf::Vector2f(0, 1075), sf::Vector2f(400, 700), sf::Vector2f(800, 900),sf::Vector2f(1200, 900),sf::Vector2f(1600, 400), sf::Vector2f(1925,1075) };
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

float Terrain::getHeight(float x,float y) const
{
    for (size_t i = 0; i < groundPoints.size() - 1; ++i)
    {
        float x1 = groundPoints[i].x;
        float x2 = groundPoints[i + 1].x;

        if (x >= x1 && x <= x2)
        {
            float y1 = groundPoints[i].y;
            float y2 = groundPoints[i + 1].y;

            if (x == x1)
                return y1;
            else if (x == x2)
                return y2;
            else
            {
                float t = (x - x1) / (x2 - x1);
                return y1 + t * (y2 - y1)-y;
            }
        }
    }
    return 0.0f;
}

const std::vector<sf::Vector2f>& Terrain::GetGroundPoints() const
{
    return this->groundPoints;
}

const sf::VertexArray& Terrain::GetGroundShape() const
{
    return this->groundShape;
}
