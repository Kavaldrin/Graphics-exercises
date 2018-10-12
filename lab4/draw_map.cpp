#include <wx/wx.h>
#include "GUIMyFrame1.h"
// UWAGA: TO JEST JEDYNY PLIK, KTORY NALEZY EDYTOWAC **************************

void GUIMyFrame1::DrawMap(int N, float d[100][3], bool Contour, int MappingType, int NoLevels, bool ShowPoints)
{
	const int SIZE = 500;


	double **arr = new double*[SIZE];
	for (int i = 0; i < SIZE; ++i) arr[i] = new double[SIZE];


	wxMemoryDC memDC;
	memDC.SelectObject(MemoryBitmap);
	memDC.SetBackground(*wxWHITE_BRUSH);
	memDC.Clear();

	wxNativePixelData data(MemoryBitmap);
	wxNativePixelData::Iterator p(data);
	p.Offset(data,0,SIZE-1);

	memDC.SetDeviceOrigin(SIZE/2, SIZE/2);
	memDC.SetPen(*wxBLACK_PEN);
	memDC.SetBrush(*wxTRANSPARENT_BRUSH);

	//plansza /100 -2.5 do 2.5
	double min = INT_MAX, max = INT_MIN, temp;
	
	//aproksymacja  //  min i max
	for (int i = 0; i < SIZE; ++i) {
		for (int j = 0; j < SIZE; ++j) {
			arr[i][j] = shepard(N, d, (i - SIZE/2) / 100., (j - SIZE/2) / 100.);
			if (arr[i][j] > max) max = arr[i][j];
			if (min > arr[i][j]) min = arr[i][j];
		}
	}
	
	double r, g, b;
	
	
	if (MappingType == 1) {
		for (int y = 0; y < SIZE; ++y) {
			for (int x = 0; x < SIZE; ++x, ++p) {
				r = 255 - ((arr[x][y] - min) / (max - min)) * 255;
				g = 0;
				b = ((arr[x][y] - min) / (max - min)) * 255;
				if (r > 255) r = 255; else if (r < 0) r = 0;
				if (g > 255) g = 255; else if (g < 0) g = 0;
				if (b > 255) b = 255; else if (b < 0) b = 0;

				p.Red() = r;
				p.Green() = g;
				p.Blue() = b;

			}
			p.OffsetY(data, -1);
			p.OffsetX(data, -SIZE);
		}
	}
	if (MappingType == 2) {
		for (int y = 0; y < SIZE; ++y) {
			for (int x = 0; x < SIZE; ++x, ++p) {
				if ((arr[x][y] - min) / (max - min) < 0.5) {
					r = 255 - ((arr[x][y] - min) / (max - min)) * 255 * 2;
					g = ((arr[x][y] - min) / (max - min)) * 2 * 255;
					b = 0;
				}
				else {
					r = 0;
					g = 255 - ((arr[x][y] - min) / (max - min) - 0.5) * 2 * 255;
					b = ((arr[x][y] - min) / (max - min) - 0.5) * 2 * 255;
				}

				if (r > 255) r = 255; else if (r < 0) r = 0;
				if (g > 255) g = 255; else if (g < 0) g = 0;
				if (b > 255) b = 255; else if (b < 0) b = 0;

				p.Red() = r;
				p.Green() = g;
				p.Blue() = b;

			}
			p.OffsetY(data, -1);
			p.OffsetX(data, -SIZE);
		}
	}
	if (MappingType == 3) {
		for (int y = 0; y < SIZE; ++y) {
			for (int x = 0; x < SIZE; ++x, ++p) {

				r = ((arr[x][y] - min) / (max - min)) * 255;
				g = ((arr[x][y] - min) / (max - min)) * 255;
				b = ((arr[x][y] - min) / (max - min)) * 255;

				if (r > 255) r = 255; else if (r < 0) r = 0;
				if (g > 255) g = 255; else if (g < 0) g = 0;
				if (b > 255) b = 255; else if (b < 0) b = 0;

				p.Red() = r;
				p.Green() = g;
				p.Blue() = b;
			}
			p.OffsetY(data, -1);
			p.OffsetX(data, -SIZE);
		}
	}


	if (Contour) {
		memDC.SetDeviceOrigin(0, 0);
		memDC.SetPen(*wxBLACK);
		drawContours(memDC, SIZE, arr,min,max);
		memDC.SetDeviceOrigin(SIZE/2,SIZE/2);
	}

	if (ShowPoints) {
		for (int i = 0; i < N; ++i) {
			memDC.DrawLine(d[i][0] * 100, -d[i][1] * 100 - 5, d[i][0] * 100, -d[i][1] * 100 + 5);
			memDC.DrawLine(d[i][0] * 100 -5, -d[i][1] * 100, d[i][0] * 100 + 5, -d[i][1] * 100);
		}
	}

	
	for (int i = 0; i < SIZE; ++i) delete[] arr[i];
	delete[] arr;

}

