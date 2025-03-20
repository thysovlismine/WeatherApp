#pragma once
#include "Panel.h"
#include "HttpFetcher.h"
#include "LocalDB.h"

class PanelStation : public Panel{
    public:
    PanelStation(Panel* origin, std::string stationId, std::string stationName);
    ~PanelStation();

    //context
    std::string stationId;
    std::string stationName;
    
    //style config
    const int styleObjectSpacingX = 10;
    const int styleObjectSpacingY = 10;

    //funcs
    void FetchParams();
    HttpFetcher* httpFetcher = nullptr;
    void OnDataFetched(wxThreadEvent& event);
    void UpdateGUI();
    void OnWindowResized(wxSizeEvent& event);
    void OnWindowMaximized(wxMaximizeEvent& event);
    void OnFullScreen(wxFullScreenEvent& event);

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