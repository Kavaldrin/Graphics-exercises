#include "noname.h"

using namespace cimg_library;



void MyFrame1::loadImage(wxCommandEvent& event)
{

	wxFileDialog openFileDialog(this, _("Otworz plik jpg"), "", "",
		"Pliki JPG (*.jpg)|*.jpg", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
	if (openFileDialog.ShowModal() == wxID_CANCEL)
		return;

	freeIMG.load(openFileDialog.GetPath().c_str());
	freeIMG.flipVertical();
	int w = freeIMG.getWidth();
	int h = freeIMG.getHeight();
	fipTag tag;
	fipMetadataFind mdfind;
	mdfind.findFirstMetadata(FIMD_EXIF_MAIN, freeIMG, tag);
	m_exifText->AppendText("Rozmiar obrazka: " + std::to_string(w) + "x"+ std::to_string(h) + "\n");
	m_exifText->AppendText("EXIF Info: \n");
	//
	m_exifText->AppendText(tag.getKey());
	m_exifText->AppendText(": ");
	m_exifText->AppendText(tag.toString(FIMD_EXIF_MAIN));
	m_exifText->AppendText("\n");

	while (mdfind.findNextMetadata(tag)) {
		m_exifText->AppendText(tag.getKey());
		m_exifText->AppendText(": ");
		m_exifText->AppendText(tag.toString(FIMD_EXIF_MAIN));
		m_exifText->AppendText("\n");
	}
	//

	
	FIBITMAP *bi = freeIMG;
	RGBQUAD pixel;
	
	
	imageWX = wxImage(w, h); //24bpp
	imageWX.InitAlpha(); //32bpp

	unsigned char *rgb = imageWX.GetData();

	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			FreeImage_GetPixelColor(bi, x, y, &pixel);
			int offset = (y * w + x)*3; //Alpha offset
			rgb[offset] = pixel.rgbRed;
			rgb[offset + 1] = pixel.rgbGreen;
			rgb[offset + 2] = pixel.rgbBlue;
		}
	}


	/////////
	imageLoaded = true;
	orgImageWx = wxImage(imageWX);
	update();

}

void MyFrame1::update()
{
	if (animationOn)
		return;
	
	bitmapWX = wxBitmap(imageWX);
	wxMemoryDC memDC;
	memDC.SelectObject(bitmapWX);
	wxClientDC dc(m_imagePanel);
	dc.Blit(0, 0, bitmapWX.GetWidth(), bitmapWX.GetHeight(), &memDC, 0, 0);
	memDC.SelectObject(wxNullBitmap);
}

void MyFrame1::sizeChanged(wxUpdateUIEvent& event)
{
	if (animationOn)
		return;

	wxSize size = m_imagePanel->GetSize();
	imageWX.Rescale(size.GetWidth(),size.GetHeight());
	orgImageWx.Rescale(size.GetWidth(), size.GetHeight());
	update();
}
void MyFrame1::wxToCImgFloat(wxImage &imgWX, CImg<float> &imgCImg)
{

	int w = imgWX.GetWidth();
	int h = imgWX.GetHeight();
	imgCImg = CImg<float>(w, h, 1, 3, 0);
	unsigned char *rgb = imgWX.GetData();
	float *CImgData = imgCImg.data();

	cimg_forXY(imgCImg, x, y) {
		int offset = (y * w + x) * 3;
		CImgData[w*h * 0 + y*w + x] = rgb[offset];
		CImgData[w*h * 1 + y*w + x] = rgb[offset + 1];
		CImgData[w*h * 2 + y*w + x] = rgb[offset + 2];

	}

	//

}
void MyFrame1::CImgToWxFloat(wxImage &imgWX, CImg<float> &imgCImg)
{
	int w = imgWX.GetWidth();
	int h = imgWX.GetHeight();
	unsigned char *rgb = imgWX.GetData();
	float *CImgData = imgCImg.data();

	cimg_forXY(imgCImg, x, y) {
		int offset = (y * w + x) * 3;
		rgb[offset] = CImgData[w*h * 0 + y*w + x];
		rgb[offset + 1] = CImgData[w*h * 1 + y*w + x];
		rgb[offset + 2] = CImgData[w*h * 2 + y*w + x];
	}

	//

}
void MyFrame1::wxToCImgChar(wxImage &imgWX, CImg<unsigned char> &imgCImg)
{

	int w = imgWX.GetWidth();
	int h = imgWX.GetHeight();
	imgCImg = CImg<unsigned char>(w, h, 1, 3, 0);
	unsigned char *rgb = imgWX.GetData();
	unsigned char *CImgData = imgCImg.data();

	cimg_forXY(imgCImg, x, y) {
		int offset = (y * w + x) * 3;
		CImgData[w*h*0+y*w+x] = rgb[offset];
		CImgData[w*h * 1 + y*w + x] = rgb[offset + 1];
		CImgData[w*h * 2 + y*w + x] = rgb[offset + 2];

	}

}
void MyFrame1::CImgToWxChar(wxImage &imgWX, CImg<unsigned char> &imgCImg)
{
	int w = imgWX.GetWidth();
	int h = imgWX.GetHeight();
	unsigned char *rgb = imgWX.GetData();
	unsigned char *CImgData = imgCImg.data();

	cimg_forXY(imgCImg, x, y) {
		int offset = (y * w + x) * 3;
		rgb[offset] = CImgData[w*h * 0 + y*w + x];
		rgb[offset + 1] = CImgData[w*h * 1 + y*w + x];
		rgb[offset + 2] = CImgData[w*h * 2 + y*w + x];
	}

}

