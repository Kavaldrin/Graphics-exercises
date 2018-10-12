#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Suwak.h"
class Kolo
{
public:
	Kolo(double x_pozycja, double y_pozycja, double wys =300, double szer =300);
	~Kolo(){}
	operator sf::CircleShape&() { return circle; }
	void ustawRGB();
	void ustawCMY();
	void ustawHSL();
	void ustawHSV();

protected:
	sf::Texture texture;
	sf::CircleShape circle;
	double m_promien;

};

