#pragma once
#include "Panel.h"
#include "HttpFetcher.h"
#include "LocalDB.h"

class PanelStart : public Panel{
    public:
    PanelStart();
    ~PanelStart();

    //style config
    const int styleObjectSpacingX = 10;
    const int styleObjectSpacingY = 10;

    //funcs
    void FetchList();
    HttpFetcher* httpFetcher = nullptr;
    void OnDataFetched(wxThreadEvent& event);
    void UpdateGUI();
    void OnWindowResized(wxSizeEvent& event);
    void OnWindowMaximized(wxMaximizeEvent& event);
    void OnFullScreen(wxFullScreenEvent& event);

    //Text top
    wxStaticText* textTop = nullptr;
    
    //List
    nlohmann::json data;
    wxListBox* listStations;
    void ListStations_OnItemDoubleClicked(wxCommandEvent& event);

    //Button About
    wxButton* button_about = nullptr;
    void ButtonAbout_OnButtonClick(wxCommandEvent& event);
};