#include "JSONTools.h"
#include <algorithm>

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





nlohmann::json JSON_MergeSort(const nlohmann::json& arr1, const nlohmann::json& arr2, const std::string& keyName) {
    // Merge arrays
    nlohmann::json mergedArray = arr1;
    mergedArray.insert(mergedArray.end(), arr2.begin(), arr2.end());

    // Sort safely
    std::sort(mergedArray.begin(), mergedArray.end(), [&keyName](const nlohmann::json& a, const nlohmann::json& b) {
        if (a.contains(keyName) && b.contains(keyName)) {
            return a[keyName].dump() < b[keyName].dump();
        }
        return a.contains(keyName);
    });

    return mergedArray;
}