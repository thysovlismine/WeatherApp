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
        std::ifstream inFile(targetFile);
        if(inFile){
            //parse json
            inFile >> present;  // Deserialize JSON data
            inFile.close();
        }
        else{
            //just make an empty array
            //present = nlohmann::json::array();
            //or skip processing part and save fetched to index.json
            std::ofstream outFile(targetFile);
            outFile << fetched.dump(4);
            outFile.close();
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
    try{
        //save present to file
        std::ofstream outFile(targetFile);
        outFile << present.dump(4);
        outFile.close();
    }
    catch(const std::exception&){
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
        std::ifstream inFile(targetFile);
        if(inFile){
            //parse json
            inFile >> present;  // Deserialize JSON data
            inFile.close();
        }
        else{
            //sort fetched
            JSON_SortByDate(fetched["values"]);

            //save fetched to the target file
            std::ofstream outFile(targetFile);
            outFile << fetched.dump(4);
            outFile.close();
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
    try{
        //save present to file
        std::ofstream outFile(targetFile);
        outFile << present.dump(4);
        outFile.close();
    }
    catch(const std::exception&){
        //error
        wxMessageBox("Error on UpdateSensor at saving part!!!!");
    }
}

std::vector<StationIndexInfo> LocalDB::LoadIndex(){
    //load json
    nlohmann::json present;

    //prepare json
    try{
        //load file
        std::ifstream inFile("index.json");
        if(inFile){
            //parse json
            inFile >> present;  // Deserialize JSON data
            inFile.close();
        }
        else{
            //error
            wxMessageBox("Error on LoadIndex (File doesn't exist)!!!!");
            return std::vector<StationIndexInfo>();
        }
    }
    catch(const std::exception&){
        //error
        wxMessageBox("Error on LoadIndex!!!!");
        return std::vector<StationIndexInfo>();
    }

    //check count
    size_t count = present.size();
    if(count <= 0)
        return std::vector<StationIndexInfo>();
    
    //write data
    std::vector<StationIndexInfo> data(count);
    while(count--){
        //check required fields
        if(present[count].contains("id") && present[count].contains("stationName")){
            //keep data
            data[count].id = JSON_ParseAsString(present[count]["id"]);            
            data[count].name = JSON_ParseString(present[count]["stationName"]);
        }
    }

    //return
    return data;
}

std::vector<SensorIndexInfo> LocalDB::LoadStation(std::string stationId){
    //load json
    nlohmann::json present;

    //prepare json
    try{
        //load file
        std::ifstream inFile("station_" + stationId + ".json");
        if(inFile){
            //parse json
            inFile >> present;  // Deserialize JSON data
            inFile.close();
        }
        else{
            //error
            wxMessageBox("Error on LoadStation (File doesn't exist)!!!!");
            return std::vector<SensorIndexInfo>();
        }
    }
    catch(const std::exception&){
        //error
        wxMessageBox("Error on LoadStation!!!!");
        return std::vector<SensorIndexInfo>();
    }

    //check count
    size_t count = present.size();
    if(count <= 0)
        return std::vector<SensorIndexInfo>();
    
    //write data
    std::vector<SensorIndexInfo> data(count);
    while(count--){
        //check requierd fields
        if(present[count].contains("id") && present[count].contains("param"))
            if(present[count]["param"].contains("paramName")){
                //add
                data[count].id = JSON_ParseAsString(present[count]["id"]);            
                data[count].name = JSON_ParseString(present[count]["param"]["paramName"]);
            }
    }

    //return
    return data;
}

std::vector<SensorData> LocalDB::LoadSensor(std::string sensorId){
    //load json
    nlohmann::json present;

    //prepare json
    try{
        //load file
        std::ifstream inFile("sensor_" + sensorId + ".json");
        if(inFile){
            //parse json
            inFile >> present;  // Deserialize JSON data
            inFile.close();
        }
        else{
            //error
            wxMessageBox("Error on LoadSensor (File doesn't exist)!!!!");
            return std::vector<SensorData>();
        }
    }
    catch(const std::exception&){
        //error
        wxMessageBox("Error on LoadSensor!!!!");
        return std::vector<SensorData>();
    }

    //scope to values
    present = present["values"];

    //check count
    size_t count = present.size();
    if(count <= 0)
        return std::vector<SensorData>();
    
    //write data
    std::vector<SensorData> data(count);
    while(count--){
        //check requierd fields
        if(present[count].contains("value") && present[count].contains("date")){
            //add
            data[count].value = JSON_ParseNumber(present[count]["value"]);            
            data[count].date = JSON_ParseString(present[count]["date"]);
        }
    }

    //return
    return data;
}

