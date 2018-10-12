#include "Implementation.h"

void mainFrame::sizeChanged(wxUpdateUIEvent& event)
{
	refresh();
}

void mainFrame::SaveToFile(wxCommandEvent & event)
{
	wxFileDialog *saveFileDialog = new wxFileDialog(this, ("BMP files"), wxEmptyString, wxEmptyString,
		wxT("Bitmap Files (*.bmp)|*.bmp"), wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
	wxInitAllImageHandlers();


	if (saveFileDialog->ShowModal() != wxID_CANCEL) {
		
		wxClientDC dc(mainPanel);
		wxBitmap bitmapToSave(dc.GetSize().x, dc.GetSize().y);
		wxMemoryDC mem;
		mem.SelectObject(bitmapToSave);
		mem.Blit(0, 0, dc.GetSize().x, dc.GetSize().y, &dc, 0,0);
		mem.SelectObject(wxNullBitmap);
		bitmapToSave.SaveFile(saveFileDialog->GetPath() + saveFileDialog->GetName(), wxBITMAP_TYPE_BMP);
	}
		



	delete saveFileDialog;
}

void mainFrame::boolBanan(wxCommandEvent & event)
{
	if (banan) {
		banan = false;
		bananPositionBar->Disable();
	}
	else {
		bananPositionBar->Enable();
		banan = true;

	}
	refresh();
}

void mainFrame::scrollMoved(wxScrollEvent & event)
{
	refresh();
	Gauge->SetValue(bananPositionBar->GetThumbPosition());
}

void mainFrame::starColor(wxCommandEvent & event)
{
	wxColourDialog cdlg(this);
	if (cdlg.ShowModal() != wxID_CANCEL) {
		starClr = cdlg.GetColourData().GetColour();
	}

}

void mainFrame::textChanged(wxCommandEvent & event)
{
	text = textArea->GetValue();
	refresh();

}

void mainFrame::shapeChoice(wxCommandEvent & event)
{
	shape_str = shapeChoiceButton->GetString(shapeChoiceButton->GetCurrentSelection());
	//SetTitle(shape_str);


}

void mainFrame::DrawText(wxDC *clientDC)
{

	clientDC->SetFont(wxFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, "Tahoma"));
	clientDC->DrawText(text, -100, 80);

	clientDC->SetFont(wxFont(35, wxFONTFAMILY_DECORATIVE, wxFONTSTYLE_SLANT, wxFONTWEIGHT_BOLD, false, "Comic Sans MS"));
	clientDC->DrawRotatedText(text, wxPoint(70, 100), 90);
}

void mainFrame::DrawMonkey(wxDC *clientDC)
{
	clientDC->SetPen(wxPen(wxColor("Black"), 1));
	double temp_radius = sqrt(std::pow(50 + 10, 2) + std::pow(15 + 0, 2)) / 2;
	//dodac rysowanie od k¹ta
	//clientDC->DrawLine(wxPoint(-30, 15), wxPoint(10, 0));
	double x, y;
	double bar = static_cast<double>(bananPositionBar->GetThumbPosition()) / bananPositionBar->GetRange();
	x = temp_radius * sin(M_PI /4. + bar * M_PI / 2.);
	y = temp_radius * cos(M_PI /4. + bar * M_PI / 2.);


	if (banan) {
		clientDC->DrawBitmap(bitmap, wxPoint(-x - bitmap.GetWidth() / 2, y - bitmap.GetHeight() / 2));
		clientDC->DrawLine(wxPoint(10, -10), wxPoint(10, 60));
		clientDC->DrawCircle(wxPoint(10, -25), 20);
		clientDC->DrawEllipse(0, -30, 10, 5);
		clientDC->DrawEllipse(15, -30, 10, 5);
		clientDC->DrawSpline(0, -15, 10, -10, 20, -15);
	}
	else {
		clientDC->DrawLine(wxPoint(10, -10), wxPoint(10, 60));
		clientDC->DrawCircle(wxPoint(10, -25), 20);
		clientDC->DrawEllipse(15, -35, 5, 10);
		clientDC->DrawEllipse(0, -30, 10, 5);
		clientDC->DrawSpline(0, -15, 10, -20, 20, -15);
	}


	clientDC->DrawLine(wxPoint(-x, y), wxPoint(10, 0));
	clientDC->DrawLine(wxPoint(-20, 90), wxPoint(10, 60));
	clientDC->DrawLine(wxPoint(40, 90), wxPoint(10, 60));
	clientDC->DrawLine(wxPoint(50, 15), wxPoint(10, 0));
	


}

