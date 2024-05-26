#include "TextBox.h"

void Gui::TextBox::init()
{
	if (!font.loadFromFile("res/font/font.OTF"))
	{
		std::cerr << "Failed to load font!\n";
	}
	text.setFont(font);
	isSelected = false;
	limit = 0;
	isMouseOver = false;
	
	box.setOutlineThickness(5.f);
	box.setOutlineColor(sf::Color::Black);

}

void Gui::TextBox::deleteLastChar()
{
    std::string currentText = os.str();
    if (!currentText.empty())
    {
        currentText.pop_back();
        os.str(""); // Clear the stream
        os.clear(); // Clear any error flags
        os << currentText; // Put the modified string back into the stream
        text.setString(os.str());
        text.setOrigin(text.getLocalBounds().getSize().x / 2.f, text.getLocalBounds().getSize().y / 2.f);
    }
}


void Gui::TextBox::inputLogic(int charTyped)
{
	if (charTyped >= 32 && charTyped < 128)
	{
		os << static_cast<char>(charTyped);
	}
	text.setString(os.str());
	text.setOrigin(text.getLocalBounds().getSize().x / 2.f, text.getLocalBounds().getSize().y / 2.f);
}

Gui::TextBox::TextBox()
{
}

Gui::TextBox::TextBox(bool save, bool hasLimit, int limit, int charSize, sf::Color TextColor, sf::Vector2f size, sf::Vector2f pos)
{
	init();
	text.setCharacterSize(charSize);
	text.setFillColor(TextColor);

	box.setSize(size);
	box.setPosition(pos);
	
	text.setOrigin(text.getLocalBounds().getSize() / 2.f);
	text.setPosition(pos + (size / 2.f));

	this->hasLimit = hasLimit;
	this->limit = limit;
    this->save = save;
}

Gui::TextBox::~TextBox()
{
    ofs.close();
}

void Gui::TextBox::create(bool save, bool hasLimit, int limit, int charSize, sf::Color TextColor, sf::Vector2f size, sf::Vector2f pos)
{
	init();
	text.setCharacterSize(charSize);
	text.setFillColor(TextColor);

	box.setSize(size);
	box.setPosition(pos);

	text.setOrigin(text.getLocalBounds().getSize() / 2.f);
	text.setPosition(pos + (size / 2.f));

	this->hasLimit = hasLimit;
	this->limit = limit;
    this->save = save;
}

void Gui::TextBox::update(sf::RenderWindow& target)
{
	sf::Vector2i mousePos = sf::Mouse::getPosition(target);

	if (mousePos.x >= box.getPosition().x &&
		mousePos.x < box.getPosition().x + box.getSize().x &&
		mousePos.y >= box.getPosition().y &&
		mousePos.y < box.getPosition().y + box.getSize().y)
	{
		isMouseOver = true;
	}
	else {
		isMouseOver = false;
	}
}

void Gui::TextBox::input(sf::Event& input)
{
	int charTyped = input.text.unicode;

	if (input.type == sf::Event::TextEntered)
	{
		if (isSelected)
		{
			if (charTyped < 128)
			{
				if (charTyped == 8) // Backspace key
				{
					deleteLastChar();
				}
				else
				{
					if (hasLimit)
					{
						if (os.str().length() <= limit)
						{
							inputLogic(charTyped);
						}
					}
					else
					{
						inputLogic(charTyped);
					}
				}
			}
		}
	}

	if (input.type == sf::Event::KeyPressed)
	{
		if (input.key.code == sf::Keyboard::Enter)
		{
			this->submission = os.str();
			os.str("");
			if (save)
			{
				saveToFile();
			}
		}
	}
}

void Gui::TextBox::hoverLogic()
{
	if (isMouseOver)
	{
		box.setOutlineColor(sf::Color(100, 100, 100));
	}
	else {
		box.setOutlineColor(sf::Color::Black);
	}
}

void Gui::TextBox::render(sf::RenderWindow& target)
{
	target.draw(box);
	target.draw(text);
}
