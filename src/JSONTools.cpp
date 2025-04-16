#include "JSONTools.h"
#include <algorithm>
#include <unordered_set>
#include <fstream>
#include <sstream>
#include <filesystem>

float JSON_ParseNumber(const nlohmann::json& item) {
    if (item.is_number()) {
        return item.get<float>();
    }
    return 0;
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
        return "";
    }
    catch(const std::exception&){
        return "";
    }
}

bool JSON_FromFile(nlohmann::json& data, std::string targetFile){
    try{
        std::ifstream inFile(targetFile);
        if(inFile){
            //parse json
            inFile >> data;  // Deserialize JSON data
            inFile.close();
            //load was successful
            return true;
        }
    }
    catch(const std::exception&){
        //do nothing
    }
    //couldn't load file
    return false;
}

bool JSON_ToFile(nlohmann::json& data, std::string targetFile){
    try{
        //make directories
        //ChatGPT
        std::filesystem::path dirPath = std::filesystem::path(targetFile).parent_path(); // Extract directory from the full path
        if (!dirPath.empty() && !std::filesystem::exists(dirPath)) {
            if (!std::filesystem::create_directories(dirPath)) {
                return false;
            }
        }
        //save present to file
        std::ofstream outFile(targetFile);
        outFile << data.dump(4);
        outFile.close();
        //save was successful
        return true;
    }
    catch(const std::exception&){
        //do nothing
    }
    //couldn't save the file
    return false;
}

bool JSON_isNumber(const nlohmann::json& item){
    return item.is_number();
}

bool JSON_isNumber(const nlohmann::json& item, const std::string keyName){
    return item.contains(keyName) && item[keyName].is_number();
}

//by ChatGPT
void JSON_Unique(nlohmann::json& jsonArray, const std::string& key) {
    std::unordered_set<std::string> seenValues;

    jsonArray.erase(std::remove_if(jsonArray.begin(), jsonArray.end(),
        [&seenValues, &key](const nlohmann::json& item) {
            // Check if the key exists in the object
            if (item.contains(key)) {
                std::string value = item[key].dump();
                // If value is already seen, remove this item
                return !seenValues.insert(value).second;
            }
            return false; // Keep items that don't have the key
        }),
        jsonArray.end()
    );
}

size_t JSON_Find(const std::string& keyValueDumped, const std::string& keyName, const nlohmann::json& arr){
    size_t i = 0;
    size_t f = arr.size();
    while(i < f){
        //compare current
        try{
            if(arr[i].contains(keyName))
                if(arr[i][keyName].dump() == keyValueDumped)
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

//arrPresent and arrNew should contain only elements with unique key names
void JSON_UpdateArray(nlohmann::json& arrPresent, const nlohmann::json& arrNew, const std::string& uniqueKeyName){
    size_t i = 0;
    //scan fetched array
    for (const auto& item : arrNew) {
        //find index of a present item with the same id
        i = JSON_Find(item[uniqueKeyName].dump(), uniqueKeyName, arrPresent);
        if(i){
            //update data of this item
            arrPresent[--i] = item;
        }else{
            //add this item to the present
            arrPresent.push_back(item);
        }
    }
}


//other

//ChatGPT
bool parseDateTime(const std::string& datetime, std::tm& tm) {
    std::istringstream ss(datetime);
    if (ss >> std::get_time(&tm, "%Y-%m-%d %H:%M:%S")) {
        return true; // Successfully parsed with date and time
    }
    // If parsing fails, try parsing just the date part (defaulting time to 00:00:00)
    ss.clear();
    ss.str(datetime); // reset the stringstream
    if (ss >> std::get_time(&tm, "%Y-%m-%d")) {
        tm.tm_hour = 0;
        tm.tm_min = 0;
        tm.tm_sec = 0;
        return true; // Successfully parsed with date only
    }
    return false; // Failed to parse
}