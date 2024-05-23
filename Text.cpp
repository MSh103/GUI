#include "Text.h"

void Gui::Text::init()
{
	if (!font.loadFromFile("res/font/font.OTF"))
	{
		std::cerr << "Failed to load Font!\n";
	}
	text.setFont(font);
}

Gui::Text::Text()
{
}

Gui::Text::Text(std::string msg, sf::Vector2f pos, int charSize, sf::Color color)
{
	init();
	text.setString(msg);
	text.setPosition(pos);
	text.setCharacterSize(charSize);
	text.setFillColor(color);
}

void Gui::Text::create(std::string msg, sf::Vector2f pos, int charSize, sf::Color color)
{
	init();
	text.setString(msg);
	text.setPosition(pos);
	text.setCharacterSize(charSize);
	text.setFillColor(color);
}