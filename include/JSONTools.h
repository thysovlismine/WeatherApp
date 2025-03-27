/**
 * @file JSONTools.h
 * @brief Utility functions for working with JSON data using nlohmann::json.
 */

 #pragma once
 #ifndef JSONTOOLS_H
 #define JSONTOOLS_H
 
 #include <nlohmann/json.hpp>
 #include <string>
 #include <algorithm>
 
 /**
  * @brief Parses a number from a JSON item.
  * @param item The JSON item to parse.
  * @return The parsed float value, or 0 if parsing fails.
  */
 float JSON_ParseNumber(const nlohmann::json& item);
 
 /**
  * @brief Parses a number from a JSON object using a specified key.
  * @param item The JSON object.
  * @param keyName The key whose value should be parsed.
  * @return The parsed float value, or 0 if parsing fails.
  */
 float JSON_ParseNumber(const nlohmann::json& item, const std::string keyName);
 
 /**
  * @brief Parses a string from a JSON item.
  * @param item The JSON item to parse.
  * @return The parsed string, or an empty string if parsing fails.
  */
 std::string JSON_ParseString(const nlohmann::json& item);
 
 /**
  * @brief Parses a string from a JSON object using a specified key.
  * @param item The JSON object.
  * @param keyName The key whose value should be parsed.
  * @return The parsed string, or an empty string if parsing fails.
  */
 std::string JSON_ParseString(const nlohmann::json& item, const std::string keyName);
 
 /**
  * @brief Converts a JSON item into a string representation.
  * @param item The JSON item to convert.
  * @return The JSON item as a string.
  */
 std::string JSON_ParseAsString(const nlohmann::json& item);
 
 /**
  * @brief Converts a specific JSON object key's value into a string representation.
  * @param item The JSON object.
  * @param keyName The key whose value should be converted.
  * @return The JSON value as a string.
  */
 std::string JSON_ParseAsString(const nlohmann::json& item, const std::string keyName);
 
 /**
  * @brief Checks if a JSON item is a number.
  * @param item The JSON item to check.
  * @return True if the item is a number, false otherwise.
  */
 bool JSON_isNumber(const nlohmann::json& item);
 
 /**
  * @brief Checks if a specific key in a JSON object is a number.
  * @param item The JSON object.
  * @param keyName The key to check.
  * @return True if the key's value is a number, false otherwise.
  */
 bool JSON_isNumber(const nlohmann::json& item, const std::string keyName);
 
 /**
  * @brief Loads JSON data from a file.
  * @param data The JSON object to populate.
  * @param targetFile The file path to read from.
  * @return True if loading succeeds, false otherwise.
  */
 bool JSON_FromFile(nlohmann::json& data, std::string targetFile);
 
 /**
  * @brief Saves JSON data to a file.
  * @param data The JSON object to save.
  * @param targetFile The file path to write to.
  * @return True if saving succeeds, false otherwise.
  */
 bool JSON_ToFile(nlohmann::json& data, std::string targetFile);
 
 /**
  * @brief Removes duplicate entries in a JSON array based on a unique key.
  * @param jsonArray The JSON array to process.
  * @param key The key used to determine uniqueness.
  */
 void JSON_Unique(nlohmann::json& jsonArray, const std::string& key);
 
 /**
  * @brief Finds the index of an object in a JSON array based on a key-value pair.
  * @param keyValueDumped The JSON string value to search for.
  * @param keyName The key whose value is being searched.
  * @param arr The JSON array to search in.
  * @return The index (1-based) of the matching object, or 0 if not found.
  */
 size_t JSON_Find(const std::string& keyValueDumped, const std::string& keyName, const nlohmann::json& arr);
 
 /**
  * @brief Updates an existing JSON array by merging elements based on a unique key.
  * @param present The existing JSON array.
  * @param fetched The new JSON array to merge.
  * @param uniqueKeyName The key used to determine uniqueness.
  */
 void JSON_UpdateArray(nlohmann::json& present, const nlohmann::json& fetched, const std::string& uniqueKeyName);
 
 /**
  * @brief Parses a date-time string into a tm structure.
  * @param datetime The date-time string in the format "%Y-%m-%d %H:%M:%S".
  * @param tm The structure to store the parsed time.
  * @return True if parsing succeeds, false otherwise.
  */
 bool parseDateTime(const std::string& datetime, std::tm& tm);
 
 #endif // JSONTOOLS_H