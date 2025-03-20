#include "PanelStart.h"
#include "PanelStation.h"
#include "PanelAbout.h"
#include "JSONTools.h"

//================================================================

PanelStart::PanelStart() : Panel(nullptr), httpFetcher(nullptr){
    //window
    SetTitle("Lista Stacji");

    //Text top
    textTop = new wxStaticText(panel, wxID_ANY, "Wybierz Stacje Pomiarowa", wxPoint(10, 10));

    //List Stations
    listStations = new wxListBox(panel, wxID_ANY, wxPoint(10, 30), wxSize(400, 250));
    listStations->Bind(wxEVT_LISTBOX_DCLICK, &PanelStart::ListStations_OnItemDoubleClicked, this);

    //Button About
    //button_about = new wxButton(panel, wxID_ANY, "Click Me", wxPoint(100, 250), wxSize(100, 40));
    //button_about->Bind(wxEVT_BUTTON, &PanelStart::ButtonAbout_OnButtonClick, this);

    //Load and Update data
    panel->Bind(EVT_HTTP_FETCH_COMPLETE, &PanelStart::OnDataFetched, this);
    FetchList();
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

    //clear list
    listStations->Clear();

    //get data from the DB
    if(LocalDB::LoadIndex(data)){
        //process json
        size_t count = data.size();
        std::string name;
        //add items
        for(size_t i = 0; i < count; i++){
            //get name
            name = JSON_ParseString(data[i], "stationName");
            //correct weird name
            if(name.length() <= 0)
                name = "Untitled (" + JSON_ParseAsString(data[i], "id") + ")";
            //add
            listStations->Append(wxString::FromUTF8(name));
        }
    }
    else{
        //Load failed

    }
}

//================================================================

void PanelStart::ListStations_OnItemDoubleClicked(wxCommandEvent& event){
    int index = listStations->GetSelection();
    if (index != wxNOT_FOUND) {
        std::string id = JSON_ParseAsString(data[index], "id");
        std::string name = JSON_ParseString(data[index], "stationName");
        new PanelStation(this, id, name);
    }
}

//================================================================

void PanelStart::ButtonAbout_OnButtonClick(wxCommandEvent& event){
    //open panel about
    //new PanelAbout(this);
    button_about->SetLabel("Clicked!");

}