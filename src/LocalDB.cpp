#include "LocalDB.h"
#include "JSONTools.h"
#include <fstream>

void UpdateGeneral(std::string data, std::string targetFile, std::string uniqueKeyName){
    //parse json
    nlohmann::json fetched;
    nlohmann::json present;
    
    //prepare jsons
    try{
        //parse fetched data
        fetched = nlohmann::json::parse(data);
        
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
        size_t i = 0;
        //scan fetched array
        for (const auto& item : fetched) {
            //find index of a present item with the same id
            i = JSON_Find(item[uniqueKeyName], uniqueKeyName, present);
            if(i){
                //update data of this item
                present[--i] = item;
            }else{
                //add this item to the present
                present.push_back(item);
            }
        }
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
    
    //merge arrays into an sorted array
    present["values"] = JSON_MergeSort(fetched["values"], present["values"], "date");
    
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

