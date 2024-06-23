#ifndef TEXT_HPP
#define TEXT_HPP

#include "../GLOBALS/globals.hpp"

namespace Gui {

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
        
        void setString(std::string& msg) {text.setString(msg);}

	};

}

#endif // !TEXT_HPP