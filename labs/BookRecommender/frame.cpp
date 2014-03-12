#include "frame.h"
#include <string>

using namespace std;

// My own macro for converting std::string to wxString,
// because wxWidgets 2.8 doesn't provide a proper conversion
// constructor for strings.
#define WXSTRING(A) wxString::FromAscii(A.c_str())


recommender_frame::~recommender_frame()
{
}

// ************************************************************************
// EVENT HANDLERS 

void recommender_frame::on_menu_about(wxCommandEvent& event) {
	wxMessageBox(	wxT("CSCI 262 Fall 2013, Lab 6: Recommender App"), 
			wxT("About Recommender"),
			wxOK | wxICON_INFORMATION );
}

void recommender_frame::on_menu_quit(wxCommandEvent& event) {
	Close(true);
}

void recommender_frame::on_menu_save(wxCommandEvent& event) {
	lib->deleteReader(GUEST_NAME);
	lib->save("books.txt", "ratings.txt");
	lib->addReader(GUEST_NAME);
	wxMessageBox(wxT("Library Saved!"), wxT("Library Save Confirmation"), wxOK | wxICON_INFORMATION );
}

void recommender_frame::on_menu_user_add_or_login(wxCommandEvent& event) {
	if(user_add_or_login_popup->ShowModal() == wxID_OK) {
		if(lib->isReader(user_add_or_login_popup->GetValue().ToStdString())) {
			user = lib->findReader(user_add_or_login_popup->GetValue().ToStdString());
			SetTitle(wxT("CSCI 262 Recommender App: Logged in as " + user_add_or_login_popup->GetValue().ToStdString()));
			wxMessageBox(wxT("Logged in as: " + user_add_or_login_popup->GetValue()), wxT("Login Confirmation"), wxOK | wxICON_INFORMATION );
		}
		else
		{
			user_add_popup->SetMessage(wxT("A user with the name \"" + user_add_or_login_popup->GetValue().ToStdString() + "\" was not found...\nWould you like to add this user?"));
			if(user_add_popup->ShowModal() == wxID_YES)
			{
				user = lib->addReader(user_add_or_login_popup->GetValue().ToStdString());
				wxMessageBox(wxT("Logged in as: " + user_add_or_login_popup->GetValue()), wxT("Login Confirmation"), wxOK | wxICON_INFORMATION );
				SetTitle(wxT("CSCI 262 Recommender App: Logged in as " + user_add_or_login_popup->GetValue().ToStdString()));
			}
			else
			{
				user = lib->findReader(GUEST_NAME);
				wxMessageBox(wxT("Did not login as: " + user_add_or_login_popup->GetValue() + "\nLogged in as Guest User"), wxT("Login Confirmation"), wxOK | wxICON_INFORMATION );
			}
		}
		for(int i = 0; i < lib->catalogSize(); i++)
		{
			book_list->SetItem(i, 2, WXSTRING(lib->getRatingDescription(user, i)));
		}
	}
}

void recommender_frame::on_menu_user_delete(wxCommandEvent& event) {
	if(user_delete_popup->ShowModal() == wxID_OK)
	{
		if(lib->isReader(user_delete_popup->GetValue().ToStdString())) {
			if(lib->findReader(user_delete_popup->GetValue().ToStdString()) == user)
			{
				user = lib->findReader(GUEST_NAME);
				SetTitle(wxT("CSCI 262 Recommender App: Logged in as " + GUEST_NAME));
				for(int i = 0; i < lib->catalogSize(); i++)
				{
					book_list->SetItem(i, 2, WXSTRING(lib->getRatingDescription(user, i)));
				}
			}
			lib->deleteReader(user_delete_popup->GetValue().ToStdString());
			wxMessageBox(wxT("User \"" + user_delete_popup->GetValue() + "\" successfully deleted!"), wxT("User Delete Confirmation"), wxOK | wxICON_INFORMATION );
		}
		else
		{
			wxMessageBox(wxT("User \"" + user_delete_popup->GetValue() + "\" not found...\nDeletion Failed!"), wxT("User Delete Failure"), wxOK | wxICON_INFORMATION );
		}
	}
}

