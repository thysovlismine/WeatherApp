/**
 * @file LocalDB.h
 * @brief Manages local storage and retrieval of JSON data for stations and sensors.
 */

 #pragma once
 #include <string>
 #include <nlohmann/json.hpp>
 #include <wx/string.h>
 #include <wx/wx.h>
 #include <vector>
 #include <fstream>
 
 /**
  * @class LocalDB
  * @brief Provides methods to update and load station and sensor data stored locally in JSON format.
  */
 class LocalDB {
 public:
     /**
      * @brief Updates the index file with new data.
      * @param data The new index data in JSON string format.
      */
     static void UpdateIndex(std::string data);
 
     /**
      * @brief Updates a specific station's data file.
      * @param stationId The unique identifier of the station.
      * @param data The new station data in JSON string format.
      */
     static void UpdateStation(std::string stationId, std::string data);
 
     /**
      * @brief Updates a specific sensor's data file.
      * @param sensorId The unique identifier of the sensor.
      * @param data The new sensor data in JSON string format.
      */
     static void UpdateSensor(std::string sensorId, std::string data);
 
     /**
      * @brief Loads the index data from the local JSON file.
      * @param data Reference to a JSON object where the index data will be stored.
      * @return True if the data is successfully loaded, false otherwise.
      */
     static bool LoadIndex(nlohmann::json& data);
 
     /**
      * @brief Loads a specific station's data from the local JSON file.
      * @param data Reference to a JSON object where the station data will be stored.
      * @param stationId The unique identifier of the station.
      * @return True if the data is successfully loaded, false otherwise.
      */
     static bool LoadStation(nlohmann::json& data, std::string stationId);
 
     /**
      * @brief Loads a specific sensor's data from the local JSON file.
      * @param data Reference to a JSON object where the sensor data will be stored.
      * @param sensorId The unique identifier of the sensor.
      * @return True if the data is successfully loaded, false otherwise.
      */
     static bool LoadSensor(nlohmann::json& data, std::string sensorId);
 };
 