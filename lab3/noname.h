///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun 17 2015)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __NONAME_H__
#define __NONAME_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/panel.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/sizer.h>
#include <wx/button.h>
#include <wx/checkbox.h>
#include <wx/scrolbar.h>
#include <wx/gauge.h>
#include <wx/textctrl.h>
#include <wx/choice.h>
#include <wx/frame.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class MyFrame1
///////////////////////////////////////////////////////////////////////////////
class MyFrame1 : public wxFrame
{
private:

protected:
	wxPanel* mainPanel;
	wxButton* saveToFileButton;
	wxCheckBox* bananCheckBox;
	wxScrollBar* bananPositionBar;
	wxGauge* Gauge;
	wxButton* starColorButton;
	wxTextCtrl* textArea;
	wxChoice* shapeChoiceButton;

	// Virtual event handlers, overide them in your derived class
	virtual void sizeChanged(wxUpdateUIEvent& event) { event.Skip(); }
	virtual void SaveToFile(wxCommandEvent& event) { event.Skip(); }
	virtual void boolBanan(wxCommandEvent& event) { event.Skip(); }
	virtual void scrollMoved(wxScrollEvent& event) { event.Skip(); }
	virtual void starColor(wxCommandEvent& event) { event.Skip(); }
	virtual void textChanged(wxCommandEvent& event) { event.Skip(); }
	virtual void shapeChoice(wxCommandEvent& event) { event.Skip(); }


public:

	MyFrame1(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(777, 422), long style = wxDEFAULT_FRAME_STYLE | wxTAB_TRAVERSAL);

	~MyFrame1();

};

#endif //__NONAME_H__
