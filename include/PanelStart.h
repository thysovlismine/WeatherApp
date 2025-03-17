#pragma once
#include "Panel.h"
#include "HttpFetcher.h"

class PanelStart : public Panel{
    public:
    PanelStart();
    ~PanelStart();

    //funcs
    void FetchList();
    HttpFetcher* httpFetcher = nullptr;
    void OnDataFetched(wxThreadEvent& event);

    //Text top
    wxStaticText* textTop;
    
    //List
    wxListBox* listStations;
    wxArrayInt stationIDs;  //database of station ids
    void ListStations_OnItemDoubleClicked(wxCommandEvent& event);

    //Button About
    wxButton* button_about;
    void ButtonAbout_OnButtonClick(wxCommandEvent& event);
};