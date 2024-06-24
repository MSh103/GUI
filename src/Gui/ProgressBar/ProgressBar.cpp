#include "ProgressBar.hpp" 

using namespace Gui;

void ProgressBar::init()
{
  this->emptyBar.setFillColor(sf::Color(172, 172, 172));
  this->progress.setFillColor(sf::Color::Green);
}

ProgressBar::ProgressBar()
{}

ProgressBar::ProgressBar(int currentValue, int maxValue)
{
  this->progressLevel = currentValue;
  int width = maxValue;
  int height = 0.25 * maxValue;
  
  emptyBar.setSize(sf::Vector2f(width + 4, height + 2));
  progress.setSize(sf::Vector2f(1, height));
}

void ProgressBar::setPosition(sf::Vector2f pos)
{
  emptyBar.setPosition(pos);
  progress.setPosition(sf::Vector2f(
    pos.x + 2,
    pos.y + 1
  ));
}

void ProgressBar::start()
{
  run = true;
}

void ProgressBar::update(int currentValue)
{
  if(run)
  {
    this->progressLevel = currentValue;
    if(progressLevel <= 100)
    {
    progress.setSize(sf::Vector2f(
      progressLevel,
      progress.getSize().y
    ));
    std::cout << "Width: " << progress.getSize().x << "\nHeight: " << progress.getSize().y << '\n';
    progress.setFillColor(sf::Color::Green);
    } else {
      progress.setSize(sf::Vector2f(
        100,
        progress.getSize().y
      ));
      done = true;
      run = false;
      std::cout << done << "\n" << run;
    }
  } else {

  }
}

void ProgressBar::render(sf::RenderWindow& target)
{
  target.draw(emptyBar);
  target.draw(progress);
}

