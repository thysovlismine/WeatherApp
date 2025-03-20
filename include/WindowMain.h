// WindowMain.h
#pragma once
#ifndef WINDOWMAIN_H
#define WINDOWMAIN_H

#include <wx/wx.h>
#include "Panel.h"

class WindowMain : public wxFrame {
    public:
    WindowMain();

    //main panel
    Panel* panel_start;
    
};

#endif // WINDOWMAIN_H
