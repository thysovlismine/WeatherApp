#include "JSONTools.h"

float JSON_ParseNumber(const nlohmann::json& item) {
    try{
        return item.get<float>();
    }
    catch(const std::exception&){
        return 0;
    }
}

float JSON_ParseNumber(const nlohmann::json& item, const std::string keyName) {
    try{
        if(item.contains(keyName))
            return item[keyName].get<float>();
        return 0;
    }
    catch(const std::exception&){
        return 0;
    }
}

std::string JSON_ParseString(const nlohmann::json& item) {
    try{
        return item.get<std::string>();
    }
    catch(const std::exception&){
        return "";
    }
}

std::string JSON_ParseString(const nlohmann::json& item, const std::string keyName) {
    try{
        if(item.contains(keyName))
            return item[keyName].get<std::string>();
        return "";
    }
    catch(const std::exception&){
        return "";
    }
}

std::string JSON_ParseAsString(const nlohmann::json& item){
    try{
        return item.dump();
    }
    catch(const std::exception&){
        return "";
    }
}

std::string JSON_ParseAsString(const nlohmann::json& item, const std::string keyName){
    try{
        if(item.contains(keyName))
            return item[keyName].dump();
        return 0;
    }
    catch(const std::exception&){
        return 0;
    }
}