void MyFrame1::erode(wxCommandEvent& event)
{
	if (animationOn)
		return;

	imageWX = orgImageWx.Copy();

	wxToCImgChar(imageWX,imageCchar);
	imageCchar.erode(5);
	CImgToWxChar(imageWX, imageCchar);

	update();
}

void MyFrame1::censorship(wxCommandEvent& event)
{
	if (animationOn)
		return;


	imageWX = orgImageWx.Copy();

	int x_start = imageWX.GetWidth() * 0.58;
	int y_start = imageWX.GetHeight() * 0.04;
	int x_stop = imageWX.GetWidth() * 0.74;
	int y_stop = imageWX.GetHeight() * 0.15;

	int headW = x_stop - x_start;
	int headH = y_stop - y_start;
	int normalW = imageWX.GetWidth();
	int normalH = imageWX.GetHeight();

	wxImage head = wxImage(headW, headH);
	head.InitAlpha();
	CImg<unsigned char> headCImg;

	unsigned char* rgbHead = head.GetData();
	unsigned char* rgbNormal = imageWX.GetData();

	for (int y = 0; y < headH; ++y) {
		for (int x = 0; x < headW; ++x) {
			int offsetHead = (y * headW + x) * 3;
			int offsetNormal = ((y + y_start)*normalW + (x_start + x)) * 3;
			rgbHead[offsetHead] = rgbNormal[offsetNormal];
			rgbHead[offsetHead+1] = rgbNormal[offsetNormal+1];
			rgbHead[offsetHead+2] = rgbNormal[offsetNormal+2];
		}
	}

	wxToCImgChar(head, headCImg);
	headCImg.blur(5);
	CImgToWxChar(head, headCImg);

	for (int y = 0; y < headH; ++y) {
		for (int x = 0; x < headW; ++x) {
			int offsetHead = (y * headW + x) * 3;
			int offsetNormal = ((y + y_start)*normalW + x_start + x) * 3;
			rgbNormal[offsetNormal] = rgbHead[offsetHead];
			rgbNormal[offsetNormal+1] = rgbHead[offsetHead+1];
			rgbNormal[offsetNormal+2] = rgbHead[offsetHead+2];
		}
	}

}

void MyFrame1::Animation(wxCommandEvent& event)
{
	if (animationOn) {
		animationOn = false;
		m_timer.Stop();
	}
	else {
		if (!imageLoaded)
			return;

		m_loadingBar->Show();
		Refresh();
		Update();
		update();


		m_animationBitmaps.clear();
		CImg<float> CImgStart;
		wxToCImgFloat(orgImageWx, CImgStart);
		const int W = orgImageWx.GetWidth();
		const int H = orgImageWx.GetHeight();

		//tworzenie obrazkow do animacji
		//60 klatek
		float spec[3] = { 1.0f,1.0f,1.0f };

		for (int i = 0; i < 60; ++i) {


			CImg<float> gauss(W, H, 1, 3);
			CImg<float> gauss2(W, H, 1, 3);
			CImg<float> copy_start(CImgStart);

			gauss.draw_gaussian(W / 2 + W*0.4 * cos(i*6 * M_PI / 180.), H / 2 + H*0.4 * sin(i*6 * M_PI / 180.), 150.0f, spec, 1.0f);
			gauss2.draw_gaussian(W / 2 + W*0.4 * cos(((i*6+180)%360) * M_PI / 180.), H / 2 + H*0.4 * sin(((i*6 + 180) % 360)* M_PI / 180.), 150.0f, spec, 1.0f);
			gauss = gauss + gauss2;
			copy_start.mul(gauss);
			wxImage wxTemp(W, H);
			wxTemp.InitAlpha();
			CImgToWxFloat(wxTemp, copy_start);
			m_animationBitmaps.push_back(wxBitmap(wxTemp));
			m_loadingBar->SetValue(i);

		}
		m_loadingBar->Hide();
		m_timer.Start(1000./70.);
		
		animationOn = true;
	}


}


void MyFrame1::OnTimer(wxTimerEvent& e)
{
	static int iterator = 0;
	wxMemoryDC memDC;
	wxClientDC dc(m_imagePanel);
	memDC.SelectObject(m_animationBitmaps[iterator]);
	dc.Blit(0, 0, m_animationBitmaps[iterator].GetWidth(), m_animationBitmaps[iterator].GetHeight(), &memDC, 0, 0);
	++iterator;
	if (iterator >= 60)
		iterator = 0;

}