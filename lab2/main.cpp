
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "font.h"
#include "Kolo.h"
#include "Suwak.h"
#include "Funkcje.h"
#include <string>
#include <iostream>

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "GFK Lab 02", sf::Style::Titlebar | sf::Style::Close);
	Suwak suwak;
	Kolo HSL(40, 20); HSL.ustawHSL();
	sf::CircleShape filtr_HSL2;
	filtr_HSL2.setRadius(250 / 2); filtr_HSL2.setPosition(40, 20); filtr_HSL2.setOutlineColor(sf::Color::Transparent);
	filtr_HSL2.setFillColor(sf::Color(255, 255, 255, suwak*2));
	sf::CircleShape filtr_HSL3;
	filtr_HSL3.setRadius(250 / 2); filtr_HSL3.setPosition(40, 20); filtr_HSL3.setOutlineColor(sf::Color::Transparent);
	filtr_HSL3.setFillColor(sf::Color(0, 0, 0, 255-(suwak*2)));


	Kolo HSV(330, 20); HSV.ustawHSV();
	sf::CircleShape filtr_HSV;
	filtr_HSV.setRadius(250 / 2); filtr_HSV.setPosition(330, 20); filtr_HSV.setOutlineColor(sf::Color::Transparent);
	filtr_HSV.setFillColor(sf::Color(0, 0, 0, 255 - suwak));

	Kolo CMY(40, 290); CMY.ustawCMY();
	sf::CircleShape filtr_Y;
	filtr_Y.setRadius(250 / 2); filtr_Y.setPosition(40, 290); filtr_Y.setOutlineColor(sf::Color::Transparent);
	filtr_Y.setFillColor(sf::Color(0, 0,255- suwak));
	Kolo RGB(330, 290); RGB.ustawRGB();
	sf::CircleShape filtr_B;
	filtr_B.setRadius(250 / 2); filtr_B.setPosition(330, 290); filtr_B.setOutlineColor(sf::Color::Transparent);
	filtr_B.setFillColor(sf::Color(0, 0, suwak));
	
	sf::Clock clock;
	sf::Time time = sf::Time::Zero;

	sf::Font font;
	font.loadFromMemory(font_data, font_data_size);
	sf::Text text;
	text.setFont(font);
	text.setCharacterSize(15);
	text.setFillColor(sf::Color::Black);
	std::string temp;


	unsigned int FPS = 0, frame_counter = 0;
	std::string fps = "FPS: 0";
	//inicjalizacja 
	clock.restart().asMilliseconds();
	while (window.isOpen())
	{
		//black 0 0 0 255
		sf::Event event;
		window.clear(sf::Color::White);

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::MouseButtonPressed) {
				if (event.mouseButton.x >= 670 && event.mouseButton.y >= 50
					&& event.mouseButton.x <= 710 && event.mouseButton.y <= 305) {
					
					suwak.OdswiezSuwak(event.mouseButton.y);
					filtr_B.setFillColor(sf::Color(0, 0, suwak));
					filtr_Y.setFillColor(sf::Color(0, 0, 255 - suwak));
					filtr_HSV.setFillColor(sf::Color(0, 0, 0, 255-suwak));
					filtr_HSL2.setFillColor(sf::Color(255, 255, 255, suwak*2));
					filtr_HSL3.setFillColor(sf::Color(0, 0, 0, 255 - (suwak * 2)));



					//reszta opcji odswiezania kola
				}
			}
			if ((event.type == sf::Event::MouseMoved) && (sf::Mouse::isButtonPressed(sf::Mouse::Left))) {
				if (event.mouseMove.x >= 670 && event.mouseMove.y >= 50
					&& event.mouseMove.x <= 710 && event.mouseMove.y <= 305) {
					suwak.OdswiezSuwak(event.mouseMove.y);
					filtr_B.setFillColor(sf::Color(0, 0, suwak));
					filtr_Y.setFillColor(sf::Color(0, 0, 255 - suwak));
					filtr_HSV.setFillColor(sf::Color(0, 0, 0, 255 - suwak));
					filtr_HSL2.setFillColor(sf::Color(255, 255, 255, suwak*2));
					filtr_HSL3.setFillColor(sf::Color(0, 0, 0, 255 - (suwak * 2)));



					//reszta opcji odswiezania kola
				}
			}
		}
		//tu wyrysowaæ wszystko na ekran

		//tu wypisaæ na ekran wartoœæ FPS
		if (clock.getElapsedTime().asSeconds() >= 1.0f)
		{
			FPS = (unsigned int)((float)frame_counter / clock.getElapsedTime().asSeconds());
			clock.restart();
			fps = "FPS: " + std::to_string(FPS);
			frame_counter = 0;
		}
		frame_counter++;
		///tekst ///////////////
		
		outtextxy(text, window, 325, 285, "RGB");
		outtextxy(text, window, 35, 285, "CMY");
		outtextxy(text, window, 325, 15, "HSV");
		outtextxy(text, window, 35, 15, "HSL");
		outtextxy(text, window, 550, 500,"B = " + std::to_string(suwak));
		outtextxy(text, window, 270, 500, "Y = " + std::to_string((static_cast<int>(suwak/255.0*100)))+"%");
		outtextxy(text, window, 550, 500, "B = " + std::to_string(suwak));
		temp = std::to_string(static_cast<int>(suwak / 255.0 * 100) / 100.0);
		temp.resize(5);
		outtextxy(text, window, 270, 250, "L = " + temp);
		outtextxy(text, window, 550, 250, "V = " + temp);



		///teskt //////////////
		//drawing ///////////////
		outtextxy(text, window, 640, 340, fps);
		suwak.draw(window);
		window.draw(RGB);
		window.draw(filtr_B,sf::BlendAdd);
		window.draw(CMY);
		window.draw(filtr_Y, sf::BlendAdd);
		window.draw(HSV);
		window.draw(filtr_HSV,sf::BlendAlpha);
		window.draw(HSL);
		if(suwak > 127)
			window.draw(filtr_HSL2, sf::BlendAlpha);
		else
			window.draw(filtr_HSL3, sf::BlendAlpha);
		// drawing /////////
		

		window.display();
	}
}