#include "Kolo.h"

#define M_PI 3.14159265359
const int SIZE = 250;
const double okres = 2 * M_PI;

Kolo::Kolo(double x_pozycja, double y_pozycja,double wys , double szer )
{
	m_promien = SIZE / 2;
	circle.setPosition(x_pozycja, y_pozycja);
	circle.setRadius(m_promien);
	circle.setOutlineColor(sf::Color::Transparent);
	texture.create(SIZE, SIZE);
	circle.setTexture(&texture);
}


void Kolo::ustawRGB()
{
	sf::Uint8 *pixele = new sf::Uint8[SIZE * SIZE * 4];
	double kat = 0;
	double promienPetli;

	for (int x = 0; x < SIZE; ++x) {
		for (int y = 0; y < SIZE; ++y) {
			promienPetli = sqrt((x - m_promien)* (x - m_promien) + (y - m_promien)* (y - m_promien));
			if (promienPetli >= m_promien)
				draw_to_color_pixels(pixele, SIZE, x, y, 0, 0, 0, 0);
			else {
			
				kat = acosl((x - m_promien) / promienPetli);
				if (y > m_promien) {
					kat = okres - kat;
				}
				draw_to_color_pixels(pixele, SIZE,x, y, 255 * promienPetli / m_promien, 255 * kat / okres, 0, 255);
			}

		}
	}
	texture.update(pixele);
	delete[] pixele;
}

void Kolo::ustawCMY()
{
	sf::Uint8 *pixele = new sf::Uint8[SIZE * SIZE * 4];
	double kat = 0;
	double promienPetli;

	for (int x = 0; x < SIZE; ++x) {
		for (int y = 0; y < SIZE; ++y) {
			promienPetli = sqrt((x - m_promien)* (x - m_promien) + (y - m_promien)* (y - m_promien));
			if (promienPetli >= m_promien)
				draw_to_color_pixels(pixele, SIZE, x, y, 0, 0, 0, 0);
			else {

				kat = acosl((x - m_promien) / promienPetli);
				if (y > m_promien) {
					kat = okres - kat;
				}
				draw_to_color_pixels(pixele,SIZE, x, y, 255 - 255 * promienPetli / m_promien, 255 - 255 * kat / okres,0, 255);
			}

		}
	}
	texture.update(pixele);
	delete[] pixele;



}

void Kolo::ustawHSL()
{
	sf::Uint8 *pixele = new sf::Uint8[SIZE * SIZE * 4];
	double kat = 0;
	double promienPetli;
	double   H, S, V, R, G, B,L,r,g,b,c,i_temp,temp,light;
	for (int x = 0; x < SIZE; ++x) {
		for (int y = 0; y < SIZE; ++y) {
			promienPetli = sqrt((x - m_promien)* (x - m_promien) + (y - m_promien)* (y - m_promien));

			if (promienPetli >= m_promien)
				draw_to_color_pixels(pixele, SIZE, x, y, 0, 0, 0, 0);
			else {
				kat = acosl((x - m_promien) / promienPetli);
				if (y > m_promien) {
					kat = okres - kat;
				}

				//www.easyrgb.com/en/math.php
				S = promienPetli / m_promien;
				L = (255.0f-127.5) / 255.0f;
				c = (1 - fabs(2 * L - 1))*S;
				i_temp = fmodf(kat * 6 / 6.283, 2.0) - 1.0;
				temp = c*(1.0 - fabs(i_temp));
				light = L - c / 2;

				if (x == 100 && y == 100) kat = 0;
				if (kat >= 0 && kat < M_PI / 3){ r = c;	g = temp; b = 0;}
				else if (kat >= M_PI / 3.0 && kat < okres / 3.0){ r = temp; g = c; b = 0;}
				else if (kat >= okres / 3.0 && kat < M_PI){ r = 0; g = c; b = temp;}
				else if (kat >= M_PI && kat < M_PI * 4 / 3.0){ r = 0; g = temp;	b = c;}
				else if (kat >= M_PI * 4 / 3.0 && kat < M_PI * 5 / 3.0){ r = temp; g = 0; b = c;}
				else if (kat >= M_PI * 5 / 3.0 && kat < okres){ r = c;	g = 0; b = temp;}
				R = (r + light) * 255;
				G = (g + light) * 255;
				B = (b + light) * 255;

				draw_to_color_pixels(pixele, SIZE, x, y, R, G, B, 255);
			}
		}
	}
	texture.update(pixele);
	delete[] pixele;

}

void Kolo::ustawHSV()
{
	sf::Uint8 *pixele = new sf::Uint8[SIZE * SIZE * 4];
	double kat = 0;
	double promienPetli;
	int cwiartka;
	double H, S, V, R, G, B;
	double  var_h, var_i, var_1, var_2, var_3, var_r, var_g, var_b;
	for (int x = 0; x < SIZE; ++x) {
		for (int y = 0; y < SIZE; ++y) {
			promienPetli = sqrt((x - m_promien)* (x - m_promien) + (y - m_promien)* (y - m_promien));
			
			if (promienPetli >= m_promien)
				draw_to_color_pixels(pixele, SIZE, x, y, 0, 0, 0, 0);
			else {
				kat = acosl((x - m_promien) / promienPetli);
				if (y > m_promien) {
					kat = okres - kat;
				}

				//zrodlo algorytmu www.easyrgb.com/en/math.php
				H = kat / okres;
				S = promienPetli / m_promien;
				V = (255.0f) / 255.0f;

				var_h = H * 6.0f;
				if (var_h == 6.0f) var_h = 0;
				var_i = (int)(var_h);
				var_1 = V * (1.0 - S);
				var_2 = V * (1.0 - S * (var_h - var_i));
				var_3 = V * (1.0 - S * (1.0 - (var_h - var_i)));

				if (var_i == 0) { var_r = V; var_g = var_3; var_b = var_1; }
				else if (var_i == 1) { var_r = var_2; var_g = V; var_b = var_1; }
				else if (var_i == 2) { var_r = var_1; var_g = V; var_b = var_3; }
				else if (var_i == 3) { var_r = var_1; var_g = var_2; var_b = V; }
				else if (var_i == 4) { var_r = var_3; var_g = var_1; var_b = V; }
				else { var_r = V; var_g = var_1; var_b = var_2; }

				R = var_r * 255;
				G = var_g * 255;
				B = var_b * 255;


				
				draw_to_color_pixels(pixele, SIZE, x, y, R, G, B, 255);
			}
		}
	}
	texture.update(pixele);
	delete[] pixele;

}


