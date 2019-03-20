#include<iostream> 
#include <iomanip>
#include"SFML\Graphics.hpp"
#include"SFML\Window.hpp"
#include"SFML\System.hpp"



using namespace sf;

//  getTime  ////////////////////////////////////////////////
//  Transform Time in a drawable string          ///////////
//  Input -> Time   Output -> String			///////////
//////////////////////////////////////////////////////////

std::string getTime(Time time) {
	std::string finalString;
	int cents = 0, seconds = 0, minutes = 0, hours = 0;
	float tempTime;

	tempTime = time.asSeconds();

	// Split time in cents, seconds, minutes and hours
	seconds = trunc(tempTime);
	cents = round ((tempTime - seconds)*100);
	hours = seconds / 3600;
	seconds = seconds % 3600;
	minutes = seconds / 60;
	seconds = seconds % 60;
		
	if (hours < 10) {
		finalString = "0" + std::to_string(hours) + " :"; // Adds zero if less than 10
	}
	else {
		finalString = std::to_string(hours) + " :";
	}

	if (minutes < 10) {
		finalString = finalString + "0" + std::to_string(minutes) + " :";
	}
	else {
		finalString = finalString + std::to_string(minutes) + " :";
	}

	if (seconds < 10) {
		finalString = finalString + "0" + std::to_string(seconds) + " :";
	}
	else {
		finalString = finalString + std::to_string(seconds) + " :";
	}

	if (cents < 10) {
		finalString = finalString + "0" + std::to_string(cents);
	}
	else {
		finalString = finalString + std::to_string(cents);
	}
	 
	return finalString;
}


int main()
{
	Clock clock;
	Time elapsed;
	bool timeOn = false, lap1Done = false, lap2Done = false, lap3Done = false, lap4Done = false;

	RenderWindow window(VideoMode(341, 192), "Kronos", Style::Close);	// Window. Not changing size

	Image imageIcon;	// Icon
	imageIcon.loadFromFile("kronosIcon.png");
	window.setIcon(imageIcon.getSize().x , imageIcon.getSize().y , imageIcon.getPixelsPtr());
	
	// BACKGROUND /////////////////////////////////////////////////////////////////////////////////////////
	Texture texture;
	texture.loadFromFile("images/backgroundTime.jpg");	
	Sprite background(texture);
	

	// FONT /////////////////////////////////////////////////////////////////////////////////////////
	Font font;
	if (!font.loadFromFile("fonts/led_real.ttf"))
	{
		std::cout << " Font no trobada " << std::endl;
	}
	Text timeText;	// TIME STRING
	timeText.setFont(font);
	timeText.setPosition(timeText.getCharacterSize()*2.5 ,timeText.getCharacterSize());
	timeText.setString("00 : 00 : 00 : 00");
	
	// BUTTONS //////////////////////////////////////////////////////////////////////////////////////

	Text startText, stopText, resetText, lapText, lap1, lap2, lap3 ,lap4;

	startText.setFont(font);
	startText.setString("Start");
	startText.setPosition(20, 80);
	startText.setOutlineColor(Color::Red);
	
	stopText.setFont(font);
	stopText.setString("Stop/lap");
	stopText.setPosition(115, 80);
	stopText.setOutlineColor(Color::Red);

	resetText.setFont(font);
	resetText.setString("Reset");
	resetText.setPosition(250, 80);
	resetText.setOutlineColor(Color::Red);

	lap1.setFont(font);
	lap1.setCharacterSize(20);
	lap1.setString("-");
	lap1.setPosition(20, 120);

	lap2.setFont(font);
	lap2.setCharacterSize(20);
	lap2.setString("-");
	lap2.setPosition(160, 120);

	lap3.setFont(font);
	lap3.setCharacterSize(20);
	lap3.setString("-");
	lap3.setPosition(20, 150);

	lap4.setFont(font);
	lap4.setCharacterSize(20);
	lap4.setString("-");
	lap4.setPosition(160, 150);

	
	// PROGRAM LOOP /////////////////////////////////////////////////////////////////////////////////////////

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
			if (event.type == Event::MouseMoved) {
				Vector2i mousePos = Mouse::getPosition(window); // Get mouse position
				if (startText.getGlobalBounds().contains( mousePos.x, mousePos.y ) )  // Changes color if mouse is over
				{
					startText.setOutlineThickness(1);
				}
				else startText.setOutlineThickness(0);

				if (stopText.getGlobalBounds().contains(mousePos.x, mousePos.y))
				{
					stopText.setOutlineThickness(1);
				}
				else stopText.setOutlineThickness(0);

				if (resetText.getGlobalBounds().contains(mousePos.x, mousePos.y))
				{
					resetText.setOutlineThickness(1);
				}
				else resetText.setOutlineThickness(0);
			}
			if (event.type == Event::MouseButtonPressed) {	// Mouse click detection
				if (startText.getOutlineThickness() == 1) {
					if (timeOn == false) {
						timeOn = true; // to avoid start once clock is on
						elapsed = clock.restart();
					}
				}
				if (stopText.getOutlineThickness() == 1){	// Split time
					if (!lap1Done)
					{
						lap1.setString(getTime(elapsed));
						lap1Done = true;
						
					}
					else {
						if (!lap2Done)
						{
							lap2.setString(getTime(elapsed));
							lap2Done = true;
						
						}
						else {
							if (!lap3Done)
							{
								lap3.setString(getTime(elapsed));
								lap3Done = true;

							}
							else {
								if (!lap4Done)
								{
									lap4.setString(getTime(elapsed));
									lap4Done = true;

								}
							}
						}
					}
					


				}
				if (resetText.getOutlineThickness() == 1){	// resets clock
					timeOn = true;
					elapsed = clock.restart();
					lap1.setString("-");	// erases lap times
					lap2.setString("-");
					lap3.setString("-");
					lap4.setString("-");
					lap1Done = false, lap2Done = false, lap3Done = false, lap4Done = false;
				}
			}

		}

		if (timeOn) {
			elapsed = clock.getElapsedTime();	// puts time in elapsed variable if start button pressed
		}
						
		timeText.setString(getTime(elapsed));	// timeText gets the time string
		std::cout << elapsed.asSeconds() << std::endl;	// just for debugging

		//DRAW
		window.clear();
		window.draw(background);
		window.draw(timeText);
		window.draw(startText);
		window.draw(stopText);
		window.draw(resetText);
		window.draw(lap1);
		window.draw(lap2);
		window.draw(lap3);
		window.draw(lap4);
		window.display();
	}

	return 0;
}