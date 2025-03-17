#pragma once
#include "Panel.h"
#include "HttpFetcher.h"
#include "LocalDB.h"

class PanelStart : public Panel{
    public:
    PanelStart();
    ~PanelStart();

    //funcs
    void FetchList();
    HttpFetcher* httpFetcher = nullptr;
    void OnDataFetched(wxThreadEvent& event);

    //Text top
    wxStaticText* textTop = nullptr;
    
    //List
    std::vector<StationIndexInfo> data;
    wxListBox* listStations;
    void ListStations_OnItemDoubleClicked(wxCommandEvent& event);

    //Button About
    wxButton* button_about = nullptr;
    void ButtonAbout_OnButtonClick(wxCommandEvent& event);
};