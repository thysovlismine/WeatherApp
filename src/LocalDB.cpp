#include "LocalDB.h"
#include "JSONTools.h"
#include <fstream>


SensorDataset::SensorDataset(){}
SensorDataset::~SensorDataset(){}

void LocalDB::UpdateIndex(std::string data){
    //parse json
    nlohmann::json fetched;
    nlohmann::json present;
    
    //prepare jsons
    try{
        //parse fetched data
        fetched = nlohmann::json::parse(data);
        
        //load file
        std::ifstream inFile("index.json");
        if(inFile){
            //parse json
            inFile >> present;  // Deserialize JSON data
            inFile.close();
        }
        else{
            //just make an empty array
            //present = nlohmann::json::array();
            //or skip processing part and save fetched to index.json
            std::ofstream outFile("index.json");
            outFile << fetched.dump(4);
            outFile.close();
            return;
        }
    }
    catch(const std::exception&){
        //error
        wxMessageBox("Error on UpdateIndex!!!!");
        return;
    }

    //update present with fresh
    try{
        size_t i = 0;
        //scan fetched array
        for (const auto& item : fetched) {
            //find index of a present item with the same id
            i = JSON_Find(item["id"], "id", present);
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
        wxMessageBox("Error on UpdateIndex at processing part!!!!");
    }
    
    //save the updated json
    try{
        //save present to file
        std::ofstream outFile("index.json");
        outFile << present.dump(4);
        outFile.close();
    }
    catch(const std::exception&){
        //error
        wxMessageBox("Error on UpdateIndex at saving part!!!!");
    }
}

void LocalDB::UpdateStation(std::string stationId, std::string data){

}

void LocalDB::UpdateSensor(std::string sensorId, std::string data){

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
        data[count].id = JSON_ParseAsString(present[count]["id"]);            
        data[count].name = JSON_ParseString(present[count]["stationName"]);
    }

    //return
    return data;
}

std::vector<SensorIndexInfo> LocalDB::LoadStation(std::string stationId){
    return std::vector<SensorIndexInfo>();
}

std::vector<SensorDataset> LocalDB::LoadSensor(std::string sensorId){
    return std::vector<SensorDataset>();
}

