#include "Lander.h"

void Lander::initVariables()//poczatkowe ilosci predkosci,obrotu,paliwa
{	
	this->speed_x = 0.2f;
	this->speed_y = 0.f;
	this->rotationAngle = 0.0f;
	this->fuel = 1000.f;
}

void Lander::initShape()
{
	//wczytywanie wygladu
	this->shape.setFillColor(sf::Color(255, 125, 100, 255));
	//ustawianie rozmiaru
	this->shape.setSize(sf::Vector2f(25.f, 50.f));
	this->shape.setOrigin(12.5f, 25.f);//ustawienie srodka osi obrotu
}

Lander::Lander(float x, float y)
{
	this->shape.setPosition(x, y);
	this->initShape();
	this->initVariables();
}

Lander::~Lander()
{

}

void Lander::update(sf::RenderTarget* target)
{
	this->updateInput();
	this->speed_y += 0.01f;//dodanie grawitacji, dodac zmienna globalna lub w klasie
	this->shape.move(this->speed_x, this->speed_y);
	//oblicznie predkosci(dodanie grawitacj) i zmiana polozenia(this->shape.move)
}

void Lander::updateInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		this->rotationAngle += -3;//zmienna o ile mozna sie obracaac jednorazowao zamiast 1
		this->shape.setRotation(this->rotationAngle);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		this->rotationAngle += 3;//zmienna o ile mozna sie obracaac jednorazowao zamiast 1
		this->shape.setRotation(this->rotationAngle);
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
	target->draw(this->shape);
}
