#include "Lander.h"
#include <iostream>

void Lander::initVariables()//poczatkowe ilosci predkosci,obrotu,paliwa
{
	this->resetPosition();
	this->maxFuel = 1000.f;
	this->fuel = this->maxFuel;
	this->gravity = 0.008f;
	this->acceleration = 0.02f;
	this->fuelConsuption = 0.5f;
}

void Lander::resetPosition(float x, float y)
{
	this->speed_x = 2.f;
	this->speed_y = 0.f;
	this->rotationAngle = 0.0f;
	this->sprite.setPosition(x, y);
	this->sprite.setRotation(this->rotationAngle);
}

void Lander::initSprite()
{	
	this->LanderTexture.loadFromFile("C:/Users/krzyw/Source/Repos/PK4/Projekt/LunarLander/Textures/test1.png");//tutaj uzyc filesystem
	
	this->sprite.setTexture(this->LanderTexture);
	this->sprite.setOrigin(this->sprite.getLocalBounds().width/2, this->sprite.getLocalBounds().height / 2);
	this->sprite.setScale(1.f, 1.f);
}

Lander::Lander()
{
	
	this->initSprite();
	this->initVariables();
}

Lander::~Lander()
{

}

void Lander::update(sf::RenderTarget* target)
{
	this->updateInput();
	this->speed_y += this->gravity;
	this->sprite.move(this->speed_x, this->speed_y);
}

void Lander::updateInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		this->rotationAngle += -3;//zmienna o ile mozna sie obracaac jednorazowao zamiast 1
		this->sprite.setRotation(this->rotationAngle);
		this->rotationAngle = this->rotationAngle % 360;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		this->rotationAngle += 3;//zmienna o ile mozna sie obracaac jednorazowao zamiast 1
		this->sprite.setRotation(this->rotationAngle);
		this->rotationAngle = this->rotationAngle % 360;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		if (fuel > 0)
		{
			this->fuel -= fuelConsuption;
			this->speed_x += this->acceleration * std::cosf(rotationAngle * (3.141 / 180) - 3.141 / 2);//przeniesc na zmienne pi i predkosc
			this->speed_y += this->acceleration * std::sinf(rotationAngle * (3.141 / 180) - 3.141 / 2);//dodac zmienna globalna pi i przyspoeszenie 0.2f
			//odejecie pi/2 zeby "dol byl na dole"
		}
	}
}


void Lander::render(sf::RenderTarget* target)
{
	target->draw(this->sprite);
}

float Lander::getX() const
{
	return this->sprite.getPosition().x;
}

//return bottom of sprite
float Lander::getLowestPoint() const
{
	sf::FloatRect bounds = this->sprite.getLocalBounds();
	sf::Vector2f corners[4] = {
		{ bounds.left, bounds.top },
		{ bounds.left + bounds.width, bounds.top },
		{ bounds.left, bounds.top + bounds.height },
		{ bounds.left + bounds.width, bounds.top + bounds.height }
	};
	float maxY = -10;//cant be less than 0

	for (const auto& corner : corners) {
		sf::Vector2f transformed = this->sprite.getTransform().transformPoint(corner);
		maxY = std::max(maxY, transformed.y);
	}
	return maxY;
}

bool Lander::checkCollision(std::vector<sf::Vector2f> groundPoints) const
{
	sf::FloatRect spriteBounds = this->sprite.getGlobalBounds();
	sf::Vector2f spriteCenter(spriteBounds.left + spriteBounds.width / 2.0f, spriteBounds.top + spriteBounds.height / 2.0f);

	for (size_t i = 0; i < groundPoints.size() - 1; ++i)
	{
		sf::Vector2f point1 = groundPoints[i];
		sf::Vector2f point2 = groundPoints[i + 1];

		sf::Vector2f lineDirection = point2 - point1;
		sf::Vector2f spriteToLine = spriteCenter - point1;

		float dotProduct = lineDirection.x * spriteToLine.x + lineDirection.y * spriteToLine.y;
		float lineLengthSquared = lineDirection.x * lineDirection.x + lineDirection.y * lineDirection.y;
		float t = dotProduct / lineLengthSquared;
		t = std::max(0.0f, std::min(1.0f, t));

		sf::Vector2f closestPoint = point1 + t * lineDirection;
		sf::Vector2f diff = spriteCenter - closestPoint;
		sf::Vector2f absDiff(std::abs(diff.x), std::abs(diff.y));

		float xOverlap = spriteBounds.width / 2.0f - absDiff.x;
		if (xOverlap <= 0.0f)
		{
			continue;
		}

		float yOverlap = spriteBounds.height / 2.0f - absDiff.y;
		if (yOverlap <= 0.0f)
		{
			continue;
		}

		return true;
	}

	return false;
}



float Lander::getHeight(std::vector<sf::Vector2f> groundPoints) const
{
	float x = this->getX();
	float y = this->getLowestPoint();
	for (size_t i = 0; i < groundPoints.size() - 1; ++i)
	{
		float x1 = groundPoints[i].x;
		float x2 = groundPoints[i + 1].x;

		if (x >= x1 && x <= x2)
		{
			float y1 = groundPoints[i].y;
			float y2 = groundPoints[i + 1].y;

			if (x == x1)
				return y1 - y;
			else if (x == x2)
				return y2 - y;
			else
			{
				float t = (x - x1) / (x2 - x1);
				return y1 + t * (y2 - y1) - y;
			}
		}
	}
	return 0.0f;
}

float Lander::getSpeedX() const
{
	return this->speed_x;
}

float Lander::getSpeedY() const
{
	return this->speed_y;
}

float Lander::getFuel() const
{
	return this->fuel;
}

int Lander::getRotationAngle() const
{
	return this->rotationAngle;
}

float Lander::getMaxFuel() const
{
	return this->maxFuel;
}
