#pragma once
#include <string>
#include <nlohmann/json.hpp>
#include <wx/string.h>
#include <wx/wx.h>
#include <vector>
#include <fstream>


//fetching more specific data about the station or sensor is a part of a additional info functions (they don't play a key in processing the data)

class LocalDB{
    public:

    //JSON Updating here
    static void UpdateIndex(std::string data);
    static void UpdateStation(std::string stationId, std::string data);
    static void UpdateSensor(std::string sensorId, std::string data);
    
    //Data loading JSON
    static bool LoadIndex(nlohmann::json& data);
    static bool LoadStation(nlohmann::json& data, std::string stationId);
    static bool LoadSensor(nlohmann::json& data, std::string sensorId);

};



