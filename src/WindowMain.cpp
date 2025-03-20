// WindowMain.cpp
#include "WindowMain.h"
#include "PanelStart.h"

wxDEFINE_EVENT(wxEVT_FETCH_COMPLETE, wxThreadEvent);

WindowMain::WindowMain() : wxFrame(nullptr, wxID_ANY, "???", wxDefaultPosition, wxSize(640, 480)) {
    // GUI Elements
    //panel = new wxPanel(this);
    
    //set globals
    mainWindow = this;
    mainSizer = new wxBoxSizer(wxVERTICAL);
    SetSizer(mainSizer);

    //run Panel Start
    panel_start = new PanelStart();
}

