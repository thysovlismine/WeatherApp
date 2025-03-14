#include <wx/wx.h>
#include <wx/thread.h>
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
#include <iostream>
#include <thread>

using json = nlohmann::json;

// Custom event for thread-safe UI updates
wxDECLARE_EVENT(wxEVT_FETCH_COMPLETE, wxThreadEvent);
wxDEFINE_EVENT(wxEVT_FETCH_COMPLETE, wxThreadEvent);

//================================================================
#pragma region WindowMain

class WindowMain : public wxFrame {
public:
    WindowMain() : wxFrame(nullptr, wxID_ANY, "REST API Data Fetcher 2", wxDefaultPosition, wxSize(600, 400)) {
        
        // GUI Elements
        panel = new wxPanel(this);
        textCtrl = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(10, 10), wxSize(560, 300), wxTE_MULTILINE | wxTE_READONLY);
        fetchButton = new wxButton(panel, wxID_ANY, "Fetch Data", wxPoint(10, 320), wxSize(100, 30));

        // Events
        fetchButton->Bind(wxEVT_BUTTON, &WindowMain::OnFetchData, this);
        Bind(wxEVT_FETCH_COMPLETE, &WindowMain::OnFetchComplete, this);
    }

private:
    wxPanel* panel;
    wxTextCtrl* textCtrl;
    wxButton* fetchButton;

    void OnFetchData(wxCommandEvent& event) {
        // Run the fetch operation in a separate thread
        std::thread(&WindowMain::FetchData, this).detach();
    }

    void FetchData() {
        std::string url = "https://jsonplaceholder.typicode.com/posts/1";
        cpr::Response r = cpr::Get(cpr::Url{url});

        wxThreadEvent evt(wxEVT_FETCH_COMPLETE);
        if (r.status_code == 200) {
            json jsonData = json::parse(r.text);
            std::string formattedData = "Title: " + jsonData["title"].get<std::string>() + "\n\n" +
                                        "Body: " + jsonData["body"].get<std::string>();
            evt.SetString(formattedData);
        } else {
            evt.SetString("Failed to fetch data. HTTP Status Code: " + std::to_string(r.status_code));
        }
        wxQueueEvent(this, evt.Clone());
    }

    void OnFetchComplete(wxThreadEvent& event) {
        textCtrl->SetValue(event.GetString());
    }
};

#pragma endregion

//================================================================
#pragma region Setup

class MyApp : public wxApp {
public:
    virtual bool OnInit() {
        WindowMain* w_main = new WindowMain();
        w_main->Show();
        return true;
    }
};

// Target that class
wxIMPLEMENT_APP(MyApp);

#pragma endregion
