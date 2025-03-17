#pragma once
#include <string>
#include <nlohmann/json.hpp>
#include <wx/string.h>
#include <wx/wx.h>
#include <vector>


//fetching more specific data about the station or sensor is a part of a additional info functions (they don't play a key in processing the data)

struct StationIndexInfo{
    std::string id;
    std::string name;
};

struct SensorIndexInfo{
    std::string id;
    wxString name;
};

struct SensorData{
    float value;
    wxString date;
};

class SensorDataset{
    public:
    SensorData* data;
    SensorDataset();
    ~SensorDataset();
};


class LocalDB{
    public:

    //JSON Updating here
    static void UpdateIndex(std::string data);
    static void UpdateStation(std::string stationId, std::string data);
    static void UpdateSensor(std::string sensorId, std::string data);

    //Data loading
    static std::vector<StationIndexInfo> LoadIndex();
    static std::vector<SensorIndexInfo> LoadStation(std::string stationId);
    static std::vector<SensorDataset> LoadSensor(std::string sensorId);

    

};



