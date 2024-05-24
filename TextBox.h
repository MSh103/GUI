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
        sf::SoundBuffer backBuffer;
        sf::SoundBuffer keyBuffer;
        sf::Sound backSpaceSound;
        sf::Sound keySound;
		sf::RectangleShape box;
		std::ostringstream os;
		std::string submission;
		int limit;
		bool hasLimit;
		bool isMouseOver;
        bool keyPlayed;
        bool backPlayed;
        bool soundState;
		bool save;
		std::ofstream ofs;

		void init();

		void deleteLastChar();

		void inputLogic(int charTyped);


	public:
		bool isSelected;

		TextBox();
		~TextBox();
		TextBox(bool save, bool hasLimit, int limit, int charSize, sf::Color TextColor, sf::Vector2f size, sf::Vector2f pos, bool soundState);
		void create(bool save, bool hasLimit, int limit, int charSize, sf::Color TextColor, sf::Vector2f size, sf::Vector2f pos, bool soundState);
	
		void setFilePath(std::string path) { ofs.open(path, std::ios::app); }

		void update(sf::RenderWindow& target);

		void input(sf::Event& input);

		void hoverLogic();

		void render(sf::RenderWindow& target);

		bool isOver() { return isMouseOver; }

		std::string getSubmittedText() { return submission; }

		void saveToFile() { ofs << submission << std::endl; }

	};

}
