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
	this->SetSizeHints(wxSize(600, 300), wxDefaultSize);

	wxBoxSizer* mainSizer;
	mainSizer = new wxBoxSizer(wxHORIZONTAL);

	wxBoxSizer* panelSizer;
	panelSizer = new wxBoxSizer(wxVERTICAL);

	mainPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	panelSizer->Add(mainPanel, 1, wxEXPAND | wxALL, 5);


	mainSizer->Add(panelSizer, 2, wxEXPAND | wxFIXED_MINSIZE, 5);

	wxBoxSizer* controlSizer;
	controlSizer = new wxBoxSizer(wxVERTICAL);

	saveToFileButton = new wxButton(this, wxID_ANY, wxT("Zapis do pliku"), wxDefaultPosition, wxDefaultSize, 0);
	controlSizer->Add(saveToFileButton, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);

	bananCheckBox = new wxCheckBox(this, wxID_ANY, wxT("banan"), wxDefaultPosition, wxDefaultSize, 0);
	controlSizer->Add(bananCheckBox, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);

	bananPositionBar = new wxScrollBar(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSB_HORIZONTAL);
	controlSizer->Add(bananPositionBar, 0, wxALIGN_CENTER_HORIZONTAL | wxALL | wxEXPAND, 5);

	Gauge = new wxGauge(this, wxID_ANY, 100, wxDefaultPosition, wxDefaultSize, wxGA_HORIZONTAL);
	Gauge->SetValue(0);
	controlSizer->Add(Gauge, 0, wxALL | wxEXPAND, 5);

	starColorButton = new wxButton(this, wxID_ANY, wxT("kolor gwiazdki"), wxDefaultPosition, wxDefaultSize, 0);
	controlSizer->Add(starColorButton, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);

	textArea = new wxTextCtrl(this, wxID_ANY, wxT("tekst"), wxDefaultPosition, wxDefaultSize, 0);
	controlSizer->Add(textArea, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);

	wxString shapeChoiceButtonChoices[] = { wxT("gwiazdka"), wxT("ksiezyc"), wxT("slonko") };
	int shapeChoiceButtonNChoices = sizeof(shapeChoiceButtonChoices) / sizeof(wxString);
	shapeChoiceButton = new wxChoice(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, shapeChoiceButtonNChoices, shapeChoiceButtonChoices, 0);
	shapeChoiceButton->SetSelection(0);
	controlSizer->Add(shapeChoiceButton, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);


	mainSizer->Add(controlSizer, 0, wxALIGN_RIGHT, 5);


	this->SetSizer(mainSizer);
	this->Layout();

	this->Centre(wxBOTH);

	// Connect Events
	mainPanel->Connect(wxEVT_UPDATE_UI, wxUpdateUIEventHandler(MyFrame1::sizeChanged), NULL, this);
	saveToFileButton->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame1::SaveToFile), NULL, this);
	bananCheckBox->Connect(wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(MyFrame1::boolBanan), NULL, this);
	bananPositionBar->Connect(wxEVT_SCROLL_TOP, wxScrollEventHandler(MyFrame1::scrollMoved), NULL, this);
	bananPositionBar->Connect(wxEVT_SCROLL_BOTTOM, wxScrollEventHandler(MyFrame1::scrollMoved), NULL, this);
	bananPositionBar->Connect(wxEVT_SCROLL_LINEUP, wxScrollEventHandler(MyFrame1::scrollMoved), NULL, this);
	bananPositionBar->Connect(wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler(MyFrame1::scrollMoved), NULL, this);
	bananPositionBar->Connect(wxEVT_SCROLL_PAGEUP, wxScrollEventHandler(MyFrame1::scrollMoved), NULL, this);
	bananPositionBar->Connect(wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler(MyFrame1::scrollMoved), NULL, this);
	bananPositionBar->Connect(wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler(MyFrame1::scrollMoved), NULL, this);
	bananPositionBar->Connect(wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler(MyFrame1::scrollMoved), NULL, this);
	bananPositionBar->Connect(wxEVT_SCROLL_CHANGED, wxScrollEventHandler(MyFrame1::scrollMoved), NULL, this);
	starColorButton->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame1::starColor), NULL, this);
	textArea->Connect(wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(MyFrame1::textChanged), NULL, this);
	shapeChoiceButton->Connect(wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler(MyFrame1::shapeChoice), NULL, this);
}

MyFrame1::~MyFrame1()
{
	// Disconnect Events
	mainPanel->Disconnect(wxEVT_UPDATE_UI, wxUpdateUIEventHandler(MyFrame1::sizeChanged), NULL, this);
	saveToFileButton->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame1::SaveToFile), NULL, this);
	bananCheckBox->Disconnect(wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(MyFrame1::boolBanan), NULL, this);
	bananPositionBar->Disconnect(wxEVT_SCROLL_TOP, wxScrollEventHandler(MyFrame1::scrollMoved), NULL, this);
	bananPositionBar->Disconnect(wxEVT_SCROLL_BOTTOM, wxScrollEventHandler(MyFrame1::scrollMoved), NULL, this);
	bananPositionBar->Disconnect(wxEVT_SCROLL_LINEUP, wxScrollEventHandler(MyFrame1::scrollMoved), NULL, this);
	bananPositionBar->Disconnect(wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler(MyFrame1::scrollMoved), NULL, this);
	bananPositionBar->Disconnect(wxEVT_SCROLL_PAGEUP, wxScrollEventHandler(MyFrame1::scrollMoved), NULL, this);
	bananPositionBar->Disconnect(wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler(MyFrame1::scrollMoved), NULL, this);
	bananPositionBar->Disconnect(wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler(MyFrame1::scrollMoved), NULL, this);
	bananPositionBar->Disconnect(wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler(MyFrame1::scrollMoved), NULL, this);
	bananPositionBar->Disconnect(wxEVT_SCROLL_CHANGED, wxScrollEventHandler(MyFrame1::scrollMoved), NULL, this);
	starColorButton->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame1::starColor), NULL, this);
	textArea->Disconnect(wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(MyFrame1::textChanged), NULL, this);
	shapeChoiceButton->Disconnect(wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler(MyFrame1::shapeChoice), NULL, this);

}