void mainFrame::DrawShape(wxDC *dc)
{

	
	if (shape_str == "gwiazdka") {
		dc->SetPen(wxPen(starClr));
		dc->SetBrush(wxBrush(starClr));
		wxPoint points[3];
		//first triangle gorny elementy
		points[0] = wxPoint(-70, -80);
		points[1] = wxPoint(-80, -60); // lewy
		points[2] = wxPoint(-60, -60); //prawy
		dc->DrawPolygon(3,points);
		//prawy gorny
		points[0] = wxPoint(-60, -60);
		points[1] = wxPoint(-40, -60);
		points[2] = wxPoint(-55, -50);
		dc->DrawPolygon(3, points);
		//lewy gorny
		points[0] = wxPoint(-80, -60);
		points[1] = wxPoint(-100, -60);
		points[2] = wxPoint(-85, -50);
		dc->DrawPolygon(3, points);

		//dolny lewy
		points[0] = wxPoint(-85, -50);
		points[1] = wxPoint(-70, -40);
		points[2] = wxPoint(-95, -33);
		dc->DrawPolygon(3, points);
		//dolny prawy
		points[0] = wxPoint(-70, -40);
		points[1] = wxPoint(-55, -50);
		points[2] = wxPoint(-45, -33);
		dc->DrawPolygon(3, points);

	}
	else if (shape_str == "ksiezyc") {
		dc->SetPen(wxPen(*wxLIGHT_GREY_PEN));
		dc->SetBrush(wxBrush(*wxLIGHT_GREY_BRUSH));
		dc->DrawCircle(wxPoint(-80, -60), 20);
		dc->SetPen(wxPen(*wxWHITE_PEN));
		dc->SetBrush(wxBrush(*wxWHITE_BRUSH));
		dc->DrawCircle(wxPoint(-90, -70), 20);
		dc->SetPen(wxPen(*wxBLACK_PEN));
		dc->SetBrush(wxBrush(*wxBLACK_BRUSH));
		dc->DrawCircle(wxPoint(-68, -60), 2);
		dc->DrawLine(wxPoint(-75, -50), wxPoint(-80, -55));




	}
	else if (shape_str == "slonko") {
		dc->SetPen(wxPen(*wxYELLOW_PEN));
		dc->SetBrush(wxBrush(*wxYELLOW_BRUSH));
		dc->DrawCircle(wxPoint(-80, -60), 20);

	}



}

void mainFrame::refresh()
{
	

	wxClientDC dc(mainPanel); // #include <wx/dcbuffer.h>
	dc.SetBackground(*wxWHITE_BRUSH); // to avoid white rectangle around banana
	wxBufferedDC newDC(&dc);
	wxSize size = mainPanel->GetClientSize();
	newDC.SetDeviceOrigin(size.x / 2, size.y / 2);
	newDC.Clear();
	DrawText(&newDC);
	DrawMonkey(&newDC);
	DrawShape(&newDC);
	
	
}



//konstruktor
mainFrame::mainFrame(wxWindow *parent): MyFrame1(parent)
{
	text = textArea->GetValue();
	bananPositionBar->SetRange(300);
	Gauge->SetRange(300);
	banan = false;
	wxImage::AddHandler(new wxPNGHandler);
	img.LoadFile("banan.png");
	bitmap = wxBitmap(img);

	bananPositionBar->Disable();
	shape_str = shapeChoiceButton->GetString(shapeChoiceButton->GetCurrentSelection());
	SetTitle(_("LAB3 GFK"));

	refresh();
}