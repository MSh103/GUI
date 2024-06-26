#ifndef ProgressBar_h
#define ProgressBar_h

#include "../GLOBALS/globals.hpp"

namespace Gui {

class ProgressBar 
{
private:  
  sf::RectangleShape emptyBar;
  sf::RectangleShape progress;

  void init();

public:
  ProgressBar();
  ProgressBar(int currentValue, int maxValue);
  void create(int currentValue, int maxValue);

  void setPosition(sf::Vector2f pos);

  void setValue(int value);

  void render(sf::RenderWindow& target);
  
};

}


#endif // !ProgressBar
