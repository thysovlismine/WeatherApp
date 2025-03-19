#pragma once
#ifndef JSONTOOLS_H
#define JSONTOOLS_H

#include <nlohmann/json.hpp>
#include <string>
#include <algorithm>

// Function declarations - Change references to const nlohmann::json&
float JSON_ParseNumber(const nlohmann::json& item);
float JSON_ParseNumber(const nlohmann::json& item, const std::string keyName);
std::string JSON_ParseString(const nlohmann::json& item);
std::string JSON_ParseString(const nlohmann::json& item, const std::string keyName);
std::string JSON_ParseAsString(const nlohmann::json& item);
std::string JSON_ParseAsString(const nlohmann::json& item, const std::string keyName);
bool JSON_isNumber(const nlohmann::json& item);
bool JSON_isNumber(const nlohmann::json& item, const std::string keyName);

bool JSON_FromFile(nlohmann::json& data, std::string targetFile);
bool JSON_ToFile(nlohmann::json& data, std::string targetFile);

void JSON_Unique(nlohmann::json& jsonArray, const std::string& key);

size_t JSON_Find(const std::string& keyValueDumped, const std::string& keyName, const nlohmann::json& arr);

void JSON_UpdateArray(nlohmann::json& present, const nlohmann::json& fetched, const std::string& uniqueKeyName);

//other

bool parseDateTime(const std::string& datetime, std::tm& tm);


#endif // JSONTOOLS_H
