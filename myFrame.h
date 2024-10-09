#pragma once

#include <wx/wx.h>
// #include <wx/frame.h>

// MyFrame class: Handles the main window and all event handling related to TV series and movies.
class MyFrame : public wxFrame {
public:
    MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);

private:
    // Event handlers for menu actions
    void OnQuit(wxCommandEvent& event);        // Handler for exiting the application
    void OnConnect(wxCommandEvent& event);     // Handler for connecting to the SQLite database
    void OnAddTVSeries(wxCommandEvent& event); // Handler for adding a new TV series
    void OnAddMovie(wxCommandEvent& event);    // Handler for adding a new movie
    void OnQuery(wxCommandEvent& event);       // Handler for the Query option
    void ShowAvailableDatabase(wxCommandEvent& event); // Show available connected database

    wxDECLARE_EVENT_TABLE();  // Declare the event table to map events to handler functions
};

// Define unique IDs for menu items
enum {
    ID_Connect = 1,       // ID for the "Connect" menu item
    ID_AddTVSeries,       // ID for adding a TV series
    ID_AddMovie,          // ID for adding a movie
    ID_Query,             // ID for querying (under construction)
    ID_ShowDatabase       // ID for showing available database
};
