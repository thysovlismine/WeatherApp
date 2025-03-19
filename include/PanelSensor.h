#pragma once
#include "Panel.h"
#include "HttpFetcher.h"
#include "LocalDB.h"
#include <wx/app.h>
#include <wx/charts/wxcharts.h>
#include <wx/slider.h>


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
    void OnWindowResized(wxSizeEvent& event);

    //Text top
    wxStaticText* textTop;

    //slider
    wxSlider* slider;
    void OnSliderChanged(wxCommandEvent& event);
    const int sliderMinValue = 0;
    const int sliderMaxValue = 1000;

    //chart
    nlohmann::json data;
    wxLineChartCtrl* chart = nullptr;
    size_t chartLastStartIndex = 0;
    void UpdateChart();
    void UpdateChartSize();

    //Button Back
    wxButton* button_back;
    void ButtonBack_OnButtonClick(wxCommandEvent& event);
};