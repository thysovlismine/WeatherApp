#include "PanelAbout.h"

PanelAbout::PanelAbout(Panel* origin, wxString text) : Panel(origin){
    

    //Button Back
    button_back = new wxButton(panel, wxID_ANY, text, wxPoint(50, 50), wxSize(100, 40));
    button_back->Bind(wxEVT_BUTTON, &PanelAbout::ButtonBack_OnButtonClick, this);
}

PanelAbout::~PanelAbout(){
    //destroy objects by pointers
    button_back->Destroy(); button_back = nullptr;
}

void PanelAbout::ButtonBack_OnButtonClick(wxCommandEvent& event){
    //open panel about
    //button_back->SetLabel("Clicked!");

    //simply go back
    delete this;
}