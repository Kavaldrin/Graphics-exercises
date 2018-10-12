#include <wx/wxprec.h>
#include <wx/dcbuffer.h>
#include "noname.h"
#include "Implementation.h"

class MyApp : public wxApp
{
public:
	virtual bool OnInit();
};



wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{
	mainFrame *frame = new mainFrame(NULL);
	frame->Show(true);
	return true;
}

