#pragma once

#include "noname.h"
#include <wx/dcbuffer.h>
#include <wx/filedlg.h>
#include <wx/colordlg.h>

class mainFrame :public MyFrame1
{
public:
	mainFrame(wxWindow*);
	void SaveToFile(wxCommandEvent& event);
	void boolBanan(wxCommandEvent& event);
	void scrollMoved(wxScrollEvent& event);
	void starColor(wxCommandEvent& event);
	void textChanged(wxCommandEvent& event);
	void shapeChoice(wxCommandEvent& event);
	void sizeChanged(wxUpdateUIEvent& event);

protected:

	wxString text;
	bool banan;
	void DrawText(wxDC *);
	void DrawMonkey(wxDC *);
	void DrawShape(wxDC *);
	void refresh();
	wxBitmap bitmap;
	wxImage img;
	wxColour starClr;
	wxString shape_str;

};
