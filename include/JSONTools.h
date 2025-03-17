#pragma once
#ifndef JSONTOOLS_H
#define JSONTOOLS_H

#include <nlohmann/json.hpp>
#include <string>

// Function declarations - Change references to const nlohmann::json&
float JSON_ParseNumber(const nlohmann::json& item);
std::string JSON_ParseString(const nlohmann::json& item);

#endif // JSONTOOLS_H
