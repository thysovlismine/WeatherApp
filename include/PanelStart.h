/**
 * @file PanelStart.h
 * @brief Defines the PanelStart class for displaying and managing the station list UI.
 */

 #pragma once
 #include "Panel.h"
 #include "HttpFetcher.h"
 #include "LocalDB.h"
 
 /**
  * @class PanelStart
  * @brief Represents the main panel displaying a list of measurement stations.
  * 
  * This panel allows users to select a station from a list, fetches station data from an API,
  * and updates the local database accordingly.
  */
 class PanelStart : public Panel {
 public:
     /**
      * @brief Constructor for PanelStart.
      * Initializes the UI components and starts fetching station data.
      */
     PanelStart();
 
     /**
      * @brief Destructor for PanelStart.
      * Cleans up dynamically allocated resources and unbinds events.
      */
     ~PanelStart();
 
     /// @name UI Styling Configuration
     /// @{
     const int styleObjectSpacingX = 10;  ///< Horizontal spacing between UI elements.
     const int styleObjectSpacingY = 10;  ///< Vertical spacing between UI elements.
     /// @}
 
     /// @name Data Fetching
     /// @{
     /**
      * @brief Initiates fetching of the station list from the API.
      * 
      * If a fetch operation is already in progress, this function does nothing.
      */
     void FetchList();
 
     /**
      * @brief Event handler for processing fetched data.
      * 
      * This method is triggered when an HTTP fetch operation is completed.
      * It updates the local database and refreshes the station list UI.
      * 
      * @param event The event containing the fetched data.
      */
     void OnDataFetched(wxThreadEvent& event);
     
     HttpFetcher* httpFetcher = nullptr;  ///< Pointer to an HTTP fetcher instance.
     /// @}
 
     /// @name UI Updates
     /// @{
     /**
      * @brief Updates the graphical user interface.
      * Resizes UI elements based on the current window size.
      */
     void UpdateGUI();
 
     /**
      * @brief Handles window resize events.
      * 
      * @param event The window resize event.
      */
     void OnWindowResized(wxSizeEvent& event);
 
     /**
      * @brief Handles window maximization events.
      * 
      * @param event The window maximize event.
      */
     void OnWindowMaximized(wxMaximizeEvent& event);
 
     /**
      * @brief Handles full-screen events.
      * 
      * @param event The full-screen event.
      */
     void OnFullScreen(wxFullScreenEvent& event);
     /// @}
 
     /// @name UI Elements
     /// @{
     wxStaticText* textTop = nullptr;   ///< Static text displaying the title.
     
     nlohmann::json data;               ///< JSON object holding station data.
 
     wxListBox* listStations;           ///< List box displaying station names.
 
     /**
      * @brief Handles double-click events on the station list.
      * Opens a new panel for the selected station.
      * 
      * @param event The list box double-click event.
      */
     void ListStations_OnItemDoubleClicked(wxCommandEvent& event);
     
     wxButton* button_about = nullptr;  ///< Button for displaying information about the application.
 
     /**
      * @brief Handles click events on the "About" button.
      * 
      * @param event The button click event.
      */
     void ButtonAbout_OnButtonClick(wxCommandEvent& event);
     /// @}
 };
 