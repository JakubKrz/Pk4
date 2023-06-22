#include "UI.h"

void UI::initMenuOptions() // 1920,1080 max
{
	for (sf::Text& text : this->menuOptions)
	{
		text.setFont(this->font);
		text.setCharacterSize(100);
		text.setFillColor(sf::Color(125, 125, 125, 125));
	}
	this->menuOptions[0].setString("Play");
	this->menuOptions[0].setFillColor(sf::Color::White);
	this->menuOptions[0].setPosition(860, 200);
	this->menuOptions[1].setString("Best scores");
	this->menuOptions[1].setPosition(685, 500);
	this->menuOptions[2].setString("Exit");
	this->menuOptions[2].setPosition(860, 800);
	this->selectedItem = 0;
}

void UI::initGameUI()
{
	this->gameTexts.resize(6);
	int i = 0;
	for (sf::Text& text : this->gameTexts)
	{
		text.setFont(this->font);
		text.setCharacterSize(30);
		text.setFillColor(sf::Color::White);
		++i;
	}
	this->gameTexts[0].setPosition(1730, 20);//height
	this->gameTexts[1].setPosition(1730, 55);//speedx
	this->gameTexts[2].setPosition(1730, 90);//speedy
	this->gameTexts[3].setPosition(30, 20);//fuel
	this->gameTexts[4].setPosition(1730, 125);//angle 
	this->gameTexts[5].setPosition(30, 90);//points
	this->LanderFuelBar.setSize(sf::Vector2f(150.f, 20.f));
	this->LanderFuelBar.setFillColor(sf::Color(255, 255, 255, 255));
	this->LanderFuelBar.setPosition(sf::Vector2f(30.f, 65.f));

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
		this->menuOptions[this->selectedItem].setFillColor(sf::Color(125, 125, 125, 125));
		--this->selectedItem;
		this->menuOptions[this->selectedItem].setFillColor(sf::Color::White);

	}
}

void UI::moveDown()
{
	if (this->selectedItem + 1 <= 2)//numbers of menu options
	{
		this->menuOptions[this->selectedItem].setFillColor(sf::Color(125, 125, 125, 125));
		++this->selectedItem;
		this->menuOptions[this->selectedItem].setFillColor(sf::Color::White);

	}
}

int UI::getSelectedItem()
{
	return this->selectedItem;
}

void UI::update(sf::RenderTarget* target, const Lander& lander,const std::vector<sf::Vector2f>& groundPoints)
{
	gameTexts[0].setString("Height:" + std::to_string(static_cast<int>(lander.getHeight(groundPoints)) / 5)); //adjustment for better precision
	gameTexts[1].setString("X speed:" + std::to_string(static_cast<int>(lander.getSpeedX()*14)));
	gameTexts[2].setString("Y speed:" + std::to_string(static_cast<int>(lander.getSpeedY()*14)));
	gameTexts[3].setString("Fuel:" + std::to_string(static_cast<int>(lander.getFuel())));
	gameTexts[4].setString("Angle:" + std::to_string(lander.getRotationAngle()));
	gameTexts[5].setString("Points:"+std::to_string(lander.getPoints()));

	
	this->LanderFuelBar.setSize(sf::Vector2f(this->LanderFuelBarBack.getSize().x * (lander.getFuel() / lander.getMaxFuel()), this->LanderFuelBarBack.getSize().y));// bar length * % of fuel

}
