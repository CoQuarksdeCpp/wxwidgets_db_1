#include "MyFrame.h"
#include "MyDatabase.h"  // Include the database logic for SQLite3
#include <wx/datectrl.h> // Include for wxDatePickerCtrl

// Event table mapping the menu items to their handlers
wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)
EVT_MENU(wxID_EXIT, MyFrame::OnQuit)                  // Exit handler
EVT_MENU(ID_Connect, MyFrame::OnConnect)              // Connect handler
EVT_MENU(ID_AddTVSeries, MyFrame::OnAddTVSeries)      // Add TV Series handler
EVT_MENU(ID_AddMovie, MyFrame::OnAddMovie)            // Add Movie handler
EVT_MENU(ID_Query, MyFrame::OnQuery)                  // Query handler (under construction)
EVT_MENU(ID_ShowDatabase, MyFrame::ShowAvailableDatabase) // Show available database handler
wxEND_EVENT_TABLE()

// Constructor: Create the main window and menu bar
MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
    : wxFrame(nullptr, wxID_ANY, title, pos, size) {

    // Create File menu
    wxMenu* menuFile = new wxMenu;
    menuFile->Append(wxID_EXIT, "E&xit\tAlt-X", "Quit the application");

    // Create DB menu with Connect, Add TV Series, Add Movie, Query items, and Show Database
    wxMenu* menuDB = new wxMenu;
    menuDB->Append(ID_Connect, "Connect", "Connect to the SQLite3 Database");  // Connect to database
    menuDB->Append(ID_AddTVSeries, "Add TV Series", "Add a new TV series");    // Add TV series
    menuDB->Append(ID_AddMovie, "Add Movie", "Add a new movie");               // Add movie
    menuDB->Append(ID_Query, "Query", "Run a query (Under Construction)");     // Placeholder query
    menuDB->Append(ID_ShowDatabase, "Show Database", "Show available database"); // Show connected database

    // Create the menu bar
    wxMenuBar* menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "&File");   // Add File menu
    menuBar->Append(menuDB, "&DB");       // Add DB menu

    // Set the menu bar for the window
    SetMenuBar(menuBar);
}


// Event handler for "Quit"
void MyFrame::OnQuit(wxCommandEvent& event) {
    Close(true);  // Close the window
}

// Event handler for "Connect"
void MyFrame::OnConnect(wxCommandEvent& event) {
    // Connect to the SQLite3 database and show a message box with the result
    if (InitDatabase("media.db")) {
        wxMessageBox("Connection successful!", "Database Status", wxOK | wxICON_INFORMATION);

        // SQL query to create the TVSeries table if it doesn't exist
        const char* createTVSeriesTable =
            "CREATE TABLE IF NOT EXISTS TVSeries ("
            "id INTEGER PRIMARY KEY AUTOINCREMENT, "
            "title TEXT NOT NULL, "
            "season INTEGER NOT NULL, "
            "episode INTEGER NOT NULL, "
            "studio TEXT, "
            "releaseDate TEXT, "
            "nextReleaseDate TEXT, "
            "referenceLink TEXT);";

        // Execute the query to create the TVSeries table
        ExecuteQuery(createTVSeriesTable);

        // SQL query to create the Movies table if it doesn't exist
        const char* createMoviesTable =
            "CREATE TABLE IF NOT EXISTS Movies ("
            "id INTEGER PRIMARY KEY AUTOINCREMENT, "
            "title TEXT NOT NULL, "
            "studio TEXT, "
            "year INTEGER NOT NULL, "
            "releaseDate TEXT, "
            "referenceLink TEXT);";

        // Execute the query to create the Movies table
        ExecuteQuery(createMoviesTable);
    }
    else {
        wxMessageBox("Failed to connect to the database.", "Database Status", wxOK | wxICON_ERROR);
    }
}

