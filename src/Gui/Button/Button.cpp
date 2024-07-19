#include "Button.hpp"

using namespace Gui;

void Button::init()
{
	if (!font.loadFromFile("res/font/font.OTF"))
	{
		std::cerr << "Failed to load font!\n";
	}

	fg.setFont(font);

	if (!buffer.loadFromFile("res/sfx/buttonhover.wav"))
	{
		std::cerr << "Failed to load Sound Buffer!\n";
	}

	sound.setBuffer(buffer);
	sound.setLoop(false);

	isMouseOver = false;
}

Button::Button()
{
}

Button::Button(std::string msg, sf::Vector2f pos, sf::Vector2f buttonSize, int charSize, sf::Color bgColor, sf::Color fgColor, sf::Color bgHoverColor)
{
	init();

	fg.setString(msg);

	bg.setPosition(pos);

	bg.setSize(buttonSize);
	fg.setCharacterSize(charSize);

	bg.setFillColor(bgColor);
	fg.setFillColor(fgColor);

	fg.setOrigin(fg.getLocalBounds().getSize() / 2.f);

	fg.setPosition(sf::Vector2f(
		(bg.getSize().x / 2.f) + pos.x,
		(bg.getSize().y / 2.f) + pos.y
	));

	normalColor[0] = float(bgColor.r);
	normalColor[1] = float(bgColor.g);
	normalColor[2] = float(bgColor.b);
	hoverColor[0] = float(bgHoverColor.r);
	hoverColor[1] = float(bgHoverColor.g);
	hoverColor[2] = float(bgHoverColor.b);

	soundPlayed = false;
}

void Button::create(std::string msg, sf::Vector2f pos, sf::Vector2f buttonSize, int charSize, sf::Color bgColor, sf::Color fgColor, sf::Color bgHoverColor)
{
	init();

	fg.setString(msg);

	bg.setPosition(pos);

	bg.setSize(buttonSize);
	fg.setCharacterSize(charSize);

	bg.setFillColor(bgColor);
	fg.setFillColor(fgColor);

	fg.setOrigin(fg.getLocalBounds().getSize() / 2.f);

	fg.setPosition(sf::Vector2f(
		(bg.getSize().x / 2.f) + pos.x,
		(bg.getSize().y / 2.f) + pos.y
	));

	normalColor[0] = float(bgColor.r);
	normalColor[1] = float(bgColor.g);
	normalColor[2] = float(bgColor.b);
	hoverColor[0] = float(bgHoverColor.r);
	hoverColor[1] = float(bgHoverColor.g);
	hoverColor[2] = float(bgHoverColor.b);
}

void Button::update(sf::RenderWindow& target)
{
	sf::Vector2i mousePos = sf::Mouse::getPosition(target);

	//std::cout << "ButtonPos: " << bg.getPosition().x << ", " << bg.getPosition().y << std::endl;
	//std::cout << "MousePos: "  << mousePos.x		 << ", " << mousePos.y		   << std::endl;

	if (mousePos.x >= bg.getPosition().x &&
		mousePos.x <= bg.getPosition().x + bg.getSize().x &&
		mousePos.y >= bg.getPosition().y &&
		mousePos.y <= bg.getPosition().y + bg.getSize().y)
	{
		isMouseOver = true;
	}
	else {
		isMouseOver = false;
	}

}

void Button::render(sf::RenderWindow& target)
{
	target.draw(bg);
	target.draw(fg);
}

void Button::hoverLogic()
{
	if (isMouseOver)
	{
		if (!soundPlayed)
		{
			if (!sound.getStatus() && !sound.getLoop())
			{
				sound.play();
			}
			soundPlayed = true;
		}
		bg.setFillColor(sf::Color(hoverColor[0], hoverColor[1], hoverColor[2]));
		fg.setFillColor(sf::Color::Black);
	}
	else
	{
		soundPlayed = false;
		sound.stop();
		bg.setFillColor(sf::Color(normalColor[0], normalColor[1], normalColor[2]));
		fg.setFillColor(sf::Color::White);
	}
}

void Button::setTextPosition(sf::Vector2f position)
{
	fg.setPosition(position);
}

void Button::moveText(sf::Vector2f position)
{
	fg.move(position);
}

void Button::setPosWCenteredText(sf::Vector2f pos)
{
	bg.setPosition(pos);

	sf::Vector2f textPos;
	textPos.x = pos.x + (bg.getSize().x / 2.f);
	textPos.y = pos.y + (bg.getSize().y / 2.f);

	fg.setPosition(textPos);
}

void Button::setPosition(sf::Vector2f buttonPos, float xOffset, float yOffset)
{
	bg.setPosition(buttonPos);

	sf::Vector2f textPos;
	textPos.x = buttonPos.x + (xOffset);
	textPos.y = buttonPos.y + (yOffset);

	fg.setPosition(textPos);
}