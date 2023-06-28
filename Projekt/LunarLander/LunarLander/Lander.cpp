#include "Lander.h"

#define PI 3.14159

Lander::Lander() : maxFuel(1000.f), fuel(maxFuel), gravity(0.006f), acceleration(0.02f), 
fuelConsumption(0.5f), points(0), rotationAngle(0), rotationValue(2), speed_x(2.f), speed_y(0.f)
{
	this->initSprite();
	this->resetPosition();
}

//Load texture, set origin
void Lander::initSprite()
{
	this->LanderTexture.loadFromFile("C:/Users/krzyw/Source/Repos/PK4/Projekt/LunarLander/Textures/test1.png");
	this->landerSprite.setTexture(this->LanderTexture);
	this->landerSprite.setOrigin(this->landerSprite.getLocalBounds().width / 2, this->landerSprite.getLocalBounds().height / 2);
	this->landerSprite.setScale(1.f, 1.f);
}

//Resets position to starting point
void Lander::resetPosition(float x, float y)
{
	this->speed_x = 2.f;
	this->speed_y = 0.f;
	this->rotationAngle = 0;
	this->landerSprite.setPosition(x, y);
	this->landerSprite.setRotation(this->rotationAngle);
}

//Resets fuel,points and call resetPosition
void Lander::reset()
{
	this->fuel = this->maxFuel;
	this->points = 0;
	this->resetPosition();
}


//checks if landing is succesfull add points or remove fuel
bool Lander::landingUpdate(const std::vector<std::pair<size_t, size_t>>& landingPads)
{
	float x = this->landerSprite.getPosition().x;
	float width = this->landerSprite.getGlobalBounds().width/2;
	bool sucesfull = false;
	int i = 0;
	int landingPadNum = 0;
	for (auto& pad : landingPads)
	{
		if (x-width > pad.first && x+width < pad.second)
		{
			if (this->speed_x * 14 < 10 && this->speed_y * 14 < 10 && std::abs(this->rotationAngle) < 20)//*14-to match the displayed speed
			{
				sucesfull = true;
				landingPadNum = i;
			}
		}
		++i;
	}
	if (sucesfull)
	{
		if (landingPadNum == 0) {
			this->points += 100;
		}
		else if (landingPadNum == 1)
		{
			this->points += 200;
		}else{
			this->points += 500;
		}
	}
	else 
	{
		this->fuel -= 300;
	}
	return(sucesfull);
}

//Apply gravity and speed, calls  updateInput
void Lander::update(sf::RenderTarget* target)
{
	this->updateInput();
	this->speed_y += this->gravity;
	this->landerSprite.move(this->speed_x, this->speed_y);
}

//Checks input, rotate or add velocity(consume fuel)
void Lander::updateInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		this->rotationAngle += -this->rotationValue;
		this->landerSprite.setRotation(this->rotationAngle);
		this->rotationAngle = this->rotationAngle % 360;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		this->rotationAngle += this->rotationValue;
		this->landerSprite.setRotation(this->rotationAngle);
		this->rotationAngle = this->rotationAngle % 360;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		if (fuel > 0)
		{
			this->fuel -= fuelConsumption;
			this->speed_x += this->acceleration * std::cosf(rotationAngle * (PI / 180.f) - PI / 2.f);
			this->speed_y += this->acceleration * std::sinf(rotationAngle * (PI / 180.f) - PI / 2.f);
			//PI/2 - adjusts the angle of the acceleration angle
		}
	}
}

//Draws lander
void Lander::render(sf::RenderTarget* target)
{
	target->draw(this->landerSprite);
}

//For each line segment, it calculates the closest point on the line segment to the center of the lander sprite. 
//Then determines the overlap on both the x-axis and the y-axis between the lander sprite and the line segment. 
//If there is an overlap on both axes, it means there is a collision.
bool Lander::checkCollision(const std::vector<sf::Vector2f>& groundPoints) const
{

	sf::FloatRect spriteBounds = this->landerSprite.getGlobalBounds();
	sf::Vector2f spriteCenter(spriteBounds.left + spriteBounds.width / 2.0f, spriteBounds.top + spriteBounds.height / 2.0f);

	for (size_t i = 0; i < groundPoints.size() - 1; ++i)
	{
		sf::Vector2f point1 = groundPoints[i];
		sf::Vector2f point2 = groundPoints[i + 1];

		sf::Vector2f lineDirection = point2 - point1; //vextor of line direction
		sf::Vector2f spriteToLine = spriteCenter - point1;	//vector from sprite to groundpoint1

		float dotProduct = lineDirection.x * spriteToLine.x + lineDirection.y * spriteToLine.y;
		float lineLengthSquared = lineDirection.x * lineDirection.x + lineDirection.y * lineDirection.y;//linedirection^2 to avoid sqrt
		float t = dotProduct / lineLengthSquared;//the position of the closest point on the line segment relative to point1
		t = std::max(0.0f, std::min(1.0f, t)); //must be between 0 and 1

		sf::Vector2f closestPoint = point1 + t * lineDirection;
		sf::Vector2f diff = spriteCenter - closestPoint;
		sf::Vector2f absDiff(std::abs(diff.x), std::abs(diff.y));

		float xOverlap = spriteBounds.width / 2.5f - absDiff.x;//adjustment to 2.5 due to sprite real size
		if (xOverlap <= 0.0f)
		{
			continue;
		}

		float yOverlap = spriteBounds.height / 2.f - absDiff.y;
		if (yOverlap <= 0.0f)
		{
			continue;
		}

		return true;
	}

	return false;
}

//Check if lander is out ouf screen
bool Lander::outOfScreen()
{
	if (this->landerSprite.getPosition().x < -this->landerSprite.getLocalBounds().width - 30.f || this->landerSprite.getPosition().x > this->landerSprite.getLocalBounds().width + 1950.f
		|| this->landerSprite.getPosition().y < -this->landerSprite.getLocalBounds().height-30.f)
	{
		return true;
	}
	return false;
}

//Retrurns distance between ground and lander
float Lander::getHeight(const std::vector<sf::Vector2f>& groundPoints) const
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

//return bottom of sprite
float Lander::getLowestPoint() const
{
	sf::FloatRect bounds = this->landerSprite.getLocalBounds();
	sf::Vector2f corners[4] = {
		{ bounds.left, bounds.top },
		{ bounds.left + bounds.width, bounds.top },
		{ bounds.left, bounds.top + bounds.height },
		{ bounds.left + bounds.width, bounds.top + bounds.height }
	};
	float maxY = -1;//cant be less than 0

	for (const auto& corner : corners) {
		sf::Vector2f transformed = this->landerSprite.getTransform().transformPoint(corner);
		maxY = std::max(maxY, transformed.y);
	}
	return maxY;
}

float Lander::getX() const
{
	return this->landerSprite.getPosition().x;
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

int Lander::getPoints() const
{
	return this->points;
}
