#pragma once
#include <wx/wx.h>
#include <string>

class LocalDB{
    public:

    //JSON Updating here
    virtual void UpdateIndex(std::string text);
    virtual void UpdateStation(int stationId, std::string text);
    virtual void UpdateSensor(int sensorId, std::string text);


    

    private:

};