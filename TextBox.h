#pragma once

#include "globals.h"

#define DELETE_KEY 8
#define ENTER_KEY 13
#define ESCAPE_KEY 27

namespace Gui {

	class TextBox {
	private:
		sf::Text text;
		sf::Font font;
		sf::RectangleShape box;
		std::ostringstream os;
		int limit;
		bool hasLimit;
		bool isMouseOver;

		void init();

		void deleteLastChar();

		void inputLogic(int charTyped);

	public:
		bool isSelected;

		TextBox();
		TextBox(bool hasLimit, int limit, int charSize, sf::Color TextColor, sf::Vector2f size, sf::Vector2f pos);
		void create(bool hasLimit, int limit, int charSize, sf::Color TextColor, sf::Vector2f size, sf::Vector2f pos);
		
		void update(sf::RenderWindow& target);

		void input(sf::Event& input);

		void hoverLogic();

		void render(sf::RenderWindow& target);

		bool isOver() { return isMouseOver; }

	};

}