// Event handler for "Add TV Series"
void MyFrame::OnAddTVSeries(wxCommandEvent& event) {
    // Create a dialog to add a new TV series
    wxDialog* dialog = new wxDialog(this, wxID_ANY, "Add TV Series", wxDefaultPosition, wxSize(600, 800));
    wxBoxSizer* vbox = new wxBoxSizer(wxVERTICAL);

    // Input fields for TV series details
    wxTextCtrl* titleCtrl = new wxTextCtrl(dialog, wxID_ANY);
    wxTextCtrl* seasonCtrl = new wxTextCtrl(dialog, wxID_ANY);
    wxTextCtrl* episodeCtrl = new wxTextCtrl(dialog, wxID_ANY);
    wxTextCtrl* studioCtrl = new wxTextCtrl(dialog, wxID_ANY);
    wxDatePickerCtrl* releaseDateCtrl = new wxDatePickerCtrl(dialog, wxID_ANY);
    wxTextCtrl* nextReleaseCtrl = new wxTextCtrl(dialog, wxID_ANY);
    wxTextCtrl* referenceLinkCtrl = new wxTextCtrl(dialog, wxID_ANY);

    // Add labels and text fields to the dialog
    vbox->Add(new wxStaticText(dialog, wxID_ANY, "Title"), 0, wxALL, 5);
    vbox->Add(titleCtrl, 0, wxALL | wxEXPAND, 5);
    vbox->Add(new wxStaticText(dialog, wxID_ANY, "Season"), 0, wxALL, 5);
    vbox->Add(seasonCtrl, 0, wxALL | wxEXPAND, 5);
    vbox->Add(new wxStaticText(dialog, wxID_ANY, "Episode"), 0, wxALL, 5);
    vbox->Add(episodeCtrl, 0, wxALL | wxEXPAND, 5);
    vbox->Add(new wxStaticText(dialog, wxID_ANY, "Studio"), 0, wxALL, 5);
    vbox->Add(studioCtrl, 0, wxALL | wxEXPAND, 5);
    vbox->Add(new wxStaticText(dialog, wxID_ANY, "Release Date"), 0, wxALL, 5);
    vbox->Add(releaseDateCtrl, 0, wxALL | wxEXPAND, 5);
    vbox->Add(new wxStaticText(dialog, wxID_ANY, "Next Release Date"), 0, wxALL, 5);
    vbox->Add(nextReleaseCtrl, 0, wxALL | wxEXPAND, 5);
    vbox->Add(new wxStaticText(dialog, wxID_ANY, "Reference Link"), 0, wxALL, 5);
    vbox->Add(referenceLinkCtrl, 0, wxALL | wxEXPAND, 5);

    // Add Save and Cancel buttons to the dialog in a horizontal box sizer
    wxBoxSizer* hbox = new wxBoxSizer(wxHORIZONTAL);
    wxButton* saveButton = new wxButton(dialog, wxID_OK, "Save");
    wxButton* cancelButton = new wxButton(dialog, wxID_CANCEL, "Cancel");
    hbox->Add(saveButton, 1, wxALL | wxEXPAND, 5);
    hbox->Add(cancelButton, 1, wxALL | wxEXPAND, 5);

    vbox->Add(hbox, 0, wxALIGN_CENTER | wxALL, 10);  // Add horizontal box with buttons to the vertical sizer

    dialog->SetSizer(vbox);
    dialog->Layout(); // Ensure layout is applied
    dialog->ShowModal();

    // Get the values from the input fields if Save is pressed
    if (dialog->GetReturnCode() == wxID_OK) {
        std::string title = titleCtrl->GetValue().ToStdString();
        int season = std::stoi(seasonCtrl->GetValue().ToStdString());
        int episode = std::stoi(episodeCtrl->GetValue().ToStdString());
        std::string studio = studioCtrl->GetValue().ToStdString();
        std::string releaseDate = releaseDateCtrl->GetValue().FormatISODate().ToStdString();
        std::string nextRelease = nextReleaseCtrl->GetValue().ToStdString();
        std::string referenceLink = referenceLinkCtrl->GetValue().ToStdString();

        // Insert the TV series information into the SQLite3 database
        std::string query = "INSERT INTO TVSeries (title, season, episode, studio, releaseDate, nextReleaseDate, referenceLink) "
            "VALUES ('" + title + "', " + std::to_string(season) + ", " + std::to_string(episode) + ", '" +
            studio + "', '" + releaseDate + "', '" + nextRelease + "', '" + referenceLink + "');";
        ExecuteQuery(query.c_str());
    }

    dialog->Destroy();
}