void recommender_frame::on_menu_book_add(wxCommandEvent& event) {
	book_add_popup->SetValue(wxT("[TITLE](AUTHOR)"));
	if(book_add_popup->ShowModal() == wxID_OK)
	{
		std::pair<std::string, std::string> test = bookParser(book_add_popup->GetValue().ToStdString());
		if(lib->isBook(test.second, test.first)) {
			wxMessageBox(wxT("Cannot add the book " + test.first + " by " + test.second + " because it already exists!"), wxT("Book Addition Error"), wxOK | wxICON_INFORMATION);
		}
		else
		{
			lib->addBook(test.second, test.first);
			wxMessageBox(wxT("The book " + test.first + " by " + test.second + " was succesfully Added!"), wxT("Book Addition Confirmation"), wxOK | wxICON_INFORMATION );
		}
	}
	on_menu_book_sort_by_author(event);
	loadBookList();
}

void recommender_frame::on_menu_book_delete(wxCommandEvent& event) {
	if(book_list->GetFirstSelected() > -1)
	{
		book_delete_popup->SetValue(wxT("[" + book_list->GetItemText(book_list->GetFirstSelected(), 0).ToStdString() + "](" + book_list->GetItemText(book_list->GetFirstSelected(), 1).ToStdString() + ")"));
	}
	else
	{
		book_delete_popup->SetValue(wxT("[TITLE](AUTHOR)"));
	}
	if(book_delete_popup->ShowModal() == wxID_OK)
	{
		std::pair<std::string, std::string> test = bookParser(book_delete_popup->GetValue().ToStdString());
		if(!lib->isBook(test.first, test.second)) {
			wxMessageBox(wxT("Cannot delete the book " + test.second + " by " + test.first + " because it doesn't exist yet!"), wxT("Book addition Error"), wxOK | wxICON_INFORMATION);
		}
		else
		{
			lib->deleteBook(test.first, test.second);
			wxMessageBox(wxT("The book " + test.second + " by " + test.first + " was succesfully deleted!"), wxT("Book Deletion Confirmation"), wxOK | wxICON_INFORMATION );
		}
	}
	on_menu_book_sort_by_author(event);
	loadBookList();
}

void recommender_frame::on_menu_book_sort_by_author(wxCommandEvent&)
{
	byAuthor.clear();
	book_list_index.clear();
	initializeBookListIndex();
	std::string a;
	for(int i = 0; i < book_list_index.size(); i++)
	{
		a = lib->getBook(book_list_index[i]).first;
		a = a.substr(a.find_last_of(' ') + 1, a.size() - a.find_last_of(' ')) + a.substr(0, a.find_first_of(' ') - 1);
		transform(a.begin(), a.end(), a.begin(), toupper);
		byAuthor.insert(std::pair<std::string, int>(a, book_list_index[i]));
	}
	int j = 0;
	for(std::multimap<std::string, int>::iterator it = byAuthor.begin(); it != byAuthor.end(); it++)
	{
		book_list_index[j++] = it->second;
	}
	loadBookList();
}

void recommender_frame::on_menu_book_sort_by_title(wxCommandEvent&)
{
	byTitle.clear();
	book_list_index.clear();
	initializeBookListIndex();
	std::string a;
	for(int i = 0; i < book_list_index.size(); i++)
	{
		a = lib->getBook(book_list_index[i]).second;
		transform(a.begin(), a.end(), a.begin(), toupper);
		if(a.substr(0, 3) == "THE")
		{
			a = a.substr(4, a.size());
		}
		byTitle.insert(std::pair<std::string, int>(a, book_list_index[i]));
	}
	int j = 0;
	for(std::map<std::string, int>::iterator it = byTitle.begin(); it != byTitle.end(); it++)
	{
		book_list_index[j++] = it->second;
	}
	loadBookList();
}

void recommender_frame::on_book_select(wxListEvent& event) {
	option_box->SetLabel(wxT("Select your rating for: " + book_list->GetItemText(event.GetIndex(), 1)));
	for (int i = 0; i < RATINGS_COUNT; i++) {
		option_box->Show(i, true);
	}
	long current_book = book_list->GetFirstSelected();
	option_box->SetSelection(lib->getRatingIndex(user, current_book));
}

void recommender_frame::on_option_select(wxCommandEvent& event) {
	long current_book = book_list_index[book_list->GetFirstSelected()];
	lib->setRating(user, current_book, RATINGS[option_box->GetSelection()]);

	// update rating in book list, option box (we update option
	// box here, because we have to allow for possibility that
	// the model has rejected or modified the user selection).
	option_box->SetSelection(lib->getRatingIndex(user, current_book));
	book_list->SetItem(book_list->GetFirstSelected(), 2, WXSTRING(lib->getRatingDescription(user, current_book)));

	// update recommendations based on latest user rating
	std::string recs;
	std::stack<std::pair<std::string, int> > favs = lib->getRecommendations(user);
	while(!favs.empty())
	{
		recs += favs.top().first;
		recs += " (";
		recs += std::to_string(static_cast<long long>(favs.top().second));
		recs += ")\n";
		favs.pop();
	}
	recommendation_text->SetValue(WXSTRING(recs));
}

