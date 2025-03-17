#include "LocalDB.h"
#include "JSONTools.h"


SensorDataset::SensorDataset(){}
SensorDataset::~SensorDataset(){}

void LocalDB::UpdateIndex(std::string data){

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

