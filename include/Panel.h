/**
 * @file Panel.h
 * @brief Defines the Panel class for managing wxWidgets panels.
 */

#pragma once
#include <wx/wx.h>


/**
 * @brief Pointer to the main application window.
 */
extern wxWindow* mainWindow;

/**
 * @brief Pointer to the main sizer for layout management.
 */
extern wxBoxSizer* mainSizer;


/**
 * @class Panel
 * @brief Represents a dynamic panel that can replace another panel in a wxWidgets application.
 */
class Panel{
    public:
    /**
    * @brief Pointer to the wxPanel instance managed by this class.
    */
    wxPanel* panel;
    
    /**
     * @brief Constructs a new Panel and hides the previous one if provided.
     * @param origin Pointer to the previous panel (can be nullptr for the main panel).
     */
    Panel(Panel* origin);   //hides the origin panel and displays only this panel
    
    
    /**
     * @brief Destructor that deletes the current panel and restores the previous one.
     */
    ~Panel();           //deletes this panel and uses the origin panel to be displayed back again.

    /**
     * @brief Sets the title of the main window.
     * @param title The new title to set.
     */
    void SetTitle(std::string title);
    
    private:
    Panel* _origin;         ///< Pointer to the previous panel.
    std::string _title;     ///< Stores the title of the panel.
};