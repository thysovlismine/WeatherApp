#pragma once
#ifndef JSONTOOLS_H
#define JSONTOOLS_H

#include <nlohmann/json.hpp>
#include <string>

// Function declarations - Change references to const nlohmann::json&
float JSON_ParseNumber(const nlohmann::json& item);
float JSON_ParseNumber(const nlohmann::json& item, const std::string keyName);
std::string JSON_ParseString(const nlohmann::json& item);
std::string JSON_ParseString(const nlohmann::json& item, const std::string keyName);
std::string JSON_ParseAsString(const nlohmann::json& item);
std::string JSON_ParseAsString(const nlohmann::json& item, const std::string keyName);

template <typename T>
size_t JSON_Find(const T keyValue, const std::string keyName, const nlohmann::json& arr){
    size_t i = 0;
    size_t f = arr.size();
    while(i < f){
        //compare current
        try{
            if(arr[i].contains(keyName))
                if(arr[i][keyName].get<T>() == keyValue)
                    return i + 1;
        }
        catch(const std::exception&){
            //do nothing and scan further
        }
        //next
        i++;
    }
    return 0;
}

#endif // JSONTOOLS_H
