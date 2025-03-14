#include "Panel.h"

Panel::Panel(Panel* origin){
    //assigns and hides a pervious panel
    _origin = origin;
    //hides a pervious panel (if this is not the main one)
    if(_origin != nullptr)
        _origin->panel->Hide();
    //create this panel
    panel = new wxPanel(mainWindow);
}

Panel::~Panel(){
    //since this object is being deleted, the object that rely on it should be too.
    
    //hide this panel and delete it
    panel->Hide();
    delete panel;
    
    //show the previous panel (if this is not the main one)
    if(_origin != nullptr) 
        _origin->panel->Show();

}