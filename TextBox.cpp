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
    
    if(!backBuffer.loadFromFile("res/sfx/back.wav"))
    {
        std::cerr << "Failed to load Back buffer!\n";
    }
    
    backSpaceSound.setBuffer(backBuffer);
    backSpaceSound.setLoop(false);
    
    if(!keyBuffer.loadFromFile("res/sfx/key.mp3"))
    {
        std::cerr << "Failed to load key buffer!\n";
    }
    
    keySound.setBuffer(keyBuffer);
    keySound.setLoop(false);
    
    keyPlayed = false;
    backPlayed = false;
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

Gui::TextBox::TextBox(bool hasLimit, int limit, int charSize, sf::Color TextColor, sf::Vector2f size, sf::Vector2f pos, bool soundState)
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
    this->soundState = soundState;
}

void Gui::TextBox::create(bool hasLimit, int limit, int charSize, sf::Color TextColor, sf::Vector2f size, sf::Vector2f pos, bool soundState)
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
    this->soundState = soundState;
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

    if(input.type == sf::Event::TextEntered)
    {
        if (isSelected)
        {
            if (charTyped < 128)
            {
                if (charTyped == 8) // Backspace key
                {
                    deleteLastChar();
                    if(soundState)
                    {
                        if(!backPlayed)
                        {
                            if(!backSpaceSound.getStatus() && !backSpaceSound.getLoop())
                            {
                                backSpaceSound.play();
                            }
                            backPlayed = true;
                        }
                    }
                }
                else
                {
                    if (hasLimit)
                    {
                        if (os.str().length() <= limit)
                        {
                            inputLogic(charTyped);
                            if(soundState)
                            {
                                if(!keyPlayed)
                                {
                                    if(!keySound.getStatus() && !keySound.getLoop())
                                    {
                                        keySound.play();
                                    }
                                    keyPlayed = true;
                                }
                            }
                        }
                    }
                    else
                    {
                        inputLogic(charTyped);
                    }
                }
            }
        }
    } else {
        keyPlayed = false;
        keySound.stop();
        backPlayed = false;
        backSpaceSound.stop();
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