// Event handler for "Add Movie"
void MyFrame::OnAddMovie(wxCommandEvent& event) {
    // Create a dialog to add a new movie
    wxDialog* dialog = new wxDialog(this, wxID_ANY, "Add Movie", wxDefaultPosition, wxSize(600, 800));
    wxBoxSizer* vbox = new wxBoxSizer(wxVERTICAL);

    // Input fields for movie details
    wxTextCtrl* titleCtrl = new wxTextCtrl(dialog, wxID_ANY);
    wxTextCtrl* studioCtrl = new wxTextCtrl(dialog, wxID_ANY);
    wxTextCtrl* yearCtrl = new wxTextCtrl(dialog, wxID_ANY);
    wxDatePickerCtrl* releaseDateCtrl = new wxDatePickerCtrl(dialog, wxID_ANY);
    wxTextCtrl* referenceLinkCtrl = new wxTextCtrl(dialog, wxID_ANY);

    // Add labels and text fields to the dialog
    vbox->Add(new wxStaticText(dialog, wxID_ANY, "Title"), 0, wxALL, 5);
    vbox->Add(titleCtrl, 0, wxALL | wxEXPAND, 5);
    vbox->Add(new wxStaticText(dialog, wxID_ANY, "Studio"), 0, wxALL, 5);
    vbox->Add(studioCtrl, 0, wxALL | wxEXPAND, 5);
    vbox->Add(new wxStaticText(dialog, wxID_ANY, "Year"), 0, wxALL, 5);
    vbox->Add(yearCtrl, 0, wxALL | wxEXPAND, 5);
    vbox->Add(new wxStaticText(dialog, wxID_ANY, "Release Date"), 0, wxALL, 5);
    vbox->Add(releaseDateCtrl, 0, wxALL | wxEXPAND, 5);
    vbox->Add(new wxStaticText(dialog, wxID_ANY, "Reference Link"), 0, wxALL, 5);
    vbox->Add(referenceLinkCtrl, 0, wxALL | wxEXPAND, 5);

    // Add Save and Cancel buttons to the dialog in a horizontal box sizer
    wxBoxSizer* hbox = new wxBoxSizer(wxHORIZONTAL);
    wxButton* saveButton = new wxButton(dialog, wxID_OK, "Save");
    wxButton* cancelButton = new wxButton(dialog, wxID_CANCEL, "Cancel");
    hbox->Add(saveButton, 1, wxALL | wxEXPAND, 5);
    hbox->Add(cancelButton, 1, wxALL | wxEXPAND, 5);

    vbox->Add(hbox, 0, wxALIGN_CENTER | wxALL, 10);  // Add horizontal box with buttons to the vertical sizer

    dialog->SetSizer(vbox);
    dialog->Layout(); // Ensure layout is applied
    dialog->ShowModal();

    // Get the values from the input fields if Save is pressed
    if (dialog->GetReturnCode() == wxID_OK) {
        std::string title = titleCtrl->GetValue().ToStdString();
        std::string studio = studioCtrl->GetValue().ToStdString();
        int year = std::stoi(yearCtrl->GetValue().ToStdString());
        std::string releaseDate = releaseDateCtrl->GetValue().FormatISODate().ToStdString();
        std::string referenceLink = referenceLinkCtrl->GetValue().ToStdString();

        // Insert the movie information into the SQLite3 database
        std::string query = "INSERT INTO Movies (title, studio, year, releaseDate, referenceLink) "
            "VALUES ('" + title + "', '" + studio + "', " + std::to_string(year) + ", '" +
            releaseDate + "', '" + referenceLink + "');";
        ExecuteQuery(query.c_str());
    }

    dialog->Destroy();
}


// Event handler for the "Query" button (currently under construction)
void MyFrame::OnQuery(wxCommandEvent& event) {
    // Placeholder functionality to indicate that the feature is under construction
    wxMessageBox("Under Construction", "Query Status", wxOK | wxICON_INFORMATION);
}

