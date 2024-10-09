#include "MyFrame.h"
#include <wx/wx.h>

// Application class derived from wxApp
class MyApp : public wxApp {
public:
    virtual bool OnInit() override;
};

// Macro to implement the application entry point
wxIMPLEMENT_APP(MyApp);

// Called on application startup
bool MyApp::OnInit() {
    MyFrame* frame = new MyFrame("TV Series and Movie Manager", wxPoint(50, 50), wxSize(600, 400));
    frame->Show(true);  // Show the main frame
    return true;        // Return true to signal successful initialization
}







































//#include <wx/wx.h>
//#include "MyFrame.h"    // Include the header for the main window
//
//class MyApp : public wxApp {
//public:
//    virtual bool OnInit() override;
//};
//
//wxIMPLEMENT_APP(MyApp);
//
//bool MyApp::OnInit() {
//    MyFrame* frame = new MyFrame("My wxWidgets App", wxPoint(50, 50), wxSize(450, 340));
//    frame->Show(true);
//    return true;
//}
