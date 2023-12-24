#include "Terrain.h"

Terrain::Terrain() : width(20), landingPadWidth(3)
{
    this->initVariables();
    this->generateGround();
    this->initMultiplier();
}

void Terrain::initVariables()
{
    this->size = 1940 / width;
    this->groundPoints.resize(this->size);
    this->groundColor = sf::Color::White;
    this->groundShape.setPrimitiveType(sf::LineStrip);
    this->groundShape.resize(this->groundPoints.size());
}

void Terrain::generateGround()
{
    this->generatePoints();
    this->generateLandingPads();
    this->initShape();
}

//Generate random points for ground
void Terrain::generatePoints()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> disY(400.0f, 1000.0f); //y -range

    //genereating points for ground
    for (size_t i = 0; i < this->size; ++i)
    {
        sf::Vector2f point(i * width, disY(gen));
        this->groundPoints[i]=point;
    }
    //Eliminating diffrence between 2 points if its too big
    /*for (size_t i = 1; i < groundPoints.size() - 1; ++i)
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
    }*/
    //smoothing
    for (size_t iteration = 0; iteration < 1; ++iteration)
    {
        for (size_t i = 3; i < groundPoints.size() - 3; ++i)
        {
            groundPoints[i].y = (0.5f * groundPoints[i - 2].y + groundPoints[i - 1].y + 2.f * groundPoints[i].y + groundPoints[i + 1].y + 0.5f * groundPoints[i + 2].y) / 5.0f;
        }
    }
}

//creates pad(few points at the same height) one within each of 3 areas, stores their position and set position of multiplier
void Terrain::generateLandingPads()
{       
    std::random_device rd;
    std::mt19937 gen(rd());
    this->landingPads.clear();
    //Calculating 3 areas for landingPads
    size_t area=(this->size-3-landingPadWidth) / 3;
    size_t m = 0;
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
        this->multiplier[m].setPosition((this->landingPads[this->landingPads.size() - 1].first + this->landingPadWidth/2.f)+11.5f , y + 5.f);
        ++m;
    }
}

//init multiplier text 
void Terrain::initMultiplier()
{
    if (!this->font.loadFromFile("C:/Users/krzyw/Source/Repos/PK4/Projekt/LunarLander/Fonts/zector/Zector.ttf"))
    {
    }
    for (size_t i = 0; i < 3; ++i)
    {
        this->multiplier[i].setFont(this->font);
        this->multiplier[i].setCharacterSize(30);
        this->multiplier[i].setFillColor(sf::Color::White);
    }
    this->multiplier[0].setString("1x");
    this->multiplier[1].setString("2x");
    this->multiplier[2].setString("5x");

}

//Creates shape of gorund using groundPoints
void Terrain::initShape()
{
    for (size_t i = 0; i < this->groundPoints.size(); ++i)
    {
        this->groundShape[i].position = groundPoints[i];
        this->groundShape[i].color = groundColor;
    }
}

//Displays ground and multiplier texts
void Terrain::render(sf::RenderTarget* target)
{
    target->draw(this->groundShape);
    for (size_t i = 0; i < 3; ++i)
    {
        target->draw(this->multiplier[i]);
    }
}

const std::vector<sf::Vector2f>& Terrain::GetGroundPoints() const
{
    return this->groundPoints;
}

const sf::VertexArray& Terrain::GetGroundShape() const
{
    return this->groundShape;
}

const std::vector<std::pair<size_t, size_t>>& Terrain::getLandingPads() const
{
    return this->landingPads;
}