#pragma once
#include <string>
#include <nlohmann/json.hpp>
#include <wx/string.h>
#include <wx/wx.h>


//fetching more specific data about the station or sensor is a part of a additional info functions (they don't play a key in processing the data)

struct StationIndexInfo{
    int id;
    wxString name;
};

struct SensorIndexInfo{
    int id;
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
    static void UpdateStation(int stationId, std::string data);
    static void UpdateSensor(int sensorId, std::string data);

    //Data loading
    static StationIndexInfo* LoadIndex();
    static SensorIndexInfo* LoadStation(int stationId);
    static SensorDataset* LoadSensor(int sensorId);

    

    private:

};



