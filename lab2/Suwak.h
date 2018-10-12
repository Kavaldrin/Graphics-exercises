#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Funkcje.h"

class Suwak
{
public:
	Suwak();
	~Suwak();
	operator int() { return m_pozycja; }
	void draw(sf::RenderWindow &window);
	void OdswiezSuwak(unsigned y);

protected:
	int m_pozycja;
	sf::VertexArray linia;
	sf::RectangleShape obramowka;
	sf::Texture texture;
	sf::Sprite sprite;
};

inline void Suwak::draw(sf::RenderWindow & window)
{
	window.draw(linia);
	window.draw(sprite);
	window.draw(obramowka);
}

inline void Suwak::OdswiezSuwak(unsigned y)
{
	//670, 50
	m_pozycja = y - 50;
	linia[0].position = sf::Vector2f(660, m_pozycja+50);
	linia[1].position = sf::Vector2f(720, m_pozycja + 50);
}
