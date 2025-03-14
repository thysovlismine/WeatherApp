#include "PanelStart.h"

PanelStart::PanelStart() : Panel(nullptr){
    
    //listbox
    listBox = new wxListBox(panel, wxID_ANY, wxPoint(10, 10), wxSize(250, 150));
    listBox->Append("Item 1");
    listBox->Append("Item 2");
    listBox->Append("Item 3");
    listBox->Append("Item 4");
    listBox->Disable();

    //Button About
    button_about = new wxButton(panel, wxID_ANY, "Click Me", wxPoint(100, 250), wxSize(100, 40));
    button_about->Bind(wxEVT_BUTTON, &PanelStart::ButtonAbout_OnButtonClick, this);
}

PanelStart::~PanelStart(){
    //destroy objects by pointers
    listBox->Destroy(); listBox = nullptr;
    button_about->Destroy(); button_about = nullptr;
}

void PanelStart::ButtonAbout_OnButtonClick(wxCommandEvent& event){
    //open panel about
    new PanelAbout(this);
    button_about->SetLabel("Clicked!");

}