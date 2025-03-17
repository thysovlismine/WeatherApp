#include "PanelStart.h"
#include "PanelStation.h"
#include "PanelAbout.h"
#include "JSONTools.h"

//================================================================

PanelStart::PanelStart() : Panel(nullptr), httpFetcher(nullptr){
    //Text top
    textTop = new wxStaticText(panel, wxID_ANY, "Wybierz Stacje Pomiarowa", wxPoint(10, 10));

    //List Stations
    listStations = new wxListBox(panel, wxID_ANY, wxPoint(10, 30), wxSize(400, 250));
    listStations->Bind(wxEVT_LISTBOX_DCLICK, &PanelStart::ListStations_OnItemDoubleClicked, this);

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
    //Destroy HttpFetcher
    if(httpFetcher != nullptr){
        httpFetcher->Destroy();
        httpFetcher = nullptr;
    }
}

//================================================================

void PanelStart::FetchList(){
    //block if already called
    if(httpFetcher != nullptr)
        return;

    //disalbe ListStations
    listStations->Disable();

    //fetch data
    httpFetcher = new HttpFetcher(panel, "https://api.gios.gov.pl/pjp-api/rest/station/findAll");
    httpFetcher->Fetch();
}

void PanelStart::OnDataFetched(wxThreadEvent& event){
    //unlock FetchList function
    httpFetcher = nullptr;

    //enable ListStations
    listStations->Enable();
    
    //get response
    std::string response = event.GetPayload<std::string>();
    
    //update DB
    LocalDB::UpdateIndex(response);

    //get data from the DB
    data = LocalDB::LoadIndex();
    //rest of the code should be reconfigured here

    //check error
    if(response.length() == 0){
        wxMessageBox("Failed to fetch data!", "Error", wxICON_ERROR | wxOK);
        return;
    }

    //parse json
    try{
        nlohmann::json responseJSON = nlohmann::json::parse(response);
        
        //add items
        stationIDs.Clear();
        listStations->Clear();
        for (const auto& item : responseJSON)
            if (
                item.contains("id")
                && item.contains("stationName")
            ){
                stationIDs.Add(item["id"].get<int>());
                listStations->Append(wxString::FromUTF8(item["stationName"].get<std::string>()));
            }
    }
    catch(const std::exception&){
        //log
        wxMessageBox("Failed to parse JSON!", "Error", wxICON_ERROR | wxOK);
    }
}

//================================================================

void PanelStart::ListStations_OnItemDoubleClicked(wxCommandEvent& event){
    int index = listStations->GetSelection();
    if (index != wxNOT_FOUND) {
        new PanelStation(this, stationIDs[index]);
    }
}

//================================================================

void PanelStart::ButtonAbout_OnButtonClick(wxCommandEvent& event){
    //open panel about
    //new PanelAbout(this);
    button_about->SetLabel("Clicked!");

}