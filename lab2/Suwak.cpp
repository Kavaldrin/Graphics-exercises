#include "Suwak.h"



Suwak::Suwak():m_pozycja(127)
{
	//rozmiar 255,40
	//

	sf::Uint8 *wypelnienie = new sf::Uint8[255 * 40 * 4];
	for (unsigned x = 0; x < 40; ++x)
		for (unsigned y = 0; y < 255; ++y)
			draw_to_color_pixels(wypelnienie, 40, x, y, y, y, y, 255);
	

	texture.create(40, 255);
	texture.update(wypelnienie);

	sprite.setPosition(670, 50);
	sprite.setTexture(texture);


	//pozycja 670/ 50
	//wielkosc 40/
	obramowka.setPosition(670, 50);
	obramowka.setSize(sf::Vector2f(40,255));
	obramowka.setFillColor(sf::Color::Transparent);
	obramowka.setOutlineColor(sf::Color::Black);
	obramowka.setOutlineThickness(1);



	linia = sf::VertexArray(sf::LinesStrip, 2);
	linia[0].position = sf::Vector2f(660, 50 + 127);
	linia[0].color =sf::Color::Black;
	linia[1].color = sf::Color::Black;
	linia[1].position = sf::Vector2f(720, 50 + 127);
	linia[1].color = sf::Color::Black;

	delete[] wypelnienie;
}


Suwak::~Suwak()
{
}


