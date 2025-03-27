/**
 * @file PanelSensor.h
 * @brief Defines the PanelSensor class for displaying sensor data charts.
 */

 #pragma once
 #include "Panel.h"
 #include "HttpFetcher.h"
 #include "LocalDB.h"
 #include <wx/app.h>
 #include <wx/charts/wxcharts.h>
 #include <wx/slider.h>
 #include <wx/richtext/richtextctrl.h>
 
 /**
  * @class PanelSensor
  * @brief Represents a panel that displays a chart with sensor data over time.
  * 
  * This panel is opened when a user selects a sensor from the PanelStation list.
  * It fetches historical data, presents it in a chart, and provides statistical analysis.
  */
 class PanelSensor : public Panel {
 public:
     /**
      * @brief Constructor for PanelSensor.
      * 
      * Initializes UI components and starts fetching sensor data.
      * 
      * @param origin Pointer to the parent panel.
      * @param sensorId Unique identifier of the sensor.
      * @param chartName Display name of the chart.
      */
     PanelSensor(Panel* origin, std::string sensorId, std::string chartName);
 
     /**
      * @brief Destructor for PanelSensor.
      * 
      * Cleans up dynamically allocated resources and unbinds events.
      */
     ~PanelSensor();
 
     /// @name Sensor Information
     /// @{
     std::string sensorId;   ///< Unique ID of the selected sensor.
     std::string chartName;  ///< Name displayed on the chart.
     /// @}
 
     /// @name UI Styling Configuration
     /// @{
     const int styleObjectSpacingX = 10; ///< Horizontal spacing between UI elements.
     const int styleObjectSpacingY = 10; ///< Vertical spacing between UI elements.
     /// @}
 
     /// @name Data Fetching
     /// @{
     /**
      * @brief Initiates fetching of sensor data.
      * 
      * If a fetch operation is already in progress, this function does nothing.
      */
     void FetchData();
 
     /**
      * @brief Event handler for processing fetched sensor data.
      * 
      * This method is triggered when an HTTP fetch operation is completed.
      * It updates the local database and refreshes the chart.
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
     wxStaticText* textTop;    ///< Static text displaying the sensor selection message.
 
     /// @name Slider Control
     /// @{
     wxSlider* slider;         ///< Slider for adjusting displayed data range.
     void OnSliderChanged(wxCommandEvent& event); ///< Handles slider change events.
 
     const int sliderMinValue = 0;       ///< Minimum value of the slider.
     const int sliderMaxValue = 1000;    ///< Maximum value of the slider.
     const int startingValueCount = 24;  ///< Default number of data points displayed.
     /// @}
 
     /// @name Summary Information
     /// @{
     wxRichTextCtrl* summery1; ///< Rich text box displaying summary statistics.
     wxRichTextCtrl* summery2; ///< Rich text box displaying transformed statistics.
 
     /**
      * @brief Updates the text in the summary box.
      */
     void UpdateSummery1Text();
 
     /**
      * @brief Applies transformations and updates the second summary box.
      */
     void UpdateSummeryTransofrm();
     /// @}
 
     /// @name Chart and Data
     /// @{
     nlohmann::json data;      ///< JSON object holding sensor data.
 
     wxLineChartCtrl* chart = nullptr; ///< Pointer to the line chart control.
 
     /**
      * @brief Updates the chart with the latest data.
      */
     void UpdateChart();
 
     /**
      * @brief Adjusts the chart size based on the window size.
      */
     void UpdateChartSize();
     /// @}
 
     /// @name Chart Statistics
     /// @{
     int chartValidCount;                  ///< Total number of valid data points.
     float chartSum;                        ///< Sum of all data points.
     size_t chartMinIndex = 0;              ///< Index of the minimum value in the dataset.
     size_t chartMaxIndex = 0;              ///< Index of the maximum value in the dataset.
     float chartStandardDeviationSum;       ///< Sum of squared deviations for standard deviation calculation.
 
     int chartLocalValidCount;              ///< Number of valid points in the currently viewed range.
     float chartLocalSum;                   ///< Sum of data points in the viewed range.
     size_t chartLocalMinIndex = 0;         ///< Index of the minimum value in the viewed range.
     size_t chartLocalMaxIndex = 0;         ///< Index of the maximum value in the viewed range.
     float chartLocalStandardDeviationSum;  ///< Sum of squared deviations for local standard deviation calculation.
     /// @}
 
     /// @name Navigation
     /// @{
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
 