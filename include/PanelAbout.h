#pragma once
#include "Panel.h"

class PanelAbout : public Panel{
    public:
    PanelAbout(Panel* origin, wxString text);
    ~PanelAbout();

    //Button Back
    wxButton* button_back;
    void ButtonBack_OnButtonClick(wxCommandEvent& event);
};