// control ids for event handling
enum {
	ID_MENU_ABOUT = 1,
	ID_MENU_QUIT,
	ID_MENU_SAVE,
	ID_MENU_USER_ADD_OR_LOGIN,
	ID_MENU_USER_DELETE,
	ID_MENU_BOOK_ADD,
	ID_MENU_BOOK_DELETE,
	ID_MENU_BOOK_SORT_BY_AUTHOR,
	ID_MENU_BOOK_SORT_BY_TITLE,
	ID_BOOK_LIST,
	ID_RATING_RADIO
};

// event binding macros (wxWidgets 2.8 required - no dynamic binding!)
BEGIN_EVENT_TABLE(recommender_frame, wxFrame)
	EVT_MENU(ID_MENU_ABOUT, recommender_frame::on_menu_about)
	EVT_MENU(ID_MENU_QUIT, recommender_frame::on_menu_quit)
	EVT_MENU(ID_MENU_SAVE, recommender_frame::on_menu_save)
	EVT_MENU(ID_MENU_USER_ADD_OR_LOGIN, recommender_frame::on_menu_user_add_or_login)
	EVT_MENU(ID_MENU_USER_DELETE, recommender_frame::on_menu_user_delete)
	EVT_MENU(ID_MENU_BOOK_ADD, recommender_frame::on_menu_book_add)
	EVT_MENU(ID_MENU_BOOK_DELETE, recommender_frame::on_menu_book_delete)
	EVT_MENU(ID_MENU_BOOK_SORT_BY_AUTHOR, recommender_frame::on_menu_book_sort_by_author)
	EVT_MENU(ID_MENU_BOOK_SORT_BY_TITLE, recommender_frame::on_menu_book_sort_by_title)
	EVT_LIST_ITEM_SELECTED(ID_BOOK_LIST, recommender_frame::on_book_select)
	EVT_RADIOBOX(ID_RATING_RADIO, recommender_frame::on_option_select)
END_EVENT_TABLE()

// ************************************************************************
// GUI SETUP
//

