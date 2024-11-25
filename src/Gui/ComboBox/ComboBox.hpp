#ifndef COMBOBOX_HPP
#define COMBOBOX_HPP

#include "../GLOBALS/globals.hpp"

namespace Gui {

	class ComboBox {
	private:
		std::vector<sf::Text> list;
		std::vector<sf::RectangleShape> bgList;
		std::vector<sf::Sound> buttonSound;
		std::vector<bool> soundPlayedForButtons;
		std::vector<std::string> options;
		sf::SoundBuffer buffer;
		sf::Text ComboBoxTitle;
		sf::RectangleShape bg;
		sf::Vector2f size;
		sf::Vector2f pos;
		sf::Sound sound;
		sf::Font font;
		bool isMouseOver;
		bool soundPlayed;
		bool open;
		int noOfOptions;

		void init();

	public:

		ComboBox();
		ComboBox(int noOptions, sf::Vector2f pos, std::vector<std::string> options, sf::Vector2f size, std::string defaultOption, sf::Color MainButton, sf::Color SubButtons, int charSize);
		void create(int noOptions, sf::Vector2f pos, std::vector<std::string> options, sf::Vector2f size, std::string defaultOption, sf::Color MainButton, sf::Color SubButtons, int charSize);

		void update(sf::RenderWindow& target);

		void render(sf::RenderWindow& target);

		void setOpenState(bool isOpen) { open = isOpen; }

		bool isOver() { return isMouseOver; }

		bool isOpen() { return open; }

		void hoverLogic(sf::Color normalTitleButton, sf::Color hoverTitle, sf::Color normalButtonColor, sf::Color hoverButtonColor);

		std::vector<bool> hoverButton;

		void setTitle(int option);

		void setMainTextColor(sf::Color color);

		void setSubTextColor(sf::Color color);

		void setTitleCharSize(int size) { ComboBoxTitle.setCharacterSize(size); }
		std::vector<sf::Text> getOptionsText() { return list; }

		void setPosition(sf::Vector2f pos);
	};

}

#endif // !COMBOBOX_HPP