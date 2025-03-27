/**
 * @file WindowMain.h
 * @brief Defines the main application window class.
 */

 #pragma once
 #ifndef WINDOWMAIN_H
 #define WINDOWMAIN_H
 
 #include <wx/wx.h>
 #include "Panel.h"
 
 /**
  * @class WindowMain
  * @brief The main application window.
  * 
  * This class serves as the primary frame for the application, initializing 
  * the main panel and setting up the GUI layout.
  */
 class WindowMain : public wxFrame {
 public:
     /**
      * @brief Constructs the main application window.
      * 
      * Initializes the main frame and sets up the starting panel.
      */
     WindowMain();
 
     /// @name Main Panel
     /// @{
     Panel* panel_start; ///< Pointer to the initial panel displayed in the main window.
     /// @}
 };
 
 #endif // WINDOWMAIN_H
 