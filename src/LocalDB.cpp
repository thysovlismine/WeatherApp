#include "LocalDB.h"
#include "JSONTools.h"
#include <fstream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <sstream>

//ChatGPT
bool parseDateTime(const std::string& datetime, std::tm& tm) {
    std::istringstream ss(datetime);
    ss >> std::get_time(&tm, "%Y-%m-%d %H:%M:%S");
    return !ss.fail(); // Return false if parsing fails
}

//ChatGPT
void JSON_SortByDate(nlohmann::json& arr){
    //ChatGPT
    //Sort the remaining elements by date
    std::sort(arr.begin(), arr.end(),
        [](const nlohmann::json& a, const nlohmann::json& b) {
            std::tm tmA, tmB;
            parseDateTime(a["date"], tmA);
            parseDateTime(b["date"], tmB);
            return
                std::tie(tmA.tm_year, tmA.tm_mon, tmA.tm_mday, 
                tmA.tm_hour, tmA.tm_min, tmA.tm_sec)
                <
                std::tie(tmB.tm_year, tmB.tm_mon, tmB.tm_mday, 
                tmB.tm_hour, tmB.tm_min, tmB.tm_sec)
            ;
        }
    );
}

void UpdateGeneral(std::string data, std::string targetFile, std::string uniqueKeyName){
    //parse json
    nlohmann::json fetched;
    nlohmann::json present;
    
    //prepare jsons
    try{
        //parse fetched data
        fetched = nlohmann::json::parse(data);

        //make sure fetched contains unique entries
        JSON_Unique(fetched, uniqueKeyName);
        
        //check required param
        if(!fetched.is_array())
            return;

        //load file
        if(!JSON_FromFile(present, targetFile)){
            //just make an empty array
            //present = nlohmann::json::array();
            //or skip processing part and save fetched to index.json
            JSON_ToFile(fetched, targetFile);
            return;
        }
    }
    catch(const std::exception&){
        //error
        wxMessageBox("Error on UpdateGeneral!!!!");
        return;
    }

    //update present with fresh
    try{
        JSON_UpdateArray(present, fetched, uniqueKeyName);
    }
    catch(const std::exception&){
        //error
        wxMessageBox("Error on UpdateGeneral at processing part!!!!");
    }
    
    //save the updated json
    if(!JSON_ToFile(present, targetFile)){
        //error
        wxMessageBox("Error on UpdateGeneral at saving part!!!!");
    }
}

void LocalDB::UpdateIndex(std::string data){
    UpdateGeneral(data, "index.json", "id");
}

void LocalDB::UpdateStation(std::string stationId, std::string data){
    UpdateGeneral(data, "station_" + stationId + ".json", "id");
}

void LocalDB::UpdateSensor(std::string sensorId, std::string data){
    //target file
    std::string targetFile = "sensor_" + sensorId + ".json";
    
    //parse json
    nlohmann::json fetched;
    nlohmann::json present;
    
    //prepare jsons
    try{
        //parse fetched data
        fetched = nlohmann::json::parse(data);
        
        //check required parm
        if(!fetched.contains("values"))
            return;
        if(!fetched["values"].is_array())
            return;

        //make sure fetched contains unique entries
        JSON_Unique(fetched["values"], "date");

        //ChatGPT
        //Remove elements with invalid dates
        fetched["values"].erase(std::remove_if(fetched["values"].begin(), fetched["values"].end(),
            [](const nlohmann::json& item) {
                std::tm tm;
                return !parseDateTime(item.value("date", ""), tm); // Remove if parsing fails
            }), fetched["values"].end());
        
        //load file
        if(!JSON_FromFile(present, targetFile)){
            //sort fetched
            JSON_SortByDate(fetched["values"]);

            //save fetched to the target file
            JSON_ToFile(fetched, targetFile);
            return;
        }
    }
    catch(const std::exception&){
        //error
        wxMessageBox("Error on UpdateGeneral!!!!");
        return;
    }
    
    //update present with fresh
    JSON_UpdateArray(present["values"], fetched["values"], "date");

    //sort present
    JSON_SortByDate(present["values"]);

    //save the updated json
    if(!JSON_ToFile(present, targetFile)){
        //error
        wxMessageBox("Error on UpdateSensor at saving part!!!!");
    }
}


bool LocalDB::LoadIndex(nlohmann::json& data){
    return JSON_FromFile(data, "index.json");
}

bool LocalDB::LoadStation(nlohmann::json& data, std::string stationId){
    return JSON_FromFile(data, "station_" + stationId + ".json");
}

bool LocalDB::LoadSensor(nlohmann::json& data, std::string sensorId){
    return JSON_FromFile(data, "sensor_" + sensorId + ".json");
}
