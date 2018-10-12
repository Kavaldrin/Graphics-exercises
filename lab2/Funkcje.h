#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

inline void draw_to_color_pixels(sf::Uint8 *pixels_array, unsigned int size_x, unsigned int x, unsigned int y, unsigned char r, unsigned char g, unsigned char b, unsigned char alfa)
{
	pixels_array[4 * (y * size_x + x) + 0] = r;
	pixels_array[4 * (y * size_x + x) + 1] = g;
	pixels_array[4 * (y * size_x + x) + 2] = b;
	pixels_array[4 * (y * size_x + x) + 3] = alfa;
}
inline void outtextxy(sf::Text &text , sf::RenderWindow& window,const float x,const float y,const std::string &str)
{
	text.setPosition(x, y);
	text.setString(str);
	window.draw(text);
}