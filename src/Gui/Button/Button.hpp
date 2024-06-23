#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "../GLOBALS/globals.hpp"

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

}

#endif // !BUTTON_HPP