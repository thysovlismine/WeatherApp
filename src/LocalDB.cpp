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

void LocalDB::UpdateStation(int stationId, std::string data){

}

void LocalDB::UpdateSensor(int sensorId, std::string data){

}

StationIndexInfo* LocalDB::LoadIndex(){
    return nullptr;
}

SensorIndexInfo* LocalDB::LoadStation(int stationId){
    return nullptr;
}

SensorDataset* LocalDB::LoadSensor(int sensorId){
    return nullptr;
}

