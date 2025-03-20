#include "PanelStation.h"
#include "PanelSensor.h"
#include "JSONTools.h"

//================================================================

PanelStation::PanelStation(Panel* origin, std::string _stationId) : Panel(origin){
    //context
    stationId = _stationId;

    //window
    SetTitle("Stacja " + stationId);

    //Text top
    textTop = new wxStaticText(panel, wxID_ANY, "Wybierz Stacje Pomiarowa", wxPoint(10, 10));

    //List Sensors
    listSensors = new wxListBox(panel, wxID_ANY, wxPoint(10, 30), wxSize(400, 250));
    listSensors->Bind(wxEVT_LISTBOX_DCLICK, &PanelStation::ListSensors_OnItemDoubleClicked, this);

    //Button Back
    button_back = new wxButton(panel, wxID_ANY, "<--", wxPoint(10, 300), wxSize(100, 40));
    button_back->Bind(wxEVT_BUTTON, &PanelStation::ButtonBack_OnButtonClick, this);

    //fetch info
    FetchParams();
    panel->Bind(EVT_HTTP_FETCH_COMPLETE, &PanelStation::OnDataFetched, this);
}

PanelStation::~PanelStation(){
    //destroy objects by pointers
    textTop->Destroy(); textTop = nullptr;
    listSensors->Destroy(); listSensors = nullptr;
    button_back->Destroy(); button_back = nullptr;
    //Destroy HttpFetcher
    if(httpFetcher != nullptr){
        httpFetcher->Destroy();
        httpFetcher = nullptr;
    }
}

//================================================================

void PanelStation::FetchParams(){
    //block if already called
    if(httpFetcher != nullptr)
        return;
    
    //disalbe ListStations
    listSensors->Disable();

    //fetch data
    httpFetcher = new HttpFetcher(panel, "https://api.gios.gov.pl/pjp-api/rest/station/sensors/" + stationId);
    httpFetcher->Fetch();
}

void PanelStation::OnDataFetched(wxThreadEvent& event){
    //unlock FetchParams function
    httpFetcher = nullptr;

    //enable ListSensors
    listSensors->Enable();

    //get response
    std::string response = event.GetPayload<std::string>();

    //check error
    if(response.length() == 0){
        wxMessageBox("Failed to fetch data!", "Error", wxICON_ERROR | wxOK);
        return;
    }
    else{
        //update DB
        LocalDB::UpdateStation(stationId, response);
    }

    //clear list
    listSensors->Clear();

    //get data from the DB
    if(LocalDB::LoadStation(data, stationId)){
        size_t count = data.size();
        std::string name;

        //add items
        for(size_t i = 0; i < count; i++){
            //get name
            name = JSON_ParseString(data[i]["param"], "paramName");
            //correct weird name
            if(name.length() <= 0)
                name = "Untitled (" + JSON_ParseAsString(data[i], "id") + ")";
            //add name
            listSensors->Append(wxString::FromUTF8(name));
        }
    }
    else{
        //Load failed

    }
}

//================================================================

void PanelStation::ListSensors_OnItemDoubleClicked(wxCommandEvent& event){
    int index = listSensors->GetSelection();
    if (index != wxNOT_FOUND) {
        std::string id = JSON_ParseAsString(data[index], "id");
        new PanelSensor(this, id);
    }
}

//================================================================

void PanelStation::ButtonBack_OnButtonClick(wxCommandEvent& event){
    //simply go back
    delete this;
}