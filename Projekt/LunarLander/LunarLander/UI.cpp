#include "UI.h"

UI::UI()
{
	if (!this->font.loadFromFile("C:/Users/krzyw/Source/Repos/PK4/Projekt/LunarLander/Fonts/zector/Zector.ttf"))
	{
		std::cout << "error, ccant load font\n";
	}
	this->text.setFont(this->font);

	// set the character size
	text.setCharacterSize(20); // in pixels, not points!

	// set the color
	text.setFillColor(sf::Color::White);

	// set the text style
	//text.setStyle();
}

UI::~UI()
{
}

void UI::render(sf::RenderTarget* target)
{
	target->draw(this->text);
}

void UI::update(sf::RenderTarget* target, float height)
{
	text.setString("Height:"+std::to_string(static_cast<int>(height)/5)); //zamiana pikesli na jednostki
}
