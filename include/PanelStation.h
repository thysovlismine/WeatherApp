#pragma once
#include "Panel.h"
#include "HttpFetcher.h"

class PanelStation : public Panel{
    public:
    PanelStation(Panel* origin, int stationId);
    ~PanelStation();

    //context
    int stationId;
    
    //funcs
    void FetchParams();
    HttpFetcher* httpFetcher = nullptr;
    void OnDataFetched(wxThreadEvent& event);

    //Text top
    wxStaticText* textTop;

    //List
    wxListBox* listSensors;
    wxArrayInt sensorIDs;   //database of sensor ids
    void ListSensors_OnItemDoubleClicked(wxCommandEvent& event);

    //Button Back
    wxButton* button_back;
    void ButtonBack_OnButtonClick(wxCommandEvent& event);
};