#include "ProgressBar.hpp" 

using namespace Gui;

void ProgressBar::init()
{
  this->emptyBar.setFillColor(sf::Color(240, 240, 240));
  this->progress.setFillColor(sf::Color(0, 150, 0));
  if(!font.loadFromFile("res/font/font.OTF"))
  {
    std::cerr << "Failed to load font!\n";
  }
  percentage.setFont(font);
  percentage.setFillColor(sf::Color(72, 72, 72));
  ss.str("");
}

ProgressBar::ProgressBar()
{}

ProgressBar::ProgressBar(int currentValue, int maxValue)
{
  int width = 1.25 * maxValue;
  int height = 0.25 * maxValue;
  this->maxValue = maxValue;
  
  emptyBar.setSize(sf::Vector2f(width + 8, height + 4));
  progress.setSize(sf::Vector2f(1, height));
  init();
  percentage.setCharacterSize(0.65 * height);
  ss << currentValue << "/" << maxValue << " %";
  percentage.setPosition(sf::Vector2f(
    emptyBar.getPosition().x + emptyBar.getSize().x / 2.f,
    emptyBar.getPosition().y + emptyBar.getSize().y / 2.f
  ));
  percentage.setString(ss.str());
  percentage.setOrigin(sf::Vector2f(
    percentage.getGlobalBounds().getSize().x / 2.f,
    percentage.getGlobalBounds().getSize().y / 2.f + 5
  ));
}

void ProgressBar::setPosition(sf::Vector2f pos)
{
  emptyBar.setPosition(pos);
  progress.setPosition(sf::Vector2f(
    pos.x + 4,
    pos.y + 2
  ));
  percentage.setPosition(sf::Vector2f(
    emptyBar.getPosition().x + emptyBar.getSize().x / 2.f,
    emptyBar.getPosition().y + emptyBar.getSize().y / 2.f
  ));
}

void ProgressBar::setValue(int value)
{
  int maxValue = emptyBar.getSize().x;
  int width = 1.25 * value;
  int height = progress.getSize().y;
  sf::Vector2f pos = emptyBar.getPosition();

  int actualMaxValue = this->maxValue;
  
  if(width < maxValue)
  {
    progress.setSize(sf::Vector2f(width, height));
    progress.setPosition(sf::Vector2f(
      pos.x + 4,
      pos.y + 2
    ));
    ss.str("");
    ss << value << "/" << actualMaxValue << " %";
    percentage.setString(ss.str());
    percentage.setOrigin(sf::Vector2f(
      percentage.getGlobalBounds().getSize().x / 2.f,
      percentage.getGlobalBounds().getSize().y / 2.f + 5
    ));
    percentage.setPosition(sf::Vector2f(
      emptyBar.getPosition().x + emptyBar.getSize().x / 2.f,
      emptyBar.getPosition().y + emptyBar.getSize().y / 2.f
    ));
  } else {
    progress.setSize(sf::Vector2f(maxValue - 8, 0.25 * maxValue - 4));
    progress.setPosition(sf::Vector2f(
      pos.x + 4,
      pos.y + 2
    ));
    percentage.setPosition(sf::Vector2f(
      emptyBar.getPosition().x + emptyBar.getSize().x / 2.f,
      emptyBar.getPosition().y + emptyBar.getSize().y / 2.f
    ));
  }
}

void ProgressBar::render(sf::RenderWindow& target)
{
  target.draw(emptyBar);
  target.draw(progress);
  target.draw(percentage);
}
