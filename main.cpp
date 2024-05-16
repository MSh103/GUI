#include "Gui.h"

int state = 0;
int titleState = 0;
int optionsState = 1;

int main(int argc, const char* argv[])
{
	sf::RenderWindow window(sf::VideoMode(1400, 800), "GUI CREATING");
	sf::RenderWindow target;


	Gui::Button button(
		"Quit",
		sf::Vector2f(50, window.getSize().y / 2.f + 120),
		{ 500, 100 },
		45,
		sf::Color(100, 100, 255),
		sf::Color::White,
		sf::Color(255, 165, 0)
	);

	Gui::Button button1(
		"Start",
		sf::Vector2f(50, window.getSize().y / 2.f - 120),
		{ 500, 100 },
		45,
		sf::Color(100, 100, 255),
		sf::Color::White,
		sf::Color(255, 165, 0)
	);


	Gui::Button button2(
		"Options",
		sf::Vector2f(50, window.getSize().y / 2.f),
		{ 500, 100 },
		45,
		sf::Color(100, 100, 255),
		sf::Color::White,
		sf::Color(255, 165, 0)
	);


	Gui::Text title("Welcome Message!", { 50, 125 }, 75, sf::Color::White);


	sf::CircleShape circle(200);
	circle.setFillColor(sf::Color::Blue);

	std::vector < std::string> options = {
		"1920 / 1080",
		"1400 / 800",
		"1280 / 800",
		"Back..",
	};

	std::vector <bool> noOfButtons = {
		false,
		false,
		false,
		false,
	};

	Gui::ComboBox comboBox(
		options.size(),
		sf::Vector2f(window.getSize().x / 2.f + 50, 100),
		options,
		{ 250, 80 },
		"Select...",
		noOfButtons
	);

	bool running = true;

	while (running)
	{
		sf::Event ev;
		while (window.pollEvent(ev))
		{
			if (ev.type == sf::Event::Closed)
			{
				window.close();
				running = false;
			}
			if (ev.type == sf::Event::MouseButtonPressed)
			{
				if (ev.mouseButton.button == sf::Mouse::Left)
				{
					if (state == titleState)
					{
						if (button.isOver())
						{
							window.close();
							running = false;
						}
						if (button1.isOver())
						{
							target.create(sf::VideoMode(400, 400), "TEST");
							target.setPosition(sf::Vector2i(
								sf::VideoMode::getDesktopMode().width,
								0
							));
						}
						if (button2.isOver())
						{
							state = optionsState;
						}
					}
					else if (state == optionsState)
					{
						if (comboBox.isOver() && !comboBox.isOpen())
						{
							comboBox.setOpenState(true);
						}
						else if(comboBox.isOver() && comboBox.isOpen()) {
							comboBox.setOpenState(false);
						}
						if (comboBox.hoverButton[0])
						{
							comboBox.setTitle(0);
							window.close();
							window.create(sf::VideoMode(1920, 1080), "GUI CREATING");
							window.setPosition({ 0, 0 });
						}
						if (comboBox.hoverButton[1])
						{
							comboBox.setTitle(1);
							window.close();
							window.create(sf::VideoMode(1400, 800), "GUI CREATING");
							window.setPosition(sf::Vector2i(
								sf::VideoMode::getDesktopMode().width / 2 - (window.getSize().x / 2),
								sf::VideoMode::getDesktopMode().height / 2 - (window.getSize().y / 2)
							));
						}
						if (comboBox.hoverButton[2])
						{
							comboBox.setTitle(2);
							window.close();
							window.create(sf::VideoMode(1280, 800), "GUI CREATING");
							window.setPosition(sf::Vector2i(
								sf::VideoMode::getDesktopMode().width / 2 - (window.getSize().x / 2),
								sf::VideoMode::getDesktopMode().height / 2 - (window.getSize().y / 2)
							));
						}
						if (comboBox.hoverButton[3])
						{
							state = titleState;
						}
					}
				}
			}
			if (ev.type == sf::Event::KeyPressed)
			{
				if (ev.key.code == sf::Keyboard::F11)
				{
					window.close();
					window.create(sf::VideoMode::getDesktopMode(), "GUI CREATING", sf::Style::Fullscreen);
				}
				if (state == optionsState)
				{
					if (ev.key.code == sf::Keyboard::Escape)
					{
						state = titleState;
					}
				}
			}
		}
		sf::Event event;
		while (target.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				target.close();
			}
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape) { target.close(); }
			}
		}

		if (state == titleState)
		{
			if (button.isOver())
			{
				button.setTextPosition(sf::Vector2f(
					(button.getButtonPosition().x + 100.f) + 50.f,
					button.getButtonPosition().y + 30.f
				));
			}
			else {
				button.setTextPosition(sf::Vector2f(
					button.getButtonPosition().x + 100.f,
					button.getButtonPosition().y + 30.f
				));
			}

			if (button1.isOver())
			{
				button1.setTextPosition(sf::Vector2f(
					(button1.getButtonPosition().x + 100.f) + 50.f,
					button1.getButtonPosition().y + 30.f
				));
			}
			else {
				button1.setTextPosition(sf::Vector2f(
					button1.getButtonPosition().x + 110.f,
					button1.getButtonPosition().y + 30.f
				));
			}

			if (button2.isOver())
			{
				button2.setTextPosition(sf::Vector2f(
					(button2.getButtonPosition().x + 100.f) + 50.f,
					button2.getButtonPosition().y + 30.f
				));
			}
			else {
				button2.setTextPosition(sf::Vector2f(
					button2.getButtonPosition().x + 130.f,
					button2.getButtonPosition().y + 30.f
				));
			}
		}

		if (state == titleState)
		{
			button1.update(window);
			button.update(window);
			button2.update(window);

			window.clear(sf::Color(100, 100, 255));

			button.hoverLogic();
			button1.hoverLogic();
			button2.hoverLogic();
			button1.render(window);
			button.render(window);
			button2.render(window);
			window.draw(title.getText());

			window.display();

			target.clear(sf::Color::Magenta);

			circle.setOrigin(circle.getLocalBounds().getSize() / 2.f);
			circle.setPosition(sf::Vector2f(
				target.getSize().x / 2.f,
				target.getSize().y / 2.f
			));

			target.draw(circle);

			target.display();
		}
		else if (state == optionsState)
		{
			comboBox.update(window);
			comboBox.hoverLogic();

			window.clear(sf::Color(100, 100, 255));

			comboBox.render(window);

			window.display();
		}
	}

	return 0;
}