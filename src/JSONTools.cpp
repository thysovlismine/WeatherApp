#include "JSONTools.h"

float JSON_ParseNumber(const nlohmann::json& item) {
    try {
        return item.get<float>();
    } catch (const std::exception&) {
        return 0;
    }
}

std::string JSON_ParseString(const nlohmann::json& item) {
    try {
        return item.get<std::string>();
    } catch (const std::exception&) {
        return "";
    }
}
