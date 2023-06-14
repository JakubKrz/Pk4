#include "Lander.h"

void Lander::initVariables()//poczatkowe ilosci predkosci,obrotu,paliwa
{
	this->speed_x = 0.2f;
	this->speed_y = 0.f;
	this->rotationAngle = 0.0f;
	this->fuel = 1000.f;
}

void Lander::initSprite()
{	
	this->texture.loadFromFile("C:/Users/krzyw/Source/Repos/PK4/Projekt/LunarLander/Textures/test.png");//tutaj uzyc filesystem
	
	this->sprite.setTexture(this->texture);
	this->sprite.setOrigin(this->sprite.getLocalBounds().width/2, this->sprite.getLocalBounds().height / 2);
}

Lander::Lander(float x, float y)
{
	this->sprite.setPosition(x, y);
	this->initSprite();
	this->initVariables();
}

Lander::~Lander()
{

}

void Lander::update(sf::RenderTarget* target)
{
	this->updateInput();
	this->speed_y += 0.01f;//dodanie grawitacji, dodac zmienna globalna lub w klasie
	this->sprite.move(this->speed_x, this->speed_y);
	//oblicznie predkosci(dodanie grawitacj) i zmiana polozenia(this->shape.move)
}

void Lander::updateInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		this->rotationAngle += -3;//zmienna o ile mozna sie obracaac jednorazowao zamiast 1
		this->sprite.setRotation(this->rotationAngle);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		this->rotationAngle += 3;//zmienna o ile mozna sie obracaac jednorazowao zamiast 1
		this->sprite.setRotation(this->rotationAngle);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		if (fuel > 0)
		{
			this->fuel -= 1.f;//zuzycie paliwa
			this->speed_x += 0.2f * std::cos(rotationAngle * (3.141 / 180.f) - 3.141 / 2);//przeniesc na zmienne pi i predkosc
			this->speed_y += 0.2f * std::sin(rotationAngle * (3.141 / 180.f) - 3.141 / 2);//dodac zmienna globalna pi i przyspoeszenie 0.2f
			//dodanie pi/2 zeby "dol byl na dole"
		}
	}
}


void Lander::render(sf::RenderTarget* target)
{
	target->draw(this->sprite);
}
