// main.cpp
#include "WindowMain.h"

wxWindow* mainWindow = nullptr;

class MyApp : public wxApp {
public:
    virtual bool OnInit() {
        WindowMain* w_main = new WindowMain();
        w_main->Show();
        return true;
    }
};

wxIMPLEMENT_APP(MyApp);