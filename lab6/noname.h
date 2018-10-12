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
#include <wx/string.h>
#include <wx/button.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/checkbox.h>
#include <wx/sizer.h>
#include <wx/textctrl.h>
#include <wx/panel.h>
#include <wx/frame.h>
#include <wx/file.h>
#include <wx/dialog.h>
#include <wx/filedlg.h>
#include <wx/dcmemory.h>
#include <wx/dcclient.h>
#include <wx/rawbmp.h>
#include <wx/dcbuffer.h>
#include <wx/bitmap.h>
#include <wx/dcclient.h>
#include <wx/gauge.h>
#include <wx/event.h>



///////////////////////////////////////////////////////////////////////////
#include "CImg.h"
#include "FreeImage.h"
#include "FreeImagePlus.h"
#include <wx/timer.h>
#include <vector>
///////////////////////////////////////////////////////////////////////////////
/// Class MyFrame1
///////////////////////////////////////////////////////////////////////////////
class MyFrame1 : public wxFrame 
{
	private:
	
	protected:
		wxButton* m_loadImageButton;
		wxButton* m_censhorshipButton;
		wxButton* m_erodeButton;
		wxCheckBox* m_animationCheck;
		wxTextCtrl* m_exifText;
		wxPanel* m_imagePanel;
		wxGauge* m_loadingBar;

		fipImage freeIMG;
		wxBitmap bitmapWX;
		wxImage imageWX;
		wxImage orgImageWx;
		cimg_library::CImg<unsigned char> imageCchar;
		cimg_library::CImg<float> imageCfloat;

		
		// Virtual event handlers, overide them in your derived class
		virtual void loadImage(wxCommandEvent& event);
		virtual void censorship(wxCommandEvent& event);
		virtual void erode(wxCommandEvent& event);
		virtual void Animation(wxCommandEvent& event);
		virtual void sizeChanged(wxUpdateUIEvent& event);

		void update();
		void wxToCImgFloat(wxImage &imgWX, cimg_library::CImg<float> &imgCImg);
		void CImgToWxFloat(wxImage &imgWX, cimg_library::CImg<float> &imgCImg);
		void wxToCImgChar(wxImage &imgWX, cimg_library::CImg<unsigned char> &imgCImg);
		void CImgToWxChar(wxImage &imgWX, cimg_library::CImg<unsigned char> &imgCImg);

		void onIdle(wxIdleEvent& e);
		void OnTimer(wxTimerEvent& e);

		bool animationOn;
		bool imageLoaded;

		std::vector<wxBitmap> m_animationBitmaps;
		wxTimer m_timer;

	
	public:
		
		MyFrame1( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 1100,553 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
		
		~MyFrame1();
	
};

#endif //__NONAME_H__
