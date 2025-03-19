#pragma once
#include "Panel.h"
#include "HttpFetcher.h"
#include "LocalDB.h"

class PanelStation : public Panel{
    public:
    PanelStation(Panel* origin, std::string stationId);
    ~PanelStation();

    //context
    std::string stationId;
    
    //funcs
    void FetchParams();
    HttpFetcher* httpFetcher = nullptr;
    void OnDataFetched(wxThreadEvent& event);

    //Text top
    wxStaticText* textTop;

    //List
    nlohmann::json data;
    wxListBox* listSensors;
    void ListSensors_OnItemDoubleClicked(wxCommandEvent& event);

    //Button Back
    wxButton* button_back;
    void ButtonBack_OnButtonClick(wxCommandEvent& event);
};