// Event handler to show the current connected database
void MyFrame::ShowAvailableDatabase(wxCommandEvent& event) {
    // Check if the database connection is active and display a message box
    if (db != nullptr) {
        wxMessageBox("Currently connected to 'media.db'", "Database Status", wxOK | wxICON_INFORMATION);
    }
    else {
        wxMessageBox("No database connection available.", "Database Status", wxOK | wxICON_WARNING);
    }
}





































//#include "MyFrame.h"
//#include "MyDatabase.h"  // Include the database logic
//
//// Event table: map events to handler functions
//wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)
//EVT_MENU(wxID_EXIT, MyFrame::OnQuit)              // Quit handler
//EVT_MENU(ID_Connect, MyFrame::OnConnect)            // Connect handler
//EVT_MENU(ID_Query, MyFrame::OnQuery)              // Query handler (show "Under Construction")
//wxEND_EVENT_TABLE()
//
//// Constructor for MyFrame
//MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
//    : wxFrame(nullptr, wxID_ANY, title, pos, size) {
//
//    // Create the File menu
//    wxMenu* menuFile = new wxMenu;
//    menuFile->Append(wxID_EXIT, "E&xit\tAlt-X", "Quit the application");
//
//    // Create the DB menu (with Connect and Query options)
//    wxMenu* menuDB = new wxMenu;
//    menuDB->Append(ID_Connect, "Connect", "Connect to the SQLite3 Database");  // Connect button
//    menuDB->Append(ID_Query, "Query", "Run a query (Under Construction)");   // Query button
//
//    // Create the menu bar
//    wxMenuBar* menuBar = new wxMenuBar;
//    menuBar->Append(menuFile, "&File");   // Add File menu
//    menuBar->Append(menuDB, "&DB");       // Add DB menu
//
//    // Set the menu bar for this frame
//    SetMenuBar(menuBar);
//}
//
//// Event handler for the "Quit" button
//void MyFrame::OnQuit(wxCommandEvent& event) {
//    Close(true);  // Close the window
//}
//
//// Event handler for the "Connect" button in the "DB" menu
//void MyFrame::OnConnect(wxCommandEvent& event) {
//    // Connect to the SQLite3 database
//    if (InitDatabase("example.db")) {
//        wxMessageBox("Connection successful!", "Database Status", wxOK | wxICON_INFORMATION);
//    }
//    else {
//        wxMessageBox("Failed to connect to the database.", "Database Status", wxOK | wxICON_ERROR);
//    }
//}
//
//// Event handler for the "Query" button in the "DB" menu
//void MyFrame::OnQuery(wxCommandEvent& event) {
//    // Show a pop-up indicating the feature is under construction
//    wxMessageBox("Under Construction", "Query Status", wxOK | wxICON_AUTH_NEEDED);
//}



















//#include "MyFrame.h"
//#include "MyDatabase.h"  // Include database logic
//
//wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)
//EVT_MENU(wxID_EXIT, MyFrame::OnQuit)           // Quit handler
//EVT_MENU(wxID_ANY, MyFrame::OnConnect)         // Connect handler
//wxEND_EVENT_TABLE()
//
//MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
//    : wxFrame(nullptr, wxID_ANY, title, pos, size) {
//    wxMenu* menuFile = new wxMenu;
//    menuFile->Append(wxID_ANY, "Connect to Database", "Connect to SQLite3 Database");  // Connect button
//    menuFile->Append(wxID_EXIT, "E&xit\tAlt-X", "Quit the application");
//
//    wxMenuBar* menuBar = new wxMenuBar;
//    menuBar->Append(menuFile, "&File");
//    SetMenuBar(menuBar);
//}
//
//void MyFrame::OnQuit(wxCommandEvent& event) {
//    Close(true);  // Close the window
//}
//
//
//// Event handler for the "Connect" button
//void MyFrame::OnConnect(wxCommandEvent& event) {
//    if (InitDatabase("example.db")) {
//        wxMessageBox("Connection successful!", "Database Status", wxOK | wxICON_INFORMATION);
//    }
//    else {
//        wxMessageBox("Failed to connect to the database.", "Database Status", wxOK | wxICON_ERROR);
//    }
//}