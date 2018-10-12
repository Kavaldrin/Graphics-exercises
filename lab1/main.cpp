// Calosc mozna dowolnie edytowac wedle uznania. 

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "C:\Users\xstilliosx\Desktop\Projekty\Paint\font.h"
#include <iostream>
#include <vector>
#include <cmath>

class Menu : public sf::Drawable
{
private:
	sf::Font font;
	sf::Text *text;
	sf::RectangleShape *rectangle;

	sf::Texture *colors_texture;
	sf::Sprite *colors_sprite;
	sf::Uint8 *colors_pixels;
	const unsigned int colors_size_x = 765;
	const unsigned int colors_size_y = 60;
	inline void draw_to_color_pixels(unsigned int x, unsigned int y, unsigned char r, unsigned char g, unsigned char b)
	{
		colors_pixels[4 * (y * colors_size_x + x) + 0] = r;
		colors_pixels[4 * (y * colors_size_x + x) + 1] = g;
		colors_pixels[4 * (y * colors_size_x + x) + 2] = b;
		colors_pixels[4 * (y * colors_size_x + x) + 3] = 255;
	}

public:
	Menu()
	{
		font.loadFromMemory(font_data, font_data_size);
		text = new sf::Text;
		text->setFont(font);
		text->setCharacterSize(12);
		text->setFillColor(sf::Color::White);

		rectangle = new sf::RectangleShape(sf::Vector2f(796, 536));
		rectangle->setFillColor(sf::Color::Transparent);
		rectangle->setOutlineColor(sf::Color::White);
		rectangle->setOutlineThickness(1.0f);
		rectangle->setPosition(2, 62);

		unsigned int x, y;
		colors_pixels = new sf::Uint8[colors_size_x * colors_size_y * 4];
		for (x = 0; x<255; x++)
			for (y = 0; y < 30; y++)
			{
				draw_to_color_pixels(x, y, x, 255, 0);
				draw_to_color_pixels(x + 255, y, 255, 255 - x, 0);
				draw_to_color_pixels(x + 510, y, 255, 0, x);
				draw_to_color_pixels(254 - x, y + 30, 0, 255, 255 - x);
				draw_to_color_pixels(509 - x, y + 30, 0, x, 255);
				draw_to_color_pixels(764 - x, y + 30, 255 - x, 0, 255);
			}

		colors_texture = new sf::Texture();
		colors_texture->create(colors_size_x, colors_size_y);
		colors_texture->update(colors_pixels);

		colors_sprite = new sf::Sprite();
		colors_sprite->setTexture(*colors_texture);
		colors_sprite->setPosition(1, 1);
	}

	void outtextxy(sf::RenderTarget& target, float x, float y, wchar_t *str) const
	{
		text->setPosition(x, y);
		text->setString(str);
		target.draw(*text);
	}

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		outtextxy(target, 5, 600, L"f - wybór koloru rysowania");
		outtextxy(target, 5, 615, L"b - wybór koloru wype³niania");
		outtextxy(target, 5, 630, L"l - rysowanie linii");

		outtextxy(target, 200, 600, L"r - rysowanie prostok¹ta");
		outtextxy(target, 200, 615, L"a - rysowanie wype³nionego prostok¹ta");
		outtextxy(target, 200, 630, L"c - rysowanie okrêgu");

		outtextxy(target, 470, 600, L"w - zapis do pliku");
		outtextxy(target, 470, 615, L"o - odczyt z pliku");
		outtextxy(target, 470, 630, L"esc - wyjœcie");

		outtextxy(target, 650, 615, L"Aktualne:");

		target.draw(*rectangle);
		target.draw(*colors_sprite);
	}
};

void DisplayActualLetter(sf::RenderWindow &target, const char c)
{
	sf::Font font;
	font.loadFromMemory(font_data, font_data_size);
	sf::Text *text = new sf::Text;
	text->setFont(font);
	text->setCharacterSize(12);
	text->setFillColor(sf::Color::White);
	text->setPosition(720, 615);
	text->setString(c);
	target.draw(*text);
}
void SetActualLetter(sf::Event& event, char *letter)
{
	if (event.key.code == sf::Keyboard::F)
		*letter = 'f';
	else if (event.key.code == sf::Keyboard::A)
		*letter = 'a';
	else if (event.key.code == sf::Keyboard::B)
		*letter = 'b';
	else if (event.key.code == sf::Keyboard::L)
		*letter = 'l';
	else if (event.key.code == sf::Keyboard::R)
		*letter = 'r';
	else if (event.key.code == sf::Keyboard::C)
		*letter = 'c';
	else if (event.key.code == sf::Keyboard::W) //zapis
		*letter = 'w';
	else if (event.key.code == sf::Keyboard::O) //odczyt
		*letter = 'o';

}


