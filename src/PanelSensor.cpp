#include "PanelSensor.h"

//================================================================

PanelSensor::PanelSensor(Panel* origin, int _sensorId) : Panel(origin){
    //context
    sensorId = _sensorId;

    //List Sensors
    list = new wxListBox(panel, wxID_ANY, wxPoint(10, 30), wxSize(400, 250));
    
    //Button Back
    button_back = new wxButton(panel, wxID_ANY, "<--", wxPoint(10, 300), wxSize(100, 40));
    button_back->Bind(wxEVT_BUTTON, &PanelSensor::ButtonBack_OnButtonClick, this);

    //fetch data
    panel->Bind(EVT_HTTP_FETCH_COMPLETE, &PanelSensor::OnDataFetched, this);
    FetchData();
}

PanelSensor::~PanelSensor(){
    //destroy objects by pointers
    list->Destroy(); list = nullptr;
    button_back->Destroy(); button_back = nullptr;
    //Destroy HttpFetcher
    if(httpFetcher != nullptr){
        httpFetcher->Destroy();
        httpFetcher = nullptr;
    }
}

//================================================================

void PanelSensor::FetchData(){
    //block if already called
    if(httpFetcher != nullptr)
        return;

    //fetch data
    httpFetcher = new HttpFetcher(panel, "https://api.gios.gov.pl/pjp-api/rest/data/getData/" + std::to_string(sensorId));
    httpFetcher->Fetch();
}

void PanelSensor::OnDataFetched(wxThreadEvent& event){
    //unlock FetchParams function
    httpFetcher = nullptr;

    //get response
    std::string response = event.GetPayload<std::string>();

    //parse json
    try{
        nlohmann::json responseJSON = nlohmann::json::parse(response);
        
        //add items
        list->Clear();
        if(responseJSON.contains("values"))
            for (const auto& item : responseJSON["values"])
                if (item.contains("date")
                    && item.contains("value")
                ){
                    list->Append(wxString::FromUTF8( std::to_string((item["value"]).get<float>()) ));
                }
                else{
                    list->Append("gag");
                }
    }
    catch(const std::exception&){
        ;
    }
}

//================================================================

void PanelSensor::ButtonBack_OnButtonClick(wxCommandEvent& event){
    //simply go back
    delete this;
}