void recommender_frame::setup() {
	// top level window setup
	SetTitle(wxT("CSCI 262 Recommender App: Logged in as " + GUEST_NAME));
	SetPosition(wxPoint(50,50));
	SetSize(wxSize(800,600));
	lib = new library;
	user = lib->addReader(GUEST_NAME);
	lib->load("books.txt", "ratings.txt");
	

	// menu setup
	wxMenu* menu_file = new wxMenu;
	menu_file->Append(ID_MENU_SAVE, wxT("&Save Changes..."));
	menu_file->AppendSeparator();
	menu_file->Append(ID_MENU_ABOUT, wxT("&About..."));
	menu_file->Append(ID_MENU_QUIT, wxT("&Quit"));

	wxMenu* menu_user = new wxMenu;
	menu_user->Append(ID_MENU_USER_ADD_OR_LOGIN, wxT("&Add/Login..."));
	menu_user->Append(ID_MENU_USER_DELETE, wxT("&Delete..."));

	wxMenu* menu_book = new wxMenu;
	menu_book->Append(ID_MENU_BOOK_ADD, wxT("&Add..."));
	menu_book->Append(ID_MENU_BOOK_DELETE, wxT("&Delete..."));
	menu_book->AppendSeparator();
	menu_book->Append(ID_MENU_BOOK_SORT_BY_AUTHOR, wxT("&Sort by Author (A-Z)"));
	menu_book->Append(ID_MENU_BOOK_SORT_BY_TITLE, wxT("&Sort by Title (A-Z)"));

	wxMenuBar *menubar = new wxMenuBar;
	menubar->Append(menu_file, wxT("&File"));
	menubar->Append(menu_user, wxT("&User"));
	menubar->Append(menu_book, wxT("&Book"));

	SetMenuBar(menubar);

	// status bar
	CreateStatusBar();
	SetStatusText(wxT("Welcome to the recommender app!"));

	// Create a panel for the controls - this will make the
	// background not be gray on Windows
	wxPanel* panel = new wxPanel(this);

	// setup book list control
	wxStaticText* books_label = new wxStaticText(panel, wxID_ANY, wxT(""));
	books_label->SetLabel(wxT("Book List"));
	book_list = new wxListView(panel, ID_BOOK_LIST, wxDefaultPosition, wxDefaultSize, wxLC_REPORT | wxLC_SINGLE_SEL);
	wxListItem col;
	col.SetText(wxT("Author"));
	col.SetWidth(200);
	book_list->InsertColumn(0, col);
	col.SetText(wxT("Title"));
	book_list->InsertColumn(1, col);
	col.SetText(wxT("Your Rating"));
	book_list->InsertColumn(2, col);
	initializeBookListIndex();
	loadBookList();

	// setup rating option box
	wxArrayString options_array;
	int option_count = RATINGS_COUNT;
	for (int i = 0; i < option_count; i++) {
		options_array.Add(WXSTRING(RATINGS_DESCRIPTION[i]));
	}
	option_box = new wxRadioBox(
		panel, ID_RATING_RADIO, wxT(""),
		wxDefaultPosition, wxDefaultSize, options_array,
		0, wxRA_SPECIFY_COLS);
	// don't show options initially - wait until a book selection
	// is made
	for (int i = 0; i < option_count; i++) {
		option_box->Show(i, false);
	}

	// setup rating recommendations field
	wxStaticText* recommendation_label = new wxStaticText(panel, wxID_ANY, wxT(""));
	recommendation_label->SetLabel(wxT("Your Recommendations"));
	recommendation_text = new wxTextCtrl(
		panel, wxID_ANY, wxT(""), wxDefaultPosition, wxDefaultSize, 
		wxTE_MULTILINE | wxTE_READONLY | wxTE_LEFT);
	recommendation_text->SetValue(wxT("You don't have any recommendations yet.\n"));
	recommendation_text->AppendText(wxT("Try rating some books."));

	// setup login box
	user_add_or_login_popup = new wxTextEntryDialog(panel, wxT("Please Enter a Username"), wxT("User Add/Login Window"), wxT(""), wxOK | wxCANCEL, wxDefaultPosition);

	user_delete_popup = new wxTextEntryDialog(panel, wxT("Please Enter a Username"), wxT("User Delete Window"), wxT(""), wxOK | wxCANCEL, wxDefaultPosition);

	user_add_popup = new wxMessageDialog(panel, wxT(""), wxT("Login Failed"), wxCENTRE| wxYES_NO, wxDefaultPosition);

	book_add_popup = new wxTextEntryDialog(panel, wxT("Please Enter a Book in the Format: [Title](Author)"), wxT("Book Add Window"), wxT(""), wxOK | wxCANCEL, wxDefaultPosition);

	book_delete_popup = new wxTextEntryDialog(panel, wxT("Please Enter a Book in the Format: [Title](Author)"), wxT("Book Delete Window"), wxT(""), wxOK | wxCANCEL, wxDefaultPosition);

	// layout management
	wxBoxSizer *top_sizer = new wxBoxSizer(wxVERTICAL);
	top_sizer->Add(books_label, 0, wxTOP | wxLEFT | wxRIGHT, 5);
	top_sizer->Add(book_list, 5, wxEXPAND | wxALL, 5);
	top_sizer->Add(option_box, 0, wxEXPAND | wxALL, 5);
	top_sizer->Add(recommendation_label, 0, wxEXPAND | wxTOP | wxLEFT | wxRIGHT, 5);
	top_sizer->Add(recommendation_text, 3, wxEXPAND | wxALL, 5);

	panel->SetSizer(top_sizer);
}

std::pair<std::string, std::string> recommender_frame::bookParser(std::string text)
{
	return std::pair<std::string, std::string>(text.substr(text.find_first_of('[') + 1, text.find_last_of(']') - text.find_first_of('[') - 1), text.substr(text.find_first_of('(') + 1, text.find_last_of(')') - text.find_first_of('(') - 1));
}

void recommender_frame::initializeBookListIndex()
{
	book_list_index.clear();
	for(int i = 0; i < lib->catalogSize(); i++)
	{
		book_list_index.push_back(i);
	}
}

void recommender_frame::loadBookList()
{
	book_list->DeleteAllItems();
	for(int i = 0; i < lib->catalogSize(); i++) {
		wxListItem item;
		item.SetId(i);
		item.SetText(WXSTRING(lib->getBook(book_list_index[i]).first));
		book_list->InsertItem(item);
		book_list->SetItem(i, 1, WXSTRING(lib->getBook(book_list_index[i]).second));
		book_list->SetItem(i, 2, WXSTRING(lib->getRatingDescription(user, book_list_index[i])));
	}
}