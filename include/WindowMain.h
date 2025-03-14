// WindowMain.h
#ifndef WINDOWMAIN_H
#define WINDOWMAIN_H

#include <wx/wx.h>
#include <wx/thread.h>
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
#include <thread>

wxDECLARE_EVENT(wxEVT_FETCH_COMPLETE, wxThreadEvent);

using json = nlohmann::json;

class WindowMain : public wxFrame {
public:
    WindowMain();

private:
    wxPanel* panel;
    wxTextCtrl* textCtrl;
    wxButton* fetchButton;

    void OnFetchData(wxCommandEvent& event);
    void FetchData();
    void OnFetchComplete(wxThreadEvent& event);
};

#endif // WINDOWMAIN_H
