///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun 17 2015)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "noname.h"

///////////////////////////////////////////////////////////////////////////

MyFrame1::MyFrame1(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style) : wxFrame(parent, id, title, pos, size, style)
{
	this->SetSizeHints(wxDefaultSize, wxDefaultSize);

	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer(wxHORIZONTAL);

	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer(wxVERTICAL);

	bSizer2->SetMinSize(wxSize(300, -1));
	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer(wxVERTICAL);

	m_loadImageButton = new wxButton(this, wxID_ANY, wxT("Wczytaj obrazek"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer4->Add(m_loadImageButton, 0, wxALIGN_CENTER | wxALL, 5);

	m_censhorshipButton = new wxButton(this, wxID_ANY, wxT("Cenzura"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer4->Add(m_censhorshipButton, 0, wxALIGN_CENTER | wxALL, 5);

	m_erodeButton = new wxButton(this, wxID_ANY, wxT("Erode"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer4->Add(m_erodeButton, 0, wxALIGN_CENTER | wxALL, 5);

	m_animationCheck = new wxCheckBox(this, wxID_ANY, wxT("Animacja"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer4->Add(m_animationCheck, 0, wxALIGN_CENTER | wxALL, 5);

	//
	m_loadingBar = new wxGauge(this, wxID_ANY , 60, wxDefaultPosition, wxDefaultSize, wxGA_HORIZONTAL);
	m_loadingBar->SetValue(0);
	m_loadingBar->Hide();

	bSizer4->Add(m_loadingBar, 0, wxALIGN_CENTER | wxALL | wxRESERVE_SPACE_EVEN_IF_HIDDEN , 5);
	//
		
	bSizer2->Add(bSizer4, 0, wxEXPAND, 5);

	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer(wxHORIZONTAL);

	m_exifText = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE | wxTE_NO_VSCROLL | wxTE_WORDWRAP);
	bSizer5->Add(m_exifText, 1, wxALL | wxEXPAND, 5);


	bSizer2->Add(bSizer5, 1, wxEXPAND, 5);


	bSizer1->Add(bSizer2, 0, wxEXPAND, 5);

	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer(wxVERTICAL);

	m_imagePanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	bSizer3->Add(m_imagePanel, 1, wxEXPAND | wxALL, 5);


	bSizer1->Add(bSizer3, 1, wxEXPAND, 5);


	this->SetSizer(bSizer1);
	this->Layout();

	this->Centre(wxBOTH);

	// Connect Events
	m_loadImageButton->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame1::loadImage), NULL, this);
	m_censhorshipButton->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame1::censorship), NULL, this);
	m_erodeButton->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame1::erode), NULL, this);
	m_animationCheck->Connect(wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(MyFrame1::Animation), NULL, this);
	m_imagePanel->Connect(wxEVT_UPDATE_UI, wxUpdateUIEventHandler(MyFrame1::sizeChanged), NULL, this);
	m_timer.Connect(wxEVT_TIMER, wxTimerEventHandler(MyFrame1::OnTimer), NULL, this);

	//
	m_imagePanel->SetBackgroundColour(*wxBLACK);
	imageWX = wxImage(1, 1);
	orgImageWx = wxImage(1, 1);
	animationOn = false;
	imageLoaded = false;
}

MyFrame1::~MyFrame1()
{
	// Disconnect Events
	m_loadImageButton->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame1::loadImage), NULL, this);
	m_censhorshipButton->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame1::censorship), NULL, this);
	m_erodeButton->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame1::erode), NULL, this);
	m_animationCheck->Disconnect(wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(MyFrame1::Animation), NULL, this);
	m_imagePanel->Disconnect(wxEVT_UPDATE_UI, wxUpdateUIEventHandler(MyFrame1::sizeChanged), NULL, this);
	m_timer.Connect(wxEVT_TIMER, wxTimerEventHandler(MyFrame1::OnTimer), NULL, this);

}