void SetColor(sf::Color &col,const int x_coord,const int y_coord)
{
	if ((x_coord >= 0 && x_coord < 3 * 512) && (y_coord >= 0 && y_coord < 60)) {
		if (y_coord >= 0 && y_coord < 30) {
			if (x_coord >= 0 && x_coord < 256)
				col = sf::Color(x_coord, 255, 0);
			else if (x_coord >= 256 && x_coord < (2 * 256))
				col = sf::Color(255, 255 - (x_coord % 256), 0);
			else if (x_coord >= (2 * 256) && x_coord < (3 * 256))
				col = sf::Color(255, 0, x_coord % 256);
		}
		else if (y_coord >= 30 && y_coord < 60) {
			if (x_coord >= 0 && x_coord < 256)
				col = sf::Color(0, 255, x_coord);
			else if (x_coord >= 256 && x_coord < (2 * 256))
				col = sf::Color(0, 255 - (x_coord % 256), 255);
			else if (x_coord >= (2 * 256) && x_coord < (3 * 256))
				col = sf::Color((x_coord % 256) - 255, 0, 255);
		}
	}
}

inline void updateLine(sf::VertexArray& line, const int&mouseX, const int&mouseY)
{
	line[1].position = sf::Vector2f(mouseX, mouseY);
}

inline void updateCircle(sf::CircleShape& circle, sf::Vector2i& starting_circle, const int &mouseX, const int &mouseY) 
{
	circle.setRadius(sqrt((starting_circle.x - mouseX)*(starting_circle.x - mouseX)
		+ (starting_circle.y - mouseY)*(starting_circle.y - mouseY)) / 2.0);
	circle.setPosition(starting_circle.x + (mouseX - starting_circle.x) / 2.0 - circle.getRadius(), starting_circle.y + (mouseY - starting_circle.y) / 2.0 - circle.getRadius());
	circle.setRotation(atan2f(mouseX - starting_circle.x, mouseY - starting_circle.y));
}
inline void updateRectangle(sf::RectangleShape& rectangle, sf::Vector2i& starting_rectangle, const int &mouseX, const int &mouseY)
{
	if (mouseX > starting_rectangle.x && mouseY > starting_rectangle.y) {
		rectangle.setPosition(starting_rectangle.x, starting_rectangle.y);
		rectangle.setSize(static_cast<sf::Vector2f>(sf::Vector2i(mouseX,mouseY) - starting_rectangle));
	}
	else if (mouseX > starting_rectangle.x && mouseY < starting_rectangle.y) {
		rectangle.setPosition(starting_rectangle.x, mouseY);
		rectangle.setSize(sf::Vector2f(mouseX - starting_rectangle.x, starting_rectangle.y - mouseY));
	}
	else if (mouseX < starting_rectangle.x && mouseY > starting_rectangle.y) {
		rectangle.setPosition(mouseX, starting_rectangle.y);
		rectangle.setSize(sf::Vector2f(starting_rectangle.x - mouseX, mouseY - starting_rectangle.y));
	}
	else if (mouseX < starting_rectangle.x && mouseY < starting_rectangle.y) {
		rectangle.setPosition(mouseX, mouseY);
		rectangle.setSize(static_cast<sf::Vector2f>(starting_rectangle - sf::Vector2i(mouseX,mouseY)));
	}
}
inline void saveToFile(const sf::RenderWindow &window,char &letter)
{
	sf::Texture texture;
	sf::Vector2u vec = window.getSize();
	texture.create(vec.x,vec.y);
	texture.update(window);
	sf::Image img = texture.copyToImage();
	texture.loadFromImage(img, sf::IntRect(2, 63, 796, 535));
	texture.copyToImage().saveToFile("img.png");
	letter = 0;
}

inline void loadFromFile(sf::Sprite &background,sf::Texture& texture_to_back, char& letter)
{
	if (!texture_to_back.loadFromFile("img.png"))
		std::cout << "BLAD!!!!!!" << std::endl;
	background.setTexture(texture_to_back);
	letter = 0;
}


