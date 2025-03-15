#include "PanelStart.h"
#include "HttpFetcher.h"

PanelStart::PanelStart() : Panel(nullptr){
    
    //Text top
    textTop = new wxStaticText(panel, wxID_ANY, "Wybierz Stacje Pomiarowa", wxPoint(10, 10));

    //List Stations
    listStations = new wxListBox(panel, wxID_ANY, wxPoint(10, 30), wxSize(400, 250));
    listStations->Bind(wxEVT_LISTBOX_DCLICK, &PanelStart::ListStations_OnItemDoubleClicked, this);
    listStations->Append("Item 1");
    listStations->Append("Item 2");
    listStations->Append("Item 3");
    listStations->Append("Item 4");
    //listStations->Disable();

    //Button About
    //button_about = new wxButton(panel, wxID_ANY, "Click Me", wxPoint(100, 250), wxSize(100, 40));
    //button_about->Bind(wxEVT_BUTTON, &PanelStart::ButtonAbout_OnButtonClick, this);

    //Load and Update data
    FetchList();
    panel->Bind(EVT_HTTP_FETCH_COMPLETE, &PanelStart::OnDataFetched, this);
}

PanelStart::~PanelStart(){
    //destroy objects by pointers
    textTop->Destroy(); textTop = nullptr;
    listStations->Destroy(); listStations = nullptr;
    button_about->Destroy(); button_about = nullptr;
}


void PanelStart::FetchList(){
    //disalbe ListStations
    listStations->Disable();

    //fetch data
    HttpFetcher* fetcher = new HttpFetcher(panel, "https://jsonplaceholder.typicode.com/posts");
    fetcher->Fetch();
}

void PanelStart::OnDataFetched(wxThreadEvent& event){
    wxString jsonString = event.GetPayload<wxString>();

    if (jsonString.IsEmpty()) {
        wxMessageBox("Failed to fetch data!", "Error", wxICON_ERROR | wxOK);
        //enable ListStations
        listStations->Enable();
        return;
    }

    // Parse JSON using nlohmann::json
    wxArrayString titles;
    try {
        nlohmann::json jsonResponse = nlohmann::json::parse(jsonString.ToStdString());

        for (const auto& item : jsonResponse) {
            if (item.contains("title")) {
                titles.Add(wxString::FromUTF8(item["title"].get<std::string>()));
            }
        }
    } catch (const std::exception&) {
        wxMessageBox("Failed to parse JSON!", "Error", wxICON_ERROR | wxOK);
        //enable ListStations
        listStations->Enable();
        return;
    }

    listStations->Clear();
    listStations->InsertItems(titles, 0);

    //enable ListStations
    listStations->Enable();
}

void PanelStart::ListStations_OnItemDoubleClicked(wxCommandEvent& event){
    int sel = listStations->GetSelection();
    if (sel != wxNOT_FOUND) {
        listStations->SetString(sel, "Double Clicked!");
    }
}


void PanelStart::ButtonAbout_OnButtonClick(wxCommandEvent& event){
    //open panel about
    new PanelAbout(this);
    button_about->SetLabel("Clicked!");

}