#include "ComboBox.hpp"

void Gui::ComboBox::init()
{
	if (!font.loadFromFile("res/font/font.OTF"))
	{
		std::cerr << "Failed to load Font!\n";
	}
	ComboBoxTitle.setFont(font);

	if (!buffer.loadFromFile("res/sfx/buttonhover.wav"))
	{
		std::cerr << "Failed to load Soundbuffer!\n";
	}
	sound.setBuffer(buffer);
	sound.setLoop(false);

	open = false;
}

Gui::ComboBox::ComboBox()
{
}

Gui::ComboBox::ComboBox(int noOptions, sf::Vector2f pos, std::vector<std::string> options, sf::Vector2f size, std::string defaultOption, sf::Color MainButton, sf::Color SubButtons, int charSize)
{
	init();
	this->noOfOptions = noOptions;
	this->pos = pos;
	this->size = size;
	this->options = options;

	for (int i = 0; i < this->noOfOptions; i++)
	{
		sf::Sound ssound;
		ssound.setBuffer(buffer);
		ssound.setLoop(false);
		buttonSound.push_back(ssound);
		hoverButton.push_back(false);
		soundPlayedForButtons.push_back(false);
	}

	bg.setSize({ this->size.x, this->size.y });
	bg.setFillColor(MainButton);
	bg.setPosition({ this->pos.x, this->pos.y});

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
		rect.setFillColor(SubButtons);
		rect.setPosition(sf::Vector2f(
			pos.x,
			pos.y + (i + 1) * size.y
		));
		text.setFont(font);
		text.setCharacterSize(charSize);
		if (!this->options.empty() && i < this->options.size()) {
			text.setString(this->options[i]);
		}
		text.setPosition(pos.x + (size.x / 2.f), pos.y + (i + 1.5) * (size.y));
		text.setOrigin(text.getLocalBounds().getSize() / 2.f);
		text.setFillColor(sf::Color::White);
		list[i] = text;
		bgList.push_back(rect);
	}

	ComboBoxTitle.setString(defaultOption);
	ComboBoxTitle.setCharacterSize(charSize);
	ComboBoxTitle.setOrigin(ComboBoxTitle.getLocalBounds().getSize() / 2.f);
}

void Gui::ComboBox::create(int noOptions, sf::Vector2f pos, std::vector<std::string> options, sf::Vector2f size, std::string defaultOption, sf::Color MainButton, sf::Color SubButtons, int charSize)
{
	init();
	this->noOfOptions = noOptions;
	this->pos = pos;
	this->size = size;
	this->options = options;

	for (int i = 0; i < this->noOfOptions; i++)
	{
		sf::Sound ssound;
		ssound.setBuffer(buffer);
		ssound.setLoop(false);
		buttonSound.push_back(ssound);
		hoverButton.push_back(false);
		soundPlayedForButtons.push_back(false);
	}

	bg.setSize({ this->size.x, this->size.y });
	bg.setFillColor(MainButton);
	bg.setPosition({ this->pos.x, this->pos.y});

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
		rect.setFillColor(SubButtons);
		rect.setPosition(sf::Vector2f(
			pos.x,
			pos.y + (i + 1) * size.y
		));
		text.setFont(font);
		text.setCharacterSize(charSize);
		if (!this->options.empty() && i < this->options.size()) {
			text.setString(this->options[i]);
		}
		text.setPosition(pos.x + (size.x / 2.f), pos.y + (i + 1.5) * (size.y));
		text.setOrigin(text.getLocalBounds().getSize() / 2.f);
		text.setFillColor(sf::Color::White);
		list[i] = text;
		bgList.push_back(rect);
	}

	ComboBoxTitle.setString(defaultOption);
	ComboBoxTitle.setCharacterSize(charSize);
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

void Gui::ComboBox::hoverLogic(sf::Color normalTitleButton, sf::Color hoverTitle, sf::Color normalButtonColor, sf::Color hoverButtonColor)
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
		bg.setFillColor(hoverTitle);
	}
	else
	{
		soundPlayed = false;
		sound.stop();
		bg.setFillColor(normalTitleButton);
	}

	for (int i = 0; i < hoverButton.size(); i++)
	{
		if (hoverButton[i])
		{
			if (!soundPlayedForButtons[i])
			{
				if (!buttonSound[i].getStatus() && !buttonSound[i].getLoop())
				{
					buttonSound[i].play();
				}
				soundPlayedForButtons[i] = true;
			}
			bgList[i].setFillColor(hoverButtonColor);
		}
		else
		{
			soundPlayedForButtons[i] = false;
			buttonSound[i].stop();
			bgList[i].setFillColor(normalButtonColor);
		}
	}
}


void Gui::ComboBox::setTitle(int option)
{
	ComboBoxTitle.setString(list[option].getString());
	ComboBoxTitle.setOrigin(ComboBoxTitle.getLocalBounds().getSize() / 2.f);
}

void Gui::ComboBox::setMainTextColor(sf::Color color)
{
	ComboBoxTitle.setFillColor(color);
}

void Gui::ComboBox::setSubTextColor(sf::Color color)
{
	for (auto& List : list)
	{
		List.setFillColor(color);
	}
}
