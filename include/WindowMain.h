// WindowMain.h
#pragma once
#ifndef WINDOWMAIN_H
#define WINDOWMAIN_H

#include <wx/wx.h>
#include <wx/listbox.h>
#include <wx/thread.h>
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
#include <thread>
#include "Panel.h"
#include "PanelStart.h"
#include "PanelAbout.h"

wxDECLARE_EVENT(wxEVT_FETCH_COMPLETE, wxThreadEvent);

using json = nlohmann::json;

class WindowMain : public wxFrame {
    public:
    WindowMain();

    //main panel
    Panel* panel_start;
    
};

#endif // WINDOWMAIN_H
