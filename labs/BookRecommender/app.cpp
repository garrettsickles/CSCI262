#include "wx/wxprec.h"
#ifndef WC_PRECOMP
	#include "wx/wx.h"
#endif
#include "frame.h"

class recommender_app: public wxApp {
	bool OnInit();
};

bool recommender_app::OnInit() {
	recommender_frame* frame = new recommender_frame();
	frame->Show(true);
	SetTopWindow(frame);
	return true;
}

// required macro from wxWidgets - sets up and launches app
IMPLEMENT_APP(recommender_app)