int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 650), "GFK Lab 01", sf::Style::Titlebar | sf::Style::Close);
	sf::Event event;
	Menu menu;

	window.setFramerateLimit(60);
	
	// INICJALIZATION VARIABLES
	char actual_letter = 0;
	sf::Color filling_color1(sf::Color::Transparent);
	sf::Color filling_color2(sf::Color::Transparent);
	sf::RectangleShape rectangle;
	sf::RectangleShape rectangle2;
	rectangle.setSize(sf::Vector2f(34, 29));
	rectangle2.setSize(sf::Vector2f(34, 29));
	rectangle.setFillColor(sf::Color::Transparent);
	rectangle2.setFillColor(sf::Color::Transparent);
	rectangle.setPosition(sf::Vector2f(766, 1));
	rectangle2.setPosition(sf::Vector2f(766, 31));

	sf::RectangleShape temp_rectangle;
	temp_rectangle.setOutlineThickness(-1);
	sf::VertexArray temp_line(sf::LinesStrip, 2);
	sf::CircleShape temp_circle;
	temp_circle.setOutlineThickness(3);
	temp_circle.setFillColor(sf::Color::Transparent);


	std::vector<sf::RectangleShape> rectangle_to_draw;
	std::vector<sf::VertexArray> line_to_draw;
	std::vector<sf::CircleShape> circle_to_draw;
	std::vector<std::string> shapes_priority;
	sf::Vector2i starting_circle(0, 0);
	sf::Vector2i starting_rectangle(0, 0);
	std::string last = "none";
	sf::Texture texture_to_background;
	sf::Sprite background;
	background.setPosition(2, 63);

	///////////////////////

	bool drawing_mode = false;

	while (window.isOpen())
	{
		window.clear(sf::Color::Black);

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) window.close();
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Escape)
					window.close();
				SetActualLetter(event, &actual_letter);
				if (actual_letter == 'o')
					loadFromFile(background,texture_to_background, actual_letter);
			}

			
			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
				if (actual_letter == 'f') {
					SetColor(filling_color1, event.mouseButton.x, event.mouseButton.y);
					rectangle.setFillColor(filling_color1);
				}
				else if (actual_letter == 'b') {
					SetColor(filling_color2, event.mouseButton.x, event.mouseButton.y);
					rectangle2.setFillColor(filling_color2);
				}
				else if (actual_letter == 'l') {
					if (!drawing_mode) {
						last = "line";
						drawing_mode = true;
						temp_line[0].position = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);
						temp_line[0].color = filling_color1;
						temp_line[1].position = temp_line[0].position;
						if (filling_color2 == sf::Color::Transparent) temp_line[1].color = filling_color1;
						else temp_line[1].color = filling_color2;
					}
				}
				else if (actual_letter == 'c') {
					if (!drawing_mode) {
						last = "circle";
						drawing_mode = true;
						temp_circle.setPosition(sf::Vector2f(event.mouseButton.x, event.mouseButton.y));
						starting_circle = sf::Mouse::getPosition(window);
						temp_circle.setOutlineColor(filling_color1);
						temp_circle.setRadius(0);
					}

				}
				else if (actual_letter == 'r' || actual_letter == 'a') {
					if (!drawing_mode) {
						drawing_mode = true;
						temp_rectangle.setPosition(sf::Vector2f(event.mouseButton.x, event.mouseButton.y));
						starting_rectangle = sf::Mouse::getPosition(window);
						temp_rectangle.setSize(sf::Vector2f(0, 0));
						temp_rectangle.setOutlineColor(filling_color1);
						if (actual_letter == 'r') temp_rectangle.setFillColor(sf::Color::Transparent);
						else temp_rectangle.setFillColor(filling_color2);
						last = "rectangle";
					}

				}
			}
			
			

			//DRAWING WHILE BUTTON PRESSED

			else if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				if (drawing_mode && event.mouseMove.y > 61 && event.mouseMove.y <599) {
					if (actual_letter == 'l') updateLine(temp_line, event.mouseMove.x, event.mouseMove.y);
					else if (actual_letter == 'c') updateCircle(temp_circle, starting_circle, event.mouseMove.x, event.mouseMove.y);
					else if (actual_letter == 'r' || actual_letter == 'a') updateRectangle(temp_rectangle, starting_rectangle, event.mouseMove.x, event.mouseMove.y);
				}
			}

			/////////////////////////

			
		//BUTTON REALESED -> SAVING SHAPE

			if (event.type == sf::Event::MouseButtonReleased) {
				if (actual_letter == 'l') {
					line_to_draw.push_back(temp_line);
					shapes_priority.push_back("line");
					drawing_mode = false;
				}
				else if (actual_letter == 'c') {
					circle_to_draw.push_back(temp_circle);
					shapes_priority.push_back("circle");
					drawing_mode = false;
				}
				else if (actual_letter == 'a' || actual_letter == 'r') {
					rectangle_to_draw.push_back(temp_rectangle);
					shapes_priority.push_back("rectangle");
					drawing_mode = false;
				}
			}
		}
		///////////////////////////////////

		

		window.draw(background);

		// DISPLAYING SAVED SHAPES
		if (actual_letter)
			DisplayActualLetter(window, actual_letter);

		auto it_line = line_to_draw.begin();
		auto it_circle = circle_to_draw.begin();
		auto it_rectangle = rectangle_to_draw.begin();

		for (std::string &str : shapes_priority) {
			if (str == "line") {
				window.draw(*it_line);
				++it_line;
			}
			else if (str == "circle") {
				window.draw(*it_circle);
				++it_circle;
			}
			else if (str == "rectangle") {
				window.draw(*it_rectangle);
				++it_rectangle;
			}
		}
		
		///////////////////////////

		//DISPLAYING CURRENT (IN DRAWING MODE) SHAPE

		if (drawing_mode) {
			if (last == "line")
				window.draw(temp_line);
			else if (last == "circle")
				window.draw(temp_circle);
			else if (last == "rectangle")
				window.draw(temp_rectangle);
		}

		/////////////////////////////////
		if (actual_letter == 'w')
			saveToFile(window, actual_letter);
		//DISPLAYING MENU
		window.draw(menu);
		window.draw(rectangle);
		window.draw(rectangle2);
		////////////////
	
		window.display();


		//Draw END
	}
	return 0;
}