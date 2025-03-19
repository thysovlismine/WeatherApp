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
    const int startingValueCount = 24;

    //info bar

    //chart
    nlohmann::json data;
    wxLineChartCtrl* chart = nullptr;
    void UpdateChart();
    void UpdateChartSize();

    //chart info
    int chartValidCount;
    float chartSum;
    size_t chartMinIndex;
    size_t chartMaxIndex;

    //current chart info
    int chartLocalValidCount;
    float chartLocalSum;
    size_t chartLocalMinIndex;
    size_t chartLocalMaxIndex;

    //Button Back
    wxButton* button_back;
    void ButtonBack_OnButtonClick(wxCommandEvent& event);
};