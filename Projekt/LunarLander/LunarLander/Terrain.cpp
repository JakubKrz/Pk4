#include "Terrain.h"

Terrain::Terrain()
{
    this->initVariables();
    this->generateGround();
}

Terrain::~Terrain()
{
}

void Terrain::generateGround()
{
    this->generatePoints();
    this->generateLandingPads();
    this->initShape();
}

void Terrain::generatePoints()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> disY(400.0f, 1000.0f); // Adjust the Y range 

    //genereating points for ground
    for (size_t i = 0; i < this->size; ++i)
    {
        sf::Vector2f point(i * width, disY(gen));
        this->groundPoints[i]=point;
    }
    //Eliminating diffrence between 2 points if its too big
    for (size_t i = 1; i < groundPoints.size() - 1; ++i)
    {
        float diff = (this->groundPoints[i].y - this->groundPoints[i - 1].y);
        if (std::abs(diff) > 450)
        {
            if (diff < 0) {
                this->groundPoints[i].y += 450;
            }
            else
            {
                this->groundPoints[i].y -= 450;
            }
        }
    }
    //smoothing
    for (size_t iteration = 0; iteration < 1; ++iteration)
    {
        for (size_t i = 3; i < groundPoints.size() - 3; ++i)
        {
            groundPoints[i].y = (0.5f * groundPoints[i - 2].y + groundPoints[i - 1].y + 2.f * groundPoints[i].y + groundPoints[i + 1].y + 0.5f * groundPoints[i + 2].y) / 5.0f;
        }
    }
}

void Terrain::initVariables()
{
    this->width = 20;
    this->size = 1940 / width;
    this->landingPadWidth = 3;//podzielnie przez 3 albo zmiana w gneratelandingpads
    this->groundPoints.resize(this->size);
    this->groundColor = sf::Color::White;
    this->groundShape.setPrimitiveType(sf::LineStrip);
    this->groundShape.resize(this->groundPoints.size());
}

void Terrain::generateLandingPads()
{       
    std::random_device rd;
    std::mt19937 gen(rd());
    //Calculating 3 areas for landingPads
    size_t area=(this->size-3-landingPadWidth) / 3;
    for (size_t i = 1; i < 3 * area; i += area)
    {
        std::uniform_real_distribution<float> dis(i, static_cast<float>(i) + area);
        size_t number = static_cast<size_t>(dis(gen));
        float y = this->groundPoints[number].y;
        for (size_t l = 0; l < this->landingPadWidth; ++l)
        {
            this->groundPoints[number + l + 1].y = y;
        }
        this->landingPads.push_back(std::make_pair<size_t, size_t>(this->groundPoints[number].x, this->groundPoints[number + this->landingPadWidth].x));
    }
}

void Terrain::initShape()
{
    for (size_t i = 0; i < this->groundPoints.size(); ++i)
    {
        this->groundShape[i].position = groundPoints[i];    
        this->groundShape[i].color = groundColor;
    }
}

void Terrain::render(sf::RenderTarget* target)
{
    target->draw(this->groundShape);
}


const std::vector<sf::Vector2f>& Terrain::GetGroundPoints() const
{
    return this->groundPoints;
}

const sf::VertexArray& Terrain::GetGroundShape() const
{
    return this->groundShape;
}

std::vector<std::pair<size_t, size_t>> Terrain::getLandingPads()
{
    return this->landingPads;
}