double shepard(int N, float d[100][3], double x, double y)
{
	double w, up, down;
	down = 0;
	up = 0;


	for (int i = 0; i < N; ++i) {
		w = 1. / (std::pow(x - d[i][0], 2) + std::pow(y - d[i][1], 2));
		up += w * d[i][2];
		down += w;
	}
	return up / down;

}

void GUIMyFrame1::drawContours(wxMemoryDC &memDC, const int SIZE, double **arr,double min, double max)
{
	double step = (max - min) / static_cast<double>((NoLevels + 1));

	int **edges = new int*[SIZE];
	for (int i = 0; i < SIZE; ++i) edges[i] = new int[SIZE];

	for (double level = min; level < max; level += step) {

		for (int i = 0; i < SIZE; ++i) {
			for (int j = 0; j < SIZE; ++j) {
				edges[i][j] = (arr[i][j] > level);
			}
		}

		for (int i = 0; i < SIZE - 1; ++i) {
			for (int j = 0; j < SIZE - 1; ++j) {
				if (!edges[i][j] && !edges[i + 1][j] && !edges[i][j + 1] && !edges[i + 1][j + 1])
					continue;
				else if (!edges[i][j] && !edges[i + 1][j] && edges[i][j + 1] && !edges[i + 1][j + 1]) {
					memDC.DrawLine(i, SIZE - j, i + 1, SIZE - j + 1);
				}
				else if (!edges[i][j] && !edges[i + 1][j] && !edges[i][j + 1] && edges[i + 1][j + 1]) {
					memDC.DrawLine(i, SIZE - j + 1, i + 1, SIZE - j);
				}
				else if (!edges[i][j] && !edges[i + 1][j] && edges[i][j + 1] && edges[i + 1][j + 1]) {
					memDC.DrawLine(i, SIZE - j, i + 1, SIZE - j);
				}
				else if (!edges[i][j] && !edges[i + 1][j] && edges[i][j + 1] && edges[i + 1][j + 1]) {
					memDC.DrawLine(i, SIZE - j, i + 1, SIZE - j + 1);
				}
				else if (!edges[i][j] && edges[i + 1][j] && edges[i][j + 1] && !edges[i + 1][j + 1]) {
					memDC.DrawLine(i, SIZE - j + 1, i + 1, SIZE - j);
				}
				else if (!edges[i][j] && edges[i + 1][j] && !edges[i][j + 1] && edges[i + 1][j + 1]) {
					memDC.DrawLine(i, SIZE - j, i, SIZE - j + 1);
				}
				else if (!edges[i][j] && edges[i + 1][j] && edges[i][j + 1] && edges[i + 1][j + 1]) {
					memDC.DrawLine(i, SIZE - j + 1, i + 1, SIZE - j);
				}
				else if (edges[i][j] && !edges[i + 1][j] && !edges[i][j + 1] && !edges[i + 1][j + 1]) {
					memDC.DrawLine(i, SIZE - j + 1, i + 1, SIZE - j);
				}
				else if (edges[i][j] && !edges[i + 1][j] && edges[i][j + 1] && !edges[i + 1][j + 1]) {
					memDC.DrawLine(i, SIZE - j, i, SIZE - j + 1);
				}
				else if (edges[i][j] && !edges[i + 1][j] && !edges[i][j + 1] && edges[i + 1][j + 1]) {
					memDC.DrawLine(i, SIZE - j, i + 1, SIZE - j + 1);
				}
				else if (edges[i][j] && !edges[i + 1][j] && edges[i][j + 1] && edges[i + 1][j + 1]) {
					memDC.DrawLine(i, SIZE - j, i + 1, SIZE - j + 1);
				}
				else if (edges[i][j] && edges[i + 1][j] && !edges[i][j + 1] && !edges[i + 1][j + 1]) {
					memDC.DrawLine(i, SIZE - j, i + 1, SIZE - j);
				}
				else if (edges[i][j] && edges[i + 1][j] && edges[i][j + 1] && !edges[i + 1][j + 1]) {
					memDC.DrawLine(i, SIZE - j + 1, i + 1, SIZE - j);
				}
				else if (edges[i][j] && edges[i + 1][j] && !edges[i][j + 1] && edges[i + 1][j + 1]) {
					memDC.DrawLine(i, SIZE - j, i + 1, SIZE - j + 1);
				}
				else if (edges[i][j] && edges[i + 1][j] && edges[i][j + 1] && edges[i + 1][j + 1]) {
					continue;
				}
			}
		}

	}

	for (int i = 0; i < SIZE; ++i) delete[] edges[i];
	delete[] edges;

}