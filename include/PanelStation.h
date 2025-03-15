#pragma once
#include "Panel.h"
#include "HttpFetcher.h"
#include <nlohmann/json.hpp>

class PanelStation : public Panel{
    public:
    PanelStation(Panel* origin, int stationId);
    ~PanelStation();

    //Button Back
    wxButton* button_back;
    void ButtonBack_OnButtonClick(wxCommandEvent& event);
};