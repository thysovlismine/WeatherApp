/**
 * @file PanelStation.h
 * @brief Defines the PanelStation class for displaying sensor data of a selected station.
 */

 #pragma once
 #include "Panel.h"
 #include "HttpFetcher.h"
 #include "LocalDB.h"
 
 /**
  * @class PanelStation
  * @brief Represents a panel that displays sensor information for a selected station.
  * 
  * This panel is opened when a user selects a station from the list in PanelStart.
  * It fetches sensor data from an API and displays it in a list, allowing further interactions.
  */
 class PanelStation : public Panel {
 public:
     /**
      * @brief Constructor for PanelStation.
      * 
      * Initializes the UI components and starts fetching sensor data for the given station.
      * 
      * @param origin Pointer to the parent panel.
      * @param stationId Unique identifier of the station.
      * @param stationName Display name of the station.
      */
     PanelStation(Panel* origin, std::string stationId, std::string stationName);
 
     /**
      * @brief Destructor for PanelStation.
      * 
      * Cleans up dynamically allocated resources and unbinds events.
      */
     ~PanelStation();
 
     /// @name Station Information
     /// @{
     std::string stationId;   ///< Unique ID of the selected station.
     std::string stationName; ///< Name of the selected station.
     /// @}
 
     /// @name UI Styling Configuration
     /// @{
     const int styleObjectSpacingX = 10; ///< Horizontal spacing between UI elements.
     const int styleObjectSpacingY = 10; ///< Vertical spacing between UI elements.
     /// @}
 
     /// @name Data Fetching
     /// @{
     /**
      * @brief Initiates fetching of sensor data for the selected station.
      * 
      * If a fetch operation is already in progress, this function does nothing.
      */
     void FetchParams();
 
     /**
      * @brief Event handler for processing fetched sensor data.
      * 
      * This method is triggered when an HTTP fetch operation is completed.
      * It updates the local database and refreshes the sensor list UI.
      * 
      * @param event The event containing the fetched data.
      */
     void OnDataFetched(wxThreadEvent& event);
     
     HttpFetcher* httpFetcher = nullptr; ///< Pointer to an HTTP fetcher instance.
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
     wxStaticText* textTop;    ///< Static text displaying the station selection message.
 
     nlohmann::json data;      ///< JSON object holding sensor data.
 
     wxListBox* listSensors;   ///< List box displaying available sensors.
 
     /**
      * @brief Handles double-click events on the sensor list.
      * Opens a new panel for the selected sensor.
      * 
      * @param event The list box double-click event.
      */
     void ListSensors_OnItemDoubleClicked(wxCommandEvent& event);
 
     wxButton* button_back;    ///< Button for navigating back to the previous panel.
 
     /**
      * @brief Handles click events on the "Back" button.
      * Closes the panel and returns to the previous screen.
      * 
      * @param event The button click event.
      */
     void ButtonBack_OnButtonClick(wxCommandEvent& event);
     /// @}
 };
 