#pragma once
#include "Panel.h"
#include "PanelAbout.h"

class PanelStart : public Panel{
    public:
    PanelStart();
    ~PanelStart();

    //Elements
    wxListBox* listBox;

    //Button About
    wxButton* button_about;
    void ButtonAbout_OnButtonClick(wxCommandEvent& event);
};