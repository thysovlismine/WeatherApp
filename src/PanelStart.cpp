#include "PanelStart.h"

PanelStart::PanelStart() : Panel(nullptr){
    
    //listbox
    listBox = new wxListBox(panel, wxID_ANY, wxPoint(10, 10), wxSize(250, 150));
    listBox->Append("Item 1");
    listBox->Append("Item 2");
    listBox->Append("Item 3");
    listBox->Append("Item 4");
    listBox->Disable();
}