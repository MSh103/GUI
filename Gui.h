#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>
#include <vector>

namespace Gui {

	class Button {
	private:
		//	Variables
		sf::Font font;
		sf::Text fg;
		sf::RectangleShape bg;
		sf::Vector2f pos;
		bool isMouseOver;
		sf::SoundBuffer buffer;
		sf::Sound sound;
		float hoverColor[3];
		float normalColor[3];
		bool soundPlayed;

		// Functions
		void init();

	public:

		Button();
		Button(std::string msg, sf::Vector2f pos, sf::Vector2f buttonSize, int charSize, sf::Color bgColor, sf::Color fgColor, sf::Color bgHoverColor);
		void create(std::string msg, sf::Vector2f pos, sf::Vector2f buttonSize, int charSize, sf::Color bgColor, sf::Color fgColor, sf::Color bgHoverColor);

		void update(sf::RenderWindow& target);

		void render(sf::RenderWindow& target);

		bool isOver() { return isMouseOver; }

		void hoverLogic();

		void setTextPosition(sf::Vector2f position);

		void moveText(sf::Vector2f position);

		sf::Vector2f getTextPosition() { return fg.getPosition(); }

		sf::Vector2f getButtonPosition() { return bg.getPosition(); }

	};

	class TextBox {
	private:

	public:

	};

	class Text {
	private:
		sf::Font font;
		sf::Text text;

		void init();

	public:
		
		Text();
		Text(std::string msg, sf::Vector2f pos, int charSize, sf::Color color);
		void create(std::string msg, sf::Vector2f pos, int charSize, sf::Color color);

		sf::Text getText() { return text; }

	};


	class ComboBox {
	private:
		std::vector<sf::Text> list;
		std::vector<sf::RectangleShape> bgList;
		sf::Text ComboBoxTitle;
		sf::Font font;
		sf::Vector2f size;
		sf::Vector2f pos;
		sf::RectangleShape bg;
		bool isMouseOver;
		sf::SoundBuffer buffer;
		sf::Sound sound;
		sf::Sound buttonSound;
		bool soundPlayed;
		int noOfOptions;
		std::vector<std::string> options;
		bool open;
		bool anyButtonHovered;
		bool soundPlayedForButtons;

		void init();

	public:

		ComboBox();
		ComboBox(int noOptions, sf::Vector2f pos, std::vector<std::string> options, sf::Vector2f size, std::string defaultOption, std::vector<bool> noOfButtons);
		void create(int noOptions, sf::Vector2f pos, std::vector<std::string> options, sf::Vector2f size, std::string defaultOption, std::vector<bool> noOfButtons);

		void update(sf::RenderWindow& target);

		void render(sf::RenderWindow& target);

		void setOpenState(bool isOpen) { open = isOpen; }

		bool isOver() { return isMouseOver; }

		bool isOpen() { return open; }

		void hoverLogic();

		std::vector<bool> hoverButton;

		void setTitle(int option);
	};

};

