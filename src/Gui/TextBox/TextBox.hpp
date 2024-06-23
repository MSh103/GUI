#ifndef TEXTBOX_HPP
#define TEXTBOX_HPP

#include "../GLOBALS/globals.hpp"

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
		std::string submission;
		int limit;
		bool hasLimit;
		bool isMouseOver;
		bool save;
		std::ofstream ofs;

		void init();

		void deleteLastChar();

		void inputLogic(int charTyped);


	public:
		bool isSelected;

		TextBox();
		~TextBox();
		TextBox(bool save, bool hasLimit, int limit, int charSize, sf::Color TextColor, sf::Vector2f size, sf::Vector2f pos);
		void create(bool save, bool hasLimit, int limit, int charSize, sf::Color TextColor, sf::Vector2f size, sf::Vector2f pos);
	
		void setFilePath(std::string path) {
			std::stringstream filess;
			filess << "mkdir -p " << path.substr(0, path.find_last_of("/"));
			system(filess.str().c_str());
			ofs.open(path, std::ios::app);

			if (!ofs.is_open()) {
				std::cerr << "Error opening file" << std::endl;
			}
		}

		void update(sf::RenderWindow& target);

		void input(sf::Event& input);

		void hoverLogic();

		void render(sf::RenderWindow& target);

		bool isOver() { return isMouseOver; }

		std::string getSubmittedText() { return submission; }

		void saveToFile() { ofs << submission << std::endl; }

	};

}

#endif // !TEXTBOX_HPP