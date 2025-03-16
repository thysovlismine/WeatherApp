#pragma once
#include "Panel.h"
#include "HttpFetcher.h"
#include <nlohmann/json.hpp>
#include <wx/app.h>
#include <wx/charts/wxcharts.h>

class PanelSensor : public Panel{
    public:
    PanelSensor(Panel* origin, int sensorId);
    ~PanelSensor();

    //context
    int sensorId;
    
    //funcs
    void FetchData();
    HttpFetcher* httpFetcher = nullptr;
    void OnDataFetched(wxThreadEvent& event);

    //Text top
    wxStaticText* textTop;

    //List
    wxListBox* list;

    //Button Back
    wxButton* button_back;
    void ButtonBack_OnButtonClick(wxCommandEvent& event);
};