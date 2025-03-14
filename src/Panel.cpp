#include "Panel.h"

Panel::Panel(Panel* origin){
    //assigns and hides a pervious panel
    _origin = origin;
    _origin->panel->Hide();
}

Panel::~Panel(){
    //since this object is being deleted, the object that rely on it should be too.
    //show the previous panel
    _origin->panel->Show();
}