#include "Panel.h"

Panel::Panel(Panel* origin){
    //assigns and hides a pervious panel
    _origin = origin;
    //hides a pervious panel (if this is not the main one)
    if(_origin != nullptr)
        _origin->panel->Hide();
    //create this panel and show it
    panel = new wxPanel(mainWindow);
    mainSizer->Add(panel, 1, wxEXPAND);
    panel->Show();
    mainWindow->Layout();  // Update layout
}

Panel::~Panel(){
    //since this object is being deleted, the object that rely on it should be too.
    
    //hide this panel and delete it
    mainSizer->Detach(panel);
    panel->Hide();
    panel->Destroy();
    panel = nullptr;
    
    //show the previous panel (if this is not the main one)
    if(_origin != nullptr)
        _origin->panel->Show();
    
    mainWindow->Layout();  // Update layout
}