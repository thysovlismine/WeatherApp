#pragma once
#include "Panel.h"
#include "HttpFetcher.h"
#include "LocalDB.h"
#include <wx/app.h>
#include <wx/charts/wxcharts.h>
#include <wx/slider.h>
#include <wx/richtext/richtextctrl.h>


class PanelSensor : public Panel{
    public:
    PanelSensor(Panel* origin, std::string sensorId, std::string chartName);
    ~PanelSensor();

    //context
    std::string sensorId;
    std::string chartName;
    
    //style config
    const int styleObjectSpacingX = 10;
    const int styleObjectSpacingY = 10;

    //funcs
    void FetchData();
    HttpFetcher* httpFetcher = nullptr;
    void OnDataFetched(wxThreadEvent& event);
    void UpdateGUI();
    void OnWindowResized(wxSizeEvent& event);
    void OnWindowMaximized(wxMaximizeEvent& event);
    void OnFullScreen(wxFullScreenEvent& event);

    //Text top
    wxStaticText* textTop;

    //slider
    wxSlider* slider;
    void OnSliderChanged(wxCommandEvent& event);
    const int sliderMinValue = 0;
    const int sliderMaxValue = 1000;
    const int startingValueCount = 24;

    //info stats
    wxRichTextCtrl* summery1;
    wxRichTextCtrl* summery2;
    void UpdateSummery1Text();
    void UpdateSummeryTransofrm();

    //chart
    nlohmann::json data;
    wxLineChartCtrl* chart = nullptr;
    void UpdateChart();
    void UpdateChartSize();

    //chart info
    int chartValidCount;
    float chartSum;
    size_t chartMinIndex = 0;
    size_t chartMaxIndex = 0;
    float chartStandardDeviationSum;

    //current chart info
    int chartLocalValidCount;
    float chartLocalSum;
    size_t chartLocalMinIndex = 0;
    size_t chartLocalMaxIndex = 0;
    float chartLocalStandardDeviationSum;

    //Button Back
    wxButton* button_back;
    void ButtonBack_OnButtonClick(wxCommandEvent& event);
};