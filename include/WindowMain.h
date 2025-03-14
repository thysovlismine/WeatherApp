// WindowMain.h
#ifndef WINDOWMAIN_H
#define WINDOWMAIN_H

#include <wx/wx.h>
#include <wx/listbox.h>
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
    //panel
    wxPanel* panel;
    
    //text
    wxTextCtrl* textCtrl;

    //button
    wxButton* fetchButton;
    void OnFetchData(wxCommandEvent& event);
    void FetchData();
    void OnFetchComplete(wxThreadEvent& event);

    //listbox
    wxListBox* listBox;
    void OnItemDoubleClicked(wxCommandEvent& event);


    
};

#endif // WINDOWMAIN_H
