#include "UI.h"

void UI::initMenuOptions() //TO DO: ustawic pozycje na srodek
{
	int i = 0;
	for (sf::Text& text : this->menuOptions)
	{
		text.setFont(this->font);
		text.setCharacterSize(20);
		text.setFillColor(sf::Color::White);
		text.setPosition(0, i * 20);//change
		++i;
	}
	this->menuOptions[0].setString("Moje Menu");
	this->menuOptions[0].setFillColor(sf::Color::Red);
	this->menuOptions[1].setString("opcja 2");
	this->menuOptions[2].setString("opcja 3 wyjscie");
	this->selectedItem = 0;
}

void UI::initGameUI()
{
	this->gameTexts.resize(6);
	int i = 0;
	for (sf::Text& text : this->gameTexts)
	{
		text.setFont(this->font);
		text.setCharacterSize(20);
		text.setFillColor(sf::Color::White);
		text.setPosition(0, i * 20);
		++i;
	}
	//text.setStyle();
	this->LanderFuelBar.setSize(sf::Vector2f(100.f, 15.f));
	this->LanderFuelBar.setFillColor(sf::Color(255, 255, 255, 255));
	this->LanderFuelBar.setPosition(sf::Vector2f(100.f, 67.f));

	this->LanderFuelBarBack = this->LanderFuelBar;
	this->LanderFuelBarBack.setFillColor(sf::Color(125, 125, 125, 125));
}

UI::UI()
{
	if (!this->font.loadFromFile("C:/Users/krzyw/Source/Repos/PK4/Projekt/LunarLander/Fonts/zector/Zector.ttf"))//filesystem
	{
		std::cout << "error, cant load font\n";
	}
	//menu texts
	this->initMenuOptions();

	//in game texts
	this->initGameUI();
}

UI::~UI()
{
}

void UI::render(sf::RenderTarget* target)
{
	for (sf::Text& text : this->gameTexts)
	{
		target->draw(text);
	}
	target->draw(this->LanderFuelBar);
	target->draw(this->LanderFuelBarBack);
}

void UI::renderMenu(sf::RenderTarget* target)
{
	for (sf::Text& text : this->menuOptions)
	{
		target->draw(text);
	}
}

void UI::moveUp()
{
	if (this->selectedItem - 1 >= 0)
	{
		this->menuOptions[this->selectedItem].setFillColor(sf::Color::White);
		--this->selectedItem;
		this->menuOptions[this->selectedItem].setFillColor(sf::Color::Red);

	}
}

void UI::moveDown()
{
	if (this->selectedItem + 1 <= 2)//numbers of menu options
	{
		this->menuOptions[this->selectedItem].setFillColor(sf::Color::White);
		++this->selectedItem;
		this->menuOptions[this->selectedItem].setFillColor(sf::Color::Red);

	}
}

int UI::getSelectedItem()
{
	return this->selectedItem;
}

void UI::update(sf::RenderTarget* target, const Lander& lander,const std::vector<sf::Vector2f>& groundPoints)
{
	gameTexts[0].setString("Height:" + std::to_string(static_cast<int>(lander.getHeight(groundPoints)) / 5)); //adjustment for better precision
	gameTexts[1].setString("Speedx:" + std::to_string(static_cast<int>(lander.getSpeedX()*14)));
	gameTexts[2].setString("Speedy:" + std::to_string(static_cast<int>(lander.getSpeedY()*14)));
	gameTexts[3].setString("Fuel:" + std::to_string(static_cast<int>(lander.getFuel())));
	gameTexts[4].setString("Points:"+std::to_string(lander.getPoints()));
	gameTexts[5].setString("RotationAngle:"+ std::to_string(lander.getRotationAngle()));
	
	this->LanderFuelBar.setSize(sf::Vector2f(this->LanderFuelBarBack.getSize().x * (lander.getFuel() / lander.getMaxFuel()), this->LanderFuelBarBack.getSize().y));// bar length * % of fuel

}
