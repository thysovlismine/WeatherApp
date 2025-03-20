#include "PanelStation.h"
#include "PanelSensor.h"
#include "JSONTools.h"

//================================================================

PanelStation::PanelStation(Panel* origin, std::string _stationId, std::string _stationName) : Panel(origin){
    //context
    stationId = _stationId;
    stationName = _stationName;

    //window
    SetTitle("Stacja: " + _stationName);
    
    //Button Back
    button_back = new wxButton(panel, wxID_ANY, "<--", wxPoint(styleObjectSpacingX, styleObjectSpacingY), wxSize(100, 40));
    button_back->Bind(wxEVT_BUTTON, &PanelStation::ButtonBack_OnButtonClick, this);
    
    //Text top
    textTop = new wxStaticText(panel, wxID_ANY, "Wybierz Stacje Pomiarowa", wxPoint(styleObjectSpacingX, button_back->GetPosition().y + button_back->GetSize().GetHeight() + styleObjectSpacingY));

    //List Sensors
    listSensors = new wxListBox(panel, wxID_ANY, wxPoint(styleObjectSpacingX, textTop->GetPosition().y + textTop->GetSize().GetHeight() + styleObjectSpacingY), wxSize(400, 250));
    listSensors->Bind(wxEVT_LISTBOX_DCLICK, &PanelStation::ListSensors_OnItemDoubleClicked, this);

    

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
        std::string name = JSON_ParseString(data[index]["param"], "paramName") + " (" + stationName + ")";
        new PanelSensor(this, id, name);
    }
}

//================================================================

void PanelStation::ButtonBack_OnButtonClick(wxCommandEvent& event){
    //simply go back
    delete this;
}