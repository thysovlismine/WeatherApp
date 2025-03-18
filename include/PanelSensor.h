#pragma once
#include "Panel.h"
#include "HttpFetcher.h"
#include "LocalDB.h"
#include <wx/app.h>
#include <wx/charts/wxcharts.h>

class PanelSensor : public Panel{
    public:
    PanelSensor(Panel* origin, std::string sensorId);
    ~PanelSensor();

    //context
    std::string sensorId;
    
    //funcs
    void FetchData();
    HttpFetcher* httpFetcher = nullptr;
    void OnDataFetched(wxThreadEvent& event);

    //Text top
    wxStaticText* textTop;

    //chart
    std::vector<SensorData> data;
    wxLineChartCtrl* chart = nullptr;

    //List
    wxListBox* list;

    //Button Back
    wxButton* button_back;
    void ButtonBack_OnButtonClick(wxCommandEvent& event);
};