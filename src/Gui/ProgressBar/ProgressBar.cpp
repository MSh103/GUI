#include "ProgressBar.hpp" 

using namespace Gui;

void ProgressBar::init()
{
  this->emptyBar.setFillColor(sf::Color(150, 150, 150));
  this->progress.setFillColor(sf::Color(0, 150, 0));
}

ProgressBar::ProgressBar()
{}

ProgressBar::ProgressBar(int currentValue, int maxValue)
{
  int width = 1.25 * maxValue;
  int height = 0.25 * maxValue;
  
  emptyBar.setSize(sf::Vector2f(width + 8, height + 4));
  progress.setSize(sf::Vector2f(1, height));
  init();
}

void ProgressBar::setPosition(sf::Vector2f pos)
{
  emptyBar.setPosition(pos);
  progress.setPosition(sf::Vector2f(
    pos.x + 4,
    pos.y + 2
  ));
}

void ProgressBar::setValue(int value)
{
  int maxValue = emptyBar.getSize().x;
  int width = 1.25 * value;
  int height = progress.getSize().y;
  sf::Vector2f pos = emptyBar.getPosition();

  if(width < maxValue)
  {
    progress.setSize(sf::Vector2f(width, height));
    progress.setPosition(sf::Vector2f(
      pos.x + 4,
      pos.y + 2
    ));
  } else {
    progress.setSize(sf::Vector2f(maxValue - 8, 0.25 * maxValue - 4));
    progress.setPosition(sf::Vector2f(
      pos.x + 4,
      pos.y + 2
    ));
  }
}

void ProgressBar::render(sf::RenderWindow& target)
{
  target.draw(emptyBar);
  target.draw(progress);
}
