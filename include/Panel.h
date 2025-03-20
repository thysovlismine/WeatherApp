#pragma once
#include <wx/wx.h>

extern wxWindow* mainWindow;
extern wxBoxSizer* mainSizer;

class Panel{
    public:
    wxPanel* panel;
    
    Panel(Panel* origin);   //hides the origin panel and displays only this panel
    ~Panel();           //deletes this panel and uses the origin panel to be displayed back again.

    void Panel::SetTitle(std::string title);
    
    private:
    Panel* _origin;
    std::string _title;
};