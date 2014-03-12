#pragma once

#include <string>
#include <queue>
#include <unordered_map>
#include <utility>

#include "wx/wxprec.h"
#ifndef WC_PRECOMP
        #include "wx/wx.h"
#endif
#include "wx/listctrl.h"
#include "wxWidgets/include/wx/textdlg.h"

#include "library.h"

const std::string GUEST_NAME = "Guest User";

class recommender_frame : public wxFrame {
public:
	// constructor 
	recommender_frame() : wxFrame((wxWindow*)NULL, wxID_ANY, wxT("")) {
		setup(); 
	}
	~recommender_frame();

	// menu event handlers
	void on_menu_about(wxCommandEvent&);
	void on_menu_quit(wxCommandEvent&);
	void on_menu_save(wxCommandEvent&);
	void on_menu_user_add_or_login(wxCommandEvent&);
	void on_menu_user_delete(wxCommandEvent&);
	void on_menu_book_add(wxCommandEvent&);
	void on_menu_book_delete(wxCommandEvent&);
	void on_menu_book_sort_by_author(wxCommandEvent&);
	void on_menu_book_sort_by_title(wxCommandEvent&);
	void on_book_select(wxListEvent&);
	void on_option_select(wxCommandEvent&);

private:
	// model
	library* lib;
	std::vector<int> book_list_index;
	std::multimap<std::string, int> byAuthor;
	std::map<std::string, int> byTitle;
	std::multimap<int, int> byRating;
	long user;

	// dynamic controls
	wxListView* book_list;
	wxRadioBox* option_box;
	wxTextCtrl* recommendation_text;
	wxTextEntryDialog* user_add_or_login_popup;
	wxMessageDialog* user_add_popup;
	wxTextEntryDialog* user_delete_popup;
	wxTextEntryDialog* book_add_popup;
	wxTextEntryDialog* book_delete_popup;

	// initialization and setup
	void setup();
	void initializeBookListIndex();
	void loadBookList();
	std::pair<std::string, std::string> bookParser(std::string);

	// Boilerplate event handling macro from wxWidgets
	DECLARE_EVENT_TABLE()
};
