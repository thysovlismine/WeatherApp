#include "PanelStation.h"
#include "HttpFetcher.h"

//================================================================

PanelStation::PanelStation(Panel* origin, int stationId) : Panel(origin){
    

    //Button Back
    button_back = new wxButton(panel, wxID_ANY, "Powrot", wxPoint(50, 50), wxSize(100, 40));
    button_back->Bind(wxEVT_BUTTON, &PanelStation::ButtonBack_OnButtonClick, this);
}

PanelStation::~PanelStation(){
    //destroy objects by pointers
    button_back->Destroy(); button_back = nullptr;
}

//================================================================

void PanelStation::ButtonBack_OnButtonClick(wxCommandEvent& event){
    //simply go back
    delete this;
}