#include "Gui/Gui.hpp"

int main(int argc, const char* argv[])
{
	/////////WINDOW HANDLING///////////////////////////
	sf::RenderWindow window(sf::VideoMode(1900, 1080), "GUI DEVELOPMENT", sf::Style::Titlebar | sf::Style::Close);

	window.setFramerateLimit(60);

	sf::Image icon;
	if(!icon.loadFromFile("res/icons/logo.png"))
		std::cerr << "ERR::INIT::WINDOW::ICON::Failed to load window icon.\n";
	window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

	bool running = true;
	///////////////////////////////////////////////////

	////////BUTTON EXAMPLE/////////////////////////////
	sf::RectangleShape bg1(sf::Vector2f(300, 150));
	bg1.setFillColor(sf::Color::White);
	bg1.setOutlineColor(sf::Color::Black);
	bg1.setOutlineThickness(5.5);
	bg1.setPosition({ 100, 150 });
	Gui::Text bg1Title("Button Example:", { 190, 100 }, 20, sf::Color::White);
	Gui::Button button(
		"Button",
		sf::Vector2f(125, 175),
		{ 250, 100 },
		20,
		sf::Color::Black,
		sf::Color::White,
		sf::Color(72, 72, 72)
	);
	sf::RectangleShape term(sf::Vector2f(300, 400));
	term.setFillColor(sf::Color::Black);
	term.setOutlineColor(sf::Color(60, 60, 60));
	term.setOutlineThickness(5.5);
	term.setPosition({ 800, 150 });
	Gui::Text termText("", { 810, 160 }, 20, sf::Color::Green);
	std::stringstream tss; // TSS = term string stream
	////////////////////////////////////////////////////

	////////TEXT EXAMPLE////////////////////////////////
	sf::RectangleShape bg2(sf::Vector2f(300, 150));
	bg2.setFillColor(sf::Color::White);
	bg2.setOutlineColor(sf::Color::Black);
	bg2.setOutlineThickness(5.5);
	bg2.setPosition({ 100, 350 });
	Gui::Text bg2Title("Text Example:", sf::Vector2f(bg2.getPosition().x + 90, bg2.getPosition().y - 40), 20, sf::Color::White);
	Gui::Text text("Text", { bg2.getPosition() + bg2.getSize() / 2.f }, 20, sf::Color::Black);
	text.setOrigin(text.getText().getGlobalBounds().getSize() / 2.f);
	////////////////////////////////////////////////////

	////////COMBO-BOX EXAMPLE///////////////////////////
	std::vector<std::string> options = {
		"Option 1",
		"Option 2",
		"Option 3",
	};
	sf::RectangleShape bg3(sf::Vector2f(300, 400));
	bg3.setFillColor(sf::Color::White);
	bg3.setOutlineColor(sf::Color::Black);
	bg3.setOutlineThickness(5.5f);
	bg3.setPosition({ 100, 550 });
	Gui::Text bg3Title("Combo-Box Example:", sf::Vector2f(bg3.getPosition().x + 55, bg3.getPosition().y - 40), 20, sf::Color::White);
	Gui::ComboBox cBox(
		3,
		sf::Vector2f(
			 bg3.getPosition().x + (bg3.getSize().x / 2.f  - 275 / 2.f),
			 bg3.getPosition().y + (bg3.getSize().y / 2.f - 175)
			),
		options,
		{ 270, 75 },
		"Select an option..",
		sf::Color::Black,
		sf::Color(72, 72, 72),
		20
	);
	sf::RectangleShape term2(sf::Vector2f(300, 400));
	term2.setFillColor(sf::Color::Black);
	term2.setOutlineColor(sf::Color(60, 60, 60));
	term2.setOutlineThickness(5.5f);
	term2.setPosition({ 1150, 150 });
	Gui::Text term2Text("", { 1160, 160 }, 20, sf::Color::Green);
	std::stringstream t2ss;	// t2ss = Term 2 StringStream
	////////////////////////////////////////////////////

	///////PROGRESS-BAR EXAMPLE//////////////
	sf::RectangleShape bg4(sf::Vector2f(300, 150));
	bg4.setFillColor(sf::Color::White);
	bg4.setOutlineColor(sf::Color::Black);
	bg4.setOutlineThickness(5.5);
	bg4.setPosition(sf::Vector2f(450, 150));
	Gui::Text bg4Title("Progress Bar Example:", sf::Vector2f(bg4.getPosition().x + 50, bg4.getPosition().y - 50), 20, sf::Color::White);
	Gui::ProgressBar pBar(0, 100);
	pBar.setPosition(sf::Vector2f(
		bg4.getPosition().x + (bg4.getSize().x / 2.f - 1.25*100/2.f),
		bg4.getPosition().y + (bg4.getSize().y / 2.f - 0.25*100/2.f)
	));
	Gui::Text note(
		"Press the Button to stop/start progress.\nPress 'R' to reset progress bar.",
		 sf::Vector2f(
			bg4.getPosition().x + 7,
			bg4.getPosition().y + (bg4.getSize().y - (32 * 1))
		 ),
		 12,
		 sf::Color::Black
	);
	float i = 0;
	bool stopped = true;
	////////////////////////////////////////////////////

	///////MESSAGE-BOX EXAMPLE//////////////////////////
	sf::RectangleShape bg5(sf::Vector2f(300, 150));
	bg5.setFillColor(sf::Color::White);
	bg5.setOutlineColor(sf::Color::Black);
	bg5.setOutlineThickness(5.5f);
	bg5.setPosition(sf::Vector2f(450, 350));
	Gui::Text bg5Title("Message Box Example:", sf::Vector2f(bg5.getPosition().x + 40, bg5.getPosition().y - 40), 20, sf::Color::White);
	Gui::Button showMBox(
		"Click to show MessageBox",
		sf::Vector2f(
			bg5.getPosition().x + (bg5.getSize().x / 2.f - 250/2.f),
			bg5.getPosition().y + (bg5.getSize().y / 2.f - 100/2.f)
		),
		{ 250, 100 },
		20,
		sf::Color::Black,
		sf::Color::White,
		sf::Color(72, 72, 72)
	);
	sf::RectangleShape term3(sf::Vector2f(300, 400));
	term3.setFillColor(sf::Color::Black);
	term3.setOutlineColor(sf::Color(60, 60, 60));
	term3.setOutlineThickness(5.5f);
	term3.setPosition({ 1150, 600 });
	Gui::Text term3Text("", {1160, 610 }, 20, sf::Color::Green);
	std::stringstream tts3; // tts3 = Term Text String 3
	////////////////////////////////////////////////////

	while(running)
	{
		pBar.setValue(int(i));
		sf::Event ev;
		while (window.pollEvent(ev))
		{
			if(ev.type == sf::Event::Closed)
			{
				window.close();
				running = false;
			}
			if(ev.type == sf::Event::KeyPressed)
			{
				if(ev.key.code == sf::Keyboard::Escape)
				{
					window.close();
					running = false;
				}
				if(ev.key.code == sf::Keyboard::R)
				{
					i = 0;
				}
			}
			if(ev.type == sf::Event::MouseButtonPressed)
			{
				///////BUTTON CLICKING//////////////////////
				if(ev.mouseButton.button == sf::Mouse::Left)
				{
					if(button.isOver())
					{
						tss << "Button is clicked\n";
						stopped = !stopped;
					}
				}
				////////////////////////////////////////////

				///////COMBO-BOX CLICKING///////////////////
				if(ev.mouseButton.button == sf::Mouse::Left)
				{
					if(cBox.isOver())
					{
						cBox.setOpenState(!cBox.isOpen());
					}
					if(cBox.hoverButton[0])
					{
						cBox.setTitle(0);
						t2ss << "Option 1 is clicked\n";
						cBox.setOpenState(false);
					}
					if(cBox.hoverButton[1])
					{
						cBox.setTitle(1);
						t2ss << "Option 2 is clicked\n";
						cBox.setOpenState(false);
					}
					if(cBox.hoverButton[2])
					{
						cBox.setTitle(2);
						t2ss << "Option 3 is clicked\n";
						cBox.setOpenState(false);
					}
				}
				////////////////////////////////////////////

				//////MESSAGE-BOX HANDLING//////////////////
				if(showMBox.isOver())
				{
					#ifdef _WIN32
						Gui::MessageBoxM mBoxW(window, "Title", "Message", MB_OKCANCEL | MB_ICONINFORMATION);
						tts3 << mBoxW.getChoice() << "\n";
					#elif TARGET_OS_MAC
						Gui::MessageBoxM mBoxD("Header", "Message", MB_OKCANCEL | MB_ICONINFORMATION);
						tts3 << mBoxD.getChoice() << "\n";
					#endif
				}
				////////////////////////////////////////////
			}
			if(ev.type == sf::Event::MouseMoved)
			{
				///////BUTTON HOVERING//////////////////////
				if(button.isOver())
				{
					tss << "Button is being hovered\n";
				}
				////////////////////////////////////////////

				///////COMBO-BOX HOVERING///////////////////
				if(cBox.isOpen())
				{
					// WARNING: Can be glitchy
					if(cBox.hoverButton[0])
					{
						t2ss << "Option 1 is being hovered\n";
					}
					if(cBox.hoverButton[1])
					{
						t2ss << "Option 2 is being hovered\n";
					}
					if(cBox.hoverButton[3])
					{
						t2ss << "Option 3 is being hovered\n";
					}
				}
				////////////////////////////////////////////
			}
		}

		//////////UPDATE////////////////////
		button.update(window);
		button.hoverLogic();
		if(tss.str().length() > 290)
		{
			tss.str("");
		}
		std::string temp = tss.str();
		termText.setString(temp);
		cBox.update(window);
		cBox.hoverLogic(sf::Color::Black, sf::Color(50, 50, 50), sf::Color(72, 72, 72), sf::Color(90, 90, 90));
		if(t2ss.str().length() > 310)
		{
			t2ss.str("");
		}
		showMBox.update(window);
		showMBox.hoverLogic();
		if(tts3.str().length() > 30)
		{
			tts3.str("");
		}
		std::string temp3 = tts3.str();
		term3Text.setString(temp3);
		std::string temp2 = t2ss.str();
		term2Text.setString(temp2);
		////////////////////////////////////

		/////////CLEARING///////////////////
		window.clear(sf::Color(72, 72, 72));
		////////////////////////////////////

		///////RENDERING////////////////////

		//////BUTTON EXAMPLE////////////////
		window.draw(bg1);
		window.draw(bg1Title.getText());
		button.render(window);
		window.draw(term);
		window.draw(termText.getText());
		////////////////////////////////////

		//////TEXT EXAMPLE//////////////////
		window.draw(bg2);
		window.draw(bg2Title.getText());
		window.draw(text.getText());
		////////////////////////////////////

		//////COMBO-BOX EXAMPLE/////////////
		window.draw(bg3);
		window.draw(bg3Title.getText());
		cBox.render(window);
		window.draw(term2);
		window.draw(term2Text.getText());
		////////////////////////////////////

		//////PROGRESS-BAR EXAMPLE//////////
		window.draw(bg4);
		window.draw(bg4Title.getText());
		pBar.render(window);
		window.draw(note.getText());
		////////////////////////////////////

		//////MESSAGE-BOX EXAMPLE///////////
		window.draw(bg5);
		window.draw(bg5Title.getText());
		showMBox.render(window);
		window.draw(term3);
		window.draw(term3Text.getText());
		////////////////////////////////////

		////////////////////////////////////

		//////CHG OF BUFFERS////////////////
		window.display();
		////////////////////////////////////

		if(i < 100)
		{
			if(!stopped)
			{
				i += 0.1;
			}
		} else {
			i = 100;
		}
	}

	return 0;
}
