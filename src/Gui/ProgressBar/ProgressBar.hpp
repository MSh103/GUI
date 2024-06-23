#ifndef ProgressBar_h
#define ProgressBar_h

#include "../GLOBALS/globals.hpp"

namespace Gui {

class ProgressBar 
{
private:  
  sf::RectangleShape emptyBar;
  sf::RectangleShape progress;
  int progressLevel;
  bool run = false;

  void init();

public:
  ProgressBar();
  ProgressBar(int currentValue, int maxValue);
  void create(int currentValue, int maxValue);

  void setPosition(sf::Vector2f pos);
  void start();

  bool getState() { return run; }

  void update(int currentValue);
  void render(sf::RenderWindow& target);
  
  bool done = false;
};

}


#endif // !ProgressBar
