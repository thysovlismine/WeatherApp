#include <wx/wx.h>
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

// Main Frame
class MyFrame : public wxFrame {
public:
    MyFrame() : wxFrame(nullptr, wxID_ANY, "REST API Data Fetcher 2", wxDefaultPosition, wxSize(600, 400)) {
        panel = new wxPanel(this);
        textCtrl = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(10, 10), wxSize(560, 300), wxTE_MULTILINE | wxTE_READONLY);
        fetchButton = new wxButton(panel, wxID_ANY, "Fetch Data", wxPoint(10, 320), wxSize(100, 30));

        // Event binding
        fetchButton->Bind(wxEVT_BUTTON, &MyFrame::OnFetchData, this);
    }

private:
    wxPanel* panel;
    wxTextCtrl* textCtrl;
    wxButton* fetchButton;

    void OnFetchData(wxCommandEvent& event) {
        std::string url = "https://jsonplaceholder.typicode.com/posts/1";
        cpr::Response r = cpr::Get(cpr::Url{url});

        if (r.status_code == 200) {
            json jsonData = json::parse(r.text);
            std::string formattedData = "Title: " + jsonData["title"].get<std::string>() + "\n\n" +
                                        "Body: " + jsonData["body"].get<std::string>();
            textCtrl->SetValue(formattedData);
        } else {
            textCtrl->SetValue("Failed to fetch data. HTTP Status Code: " + std::to_string(r.status_code));
        }
    }
};

// wxWidgets Application
class MyApp : public wxApp {
public:
    virtual bool OnInit() {
        MyFrame* frame = new MyFrame();
        frame->Show();
        return true;
    }
};

// wxWidgets Entry Point
wxIMPLEMENT_APP(MyApp);
