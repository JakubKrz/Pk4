#include "UI.h"

UI::UI()
{
	if (!this->font.loadFromFile("C:/Users/krzyw/Source/Repos/PK4/Projekt/LunarLander/Fonts/zector/Zector.ttf"))
	{
		std::cout << "error, ccant load font\n";
	}
	this->texts.resize(6);
	int i = 0;
	for (sf::Text& text : this->texts) 
	{
		text.setFont(this->font);
		text.setCharacterSize(20);
		text.setFillColor(sf::Color::White);
		text.setPosition(0, i*20);
		++i;
	}
	//text.setStyle();
}

UI::~UI()
{
}

void UI::render(sf::RenderTarget* target)
{
	for (sf::Text& text : this->texts)
	{
		target->draw(text);
	}
}

void UI::update(sf::RenderTarget* target, const Lander& lander,const std::vector<sf::Vector2f>& groundPoints)
{
	texts[0].setString("Height:" + std::to_string(static_cast<int>(lander.getHeight(groundPoints)) / 5)); //adjustment for better precision
	texts[1].setString("Speedx:" + std::to_string(static_cast<int>(lander.getSpeedX()*10)));
	texts[2].setString("Speedy:" + std::to_string(static_cast<int>(lander.getSpeedY()*10)));
	texts[3].setString("Fuel:" + std::to_string(static_cast<int>(lander.getFuel())));
	texts[4].setString("Kolizja:"+std::to_string(lander.checkCollision(groundPoints)));
	texts[5].setString("RotationAngle:"+ std::to_string(lander.getRotationAngle()));

}
