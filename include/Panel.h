#include <wx/wx.h>

class Panel{
    public:
    wxPanel* panel;
    
    Panel(Panel* origin);   //hides the origin panel and displays only this panel
    ~Panel();           //deletes this panel and uses the origin panel to be displayed back again.

    private:
    Panel* _origin;
};