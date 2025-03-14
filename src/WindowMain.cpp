// WindowMain.cpp
#include "WindowMain.h"

wxDEFINE_EVENT(wxEVT_FETCH_COMPLETE, wxThreadEvent);

WindowMain::WindowMain() : wxFrame(nullptr, wxID_ANY, "REST API Data Fetcher 2", wxDefaultPosition, wxSize(640, 480)) {
    // GUI Elements
    //panel = new wxPanel(this);
    
    //set mainWindow
    mainWindow = this;

    //run Panel Start
    panel_start = new PanelStart();
}

