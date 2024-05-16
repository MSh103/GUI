#include "Gui.h"

void Gui::Button::init()
{
	if (!font.loadFromFile("res/font/font.ttf"))
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

Gui::Button::Button()
{
}

Gui::Button::Button(std::string msg, sf::Vector2f pos, sf::Vector2f buttonSize, int charSize, sf::Color bgColor, sf::Color fgColor, sf::Color bgHoverColor)
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
	hoverColor[0] =  float(bgHoverColor.r);
	hoverColor[1] =  float(bgHoverColor.g);
	hoverColor[2] =  float(bgHoverColor.b);

	soundPlayed = false;
}

void Gui::Button::create(std::string msg, sf::Vector2f pos, sf::Vector2f buttonSize, int charSize, sf::Color bgColor, sf::Color fgColor, sf::Color bgHoverColor)
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

void Gui::Button::update(sf::RenderWindow& target)
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

void Gui::Button::render(sf::RenderWindow& target)
{
	target.draw(bg);
	target.draw(fg);
}

void Gui::Button::hoverLogic()
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

void Gui::Button::setTextPosition(sf::Vector2f position)
{
	fg.setPosition(position);
}

void Gui::Button::moveText(sf::Vector2f position)
{
	fg.move(position);
}

void Gui::Text::init()
{
	if (!font.loadFromFile("res/font/font.ttf"))
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

void Gui::ComboBox::init()
{
	if (!font.loadFromFile("res/font/font.ttf"))
	{
		std::cerr << "Failed to load Font!\n";
	}
	ComboBoxTitle.setFont(font);
	ComboBoxTitle.setCharacterSize(45);
	
	if (!buffer.loadFromFile("res/sfx/buttonhover.wav"))
	{
		std::cerr << "Failed to load Soundbuffer!\n";
	}
	sound.setBuffer(buffer);
	sound.setLoop(false);

	buttonSound.setBuffer(buffer);
	buttonSound.setLoop(false);

	open = false;

	anyButtonHovered = false;
	soundPlayedForButtons = false;
}

Gui::ComboBox::ComboBox()
{
}

Gui::ComboBox::ComboBox(int noOptions, sf::Vector2f pos, std::vector<std::string> options, sf::Vector2f size, std::string defaultOption, std::vector<bool> noOfButtons)
{
	init();
	this->noOfOptions = noOptions;
	this->pos = pos;
	this->size = size;
	this->options = options;
	this->hoverButton = noOfButtons;

	bg.setSize({ this->size.x + 25.f, this->size.y });
	bg.setFillColor(sf::Color::Black);
	bg.setPosition({ this->pos.x - (25.f / 2.f), this->pos.y });

	ComboBoxTitle.setPosition(sf::Vector2f(
		pos.x + (size.x / 2.f),
		pos.y + (size.y / 2.f)
	));

	list.resize(noOfOptions);
	for (int i = 0; i < this->noOfOptions; ++i) {
		sf::Text text;
		sf::RectangleShape rect;
		this->hoverButton[i] = false;
		rect.setSize(this->size);
		rect.setFillColor(sf::Color(100, 100, 100));
		rect.setPosition(sf::Vector2f(
			pos.x,
			pos.y + (i+1) * size.y
		));
		text.setFont(font);
		text.setCharacterSize(45);
		if (!this->options.empty() && i < this->options.size()) {
			text.setString(this->options[i]);
		}
		text.setPosition(pos.x + (size.x / 2.f), pos.y + (i + 1.5) * (size.y));
		text.setOrigin(text.getLocalBounds().getSize() / 2.f); 
		list[i] = text;
		bgList.push_back(rect);
	}

	ComboBoxTitle.setString(defaultOption);

	ComboBoxTitle.setOrigin(ComboBoxTitle.getLocalBounds().getSize() / 2.f);

}

void Gui::ComboBox::create(int noOptions, sf::Vector2f pos, std::vector<std::string> options, sf::Vector2f size, std::string defaultOption, std::vector<bool> noOfButtons)
{
	init();
	this->noOfOptions = noOptions;
	this->pos = pos;
	this->size = size;
	this->options = options;

	bg.setSize(this->size);
	bg.setFillColor(sf::Color::Black);
	bg.setPosition(this->pos);

	ComboBoxTitle.setPosition(sf::Vector2f(
		pos.x + (size.x / 2.f),
		pos.y + (size.y / 2.f)
	));

	list.resize(noOfOptions);
	for (int i = 0; i < this->noOfOptions; ++i) {
		sf::Text text;
		sf::RectangleShape rect;
		rect.setSize(this->size);
		rect.setFillColor(sf::Color(100, 100, 100));
		rect.setPosition(sf::Vector2f(
			pos.x,
			pos.y + (i + 1) * size.y
		));
		text.setFont(font);
		text.setCharacterSize(45);
		if (!this->options.empty() && i < this->options.size()) {
			text.setString(this->options[i]);
		}
		text.setPosition(pos.x + (size.x / 2.f), pos.y + (i + 1.5) * (size.y));
		text.setOrigin(text.getLocalBounds().getSize() / 2.f);
		list[i] = text;
		bgList.push_back(rect);
	}
	ComboBoxTitle.setString(defaultOption);

	ComboBoxTitle.setOrigin(ComboBoxTitle.getLocalBounds().getSize() / 2.f);

}

void Gui::ComboBox::update(sf::RenderWindow& target)
{
	sf::Vector2i mousePos = sf::Mouse::getPosition(target);

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

	//if (mousePos.x >= bgList.front().getPosition().x &&
	//	mousePos.x < bgList.back().getPosition().x + bgList.back().getSize().x &&
	//	mousePos.y >= bgList.front().getPosition().y &&
	//	mousePos.y < bgList.back().getPosition().y + bgList.back().getSize().y &&
	//	open)
	//{
	//	std::cout << "HOVERING!\n";
	//}
	//else {
	//	std::cout << "NOO\n";
	//}

	for (int i = 0; i < bgList.size(); ++i)
	{
		if (mousePos.x >= bgList[i].getPosition().x &&
			mousePos.x < bgList[i].getPosition().x + bgList[i].getSize().x &&
			mousePos.y >= bgList[i].getPosition().y &&
			mousePos.y < bgList[i].getPosition().y + bgList[i].getSize().y &&
			open)
		{
			hoverButton[i] = true;
		}
		else {
			hoverButton[i] = false;
		}
	}

}

void Gui::ComboBox::render(sf::RenderWindow& target)
{

	if (open)
	{
		for (auto& BGList : bgList)
		{
			target.draw(BGList);
		}
	}
	target.draw(bg);
	target.draw(ComboBoxTitle);
	if (open)
	{
		for (auto& List : list)
		{
			target.draw(List);
		}
	}
}

void Gui::ComboBox::hoverLogic()
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
		bg.setFillColor(sf::Color::Red);
	}
	else
	{
		soundPlayed = false;
		sound.stop();
		bg.setFillColor(sf::Color::Black);
	}

	for (int i = 0; i < noOfOptions; i++)
	{
		if (hoverButton[i])
		{
			if (!soundPlayedForButtons)
			{
				if (!buttonSound.getStatus() && !buttonSound.getLoop())
				{
					buttonSound.play();
				}
				soundPlayedForButtons = true;
			}
			bgList[i].setFillColor(sf::Color::Red);
		}
		else
		{
			soundPlayedForButtons = false;
			buttonSound.stop();
			bgList[i].setFillColor(sf::Color(100, 100, 100));
		}
	}
}


void Gui::ComboBox::setTitle(int option)
{
	ComboBoxTitle.setString(list[option].getString());
	ComboBoxTitle.setOrigin(ComboBoxTitle.getLocalBounds().getSize() / 2.f);
}