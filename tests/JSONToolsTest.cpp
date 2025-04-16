#include <gtest/gtest.h>
#include "JSONTools.h"
#include <nlohmann/json.hpp>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <string>
#include <fstream>
#include <filesystem>

using json = nlohmann::json;

//================================================================
// float JSON_ParseNumber(const nlohmann::json& item)



TEST(JSON_ParseNumberTest, ParsesValidFloat) {
    json value = 3.14;
    EXPECT_FLOAT_EQ(JSON_ParseNumber(value), 3.14f);
}

TEST(JSON_ParseNumberTest, ParsesValidIntegerAsFloat) {
    json value = 42;
    EXPECT_FLOAT_EQ(JSON_ParseNumber(value), 42.0f);
}

TEST(JSON_ParseNumberTest, ReturnsZeroOnString) {
    json value = "not a number";
    EXPECT_FLOAT_EQ(JSON_ParseNumber(value), 0.0f);
}

TEST(JSON_ParseNumberTest, ReturnsZeroOnObject) {
    json value = json::object();
    EXPECT_FLOAT_EQ(JSON_ParseNumber(value), 0.0f);
}

TEST(JSON_ParseNumberTest, ReturnsZeroOnArray) {
    json value = json::array();
    EXPECT_FLOAT_EQ(JSON_ParseNumber(value), 0.0f);
}

TEST(JSON_ParseNumberTest, ReturnsZeroOnNull) {
    json value = nullptr;
    EXPECT_FLOAT_EQ(JSON_ParseNumber(value), 0.0f);
}

TEST(JSON_ParseNumberTest, ReturnsZeroOnBoolean) {
    json value = true;
    EXPECT_FLOAT_EQ(JSON_ParseNumber(value), 0.0f);
}



//================================================================
// float JSON_ParseNumber(const nlohmann::json& item, const std::string keyName)



// Test when key exists and holds a valid number
TEST(JSONToolsTest, ParseNumberWithKey_Valid) {
    nlohmann::json j = { {"temperature", 36.6} };
    EXPECT_FLOAT_EQ(JSON_ParseNumber(j, "temperature"), 36.6f);
}

// Test when key exists but holds a string (invalid number)
TEST(JSONToolsTest, ParseNumberWithKey_InvalidType) {
    nlohmann::json j = { {"temperature", "hot"} };
    EXPECT_FLOAT_EQ(JSON_ParseNumber(j, "temperature"), 0.0f);
}

// Test when key does not exist
TEST(JSONToolsTest, ParseNumberWithKey_MissingKey) {
    nlohmann::json j = { {"humidity", 55.0} };
    EXPECT_FLOAT_EQ(JSON_ParseNumber(j, "temperature"), 0.0f);
}

// Test when JSON is empty
TEST(JSONToolsTest, ParseNumberWithKey_EmptyJSON) {
    nlohmann::json j;
    EXPECT_FLOAT_EQ(JSON_ParseNumber(j, "temperature"), 0.0f);
}

// Test when value is null
TEST(JSONToolsTest, ParseNumberWithKey_NullValue) {
    nlohmann::json j = { {"temperature", nullptr} };
    EXPECT_FLOAT_EQ(JSON_ParseNumber(j, "temperature"), 0.0f);
}



//================================================================
// std::string JSON_ParseString(const nlohmann::json& item)



// Test when item holds a valid string
TEST(JSONToolsTest, ParseString_Valid) {
    nlohmann::json j = "Hello World";
    EXPECT_EQ(JSON_ParseString(j), "Hello World");
}

// Test when item holds a number (invalid string)
TEST(JSONToolsTest, ParseString_InvalidTypeNumber) {
    nlohmann::json j = 42;
    EXPECT_EQ(JSON_ParseString(j), "");
}

// Test when item holds a boolean (invalid string)
TEST(JSONToolsTest, ParseString_InvalidTypeBoolean) {
    nlohmann::json j = true;
    EXPECT_EQ(JSON_ParseString(j), "");
}

// Test when item is null
TEST(JSONToolsTest, ParseString_NullValue) {
    nlohmann::json j = nullptr;
    EXPECT_EQ(JSON_ParseString(j), "");
}

// Test when item is an object (invalid string)
TEST(JSONToolsTest, ParseString_InvalidTypeObject) {
    nlohmann::json j = { {"key", "value"} };
    EXPECT_EQ(JSON_ParseString(j), "");
}



//================================================================
// std::string JSON_ParseString(const nlohmann::json& item, const std::string keyName)



// Test when key exists and holds a valid string
TEST(JSONToolsTest, ParseStringWithKey_Valid) {
    nlohmann::json j = { {"name", "John Doe"} };
    EXPECT_EQ(JSON_ParseString(j, "name"), "John Doe");
}

// Test when key exists but holds a number (invalid string)
TEST(JSONToolsTest, ParseStringWithKey_InvalidTypeNumber) {
    nlohmann::json j = { {"name", 42} };
    EXPECT_EQ(JSON_ParseString(j, "name"), "");
}

// Test when key exists but holds a boolean (invalid string)
TEST(JSONToolsTest, ParseStringWithKey_InvalidTypeBoolean) {
    nlohmann::json j = { {"name", true} };
    EXPECT_EQ(JSON_ParseString(j, "name"), "");
}

// Test when key does not exist
TEST(JSONToolsTest, ParseStringWithKey_MissingKey) {
    nlohmann::json j = { {"age", 25} };
    EXPECT_EQ(JSON_ParseString(j, "name"), "");
}

// Test when value is null
TEST(JSONToolsTest, ParseStringWithKey_NullValue) {
    nlohmann::json j = { {"name", nullptr} };
    EXPECT_EQ(JSON_ParseString(j, "name"), "");
}

// Test when JSON is empty
TEST(JSONToolsTest, ParseStringWithKey_EmptyJSON) {
    nlohmann::json j;
    EXPECT_EQ(JSON_ParseString(j, "name"), "");
}



//================================================================
// std::string JSON_ParseAsString(const nlohmann::json& item)



#include <gtest/gtest.h>
#include "JSONTools.h"
#include <nlohmann/json.hpp>

// Test when item is a string
TEST(JSONToolsTest, ParseAsString_StringValue) {
    nlohmann::json j = "Hello World";
    EXPECT_EQ(JSON_ParseAsString(j), "\"Hello World\"");
}

// Test when item is a number
TEST(JSONToolsTest, ParseAsString_NumberValue) {
    nlohmann::json j = 42;
    EXPECT_EQ(JSON_ParseAsString(j), "42");
}

// Test when item is a boolean true
TEST(JSONToolsTest, ParseAsString_BooleanTrue) {
    nlohmann::json j = true;
    EXPECT_EQ(JSON_ParseAsString(j), "true");
}

// Test when item is a boolean false
TEST(JSONToolsTest, ParseAsString_BooleanFalse) {
    nlohmann::json j = false;
    EXPECT_EQ(JSON_ParseAsString(j), "false");
}

// Test when item is null
TEST(JSONToolsTest, ParseAsString_NullValue) {
    nlohmann::json j = nullptr;
    EXPECT_EQ(JSON_ParseAsString(j), "null");
}

// Test when item is an array
TEST(JSONToolsTest, ParseAsString_ArrayValue) {
    nlohmann::json j = {1, 2, 3};
    EXPECT_EQ(JSON_ParseAsString(j), "[1,2,3]");
}

// Test when item is an object
TEST(JSONToolsTest, ParseAsString_ObjectValue) {
    nlohmann::json j = { {"key", "value"} };
    EXPECT_EQ(JSON_ParseAsString(j), "{\"key\":\"value\"}");
}



//================================================================
// std::string JSON_ParseAsString(const nlohmann::json& item, const std::string keyName)



#include <gtest/gtest.h>
#include "JSONTools.h"
#include <nlohmann/json.hpp>

// Test when key exists and holds a string
TEST(JSONToolsTest, ParseAsStringWithKey_StringValue) {
    nlohmann::json j = { {"greeting", "Hello"} };
    EXPECT_EQ(JSON_ParseAsString(j, "greeting"), "\"Hello\"");
}

// Test when key exists and holds a number
TEST(JSONToolsTest, ParseAsStringWithKey_NumberValue) {
    nlohmann::json j = { {"age", 30} };
    EXPECT_EQ(JSON_ParseAsString(j, "age"), "30");
}

// Test when key exists and holds a boolean
TEST(JSONToolsTest, ParseAsStringWithKey_BooleanValue) {
    nlohmann::json j = { {"status", true} };
    EXPECT_EQ(JSON_ParseAsString(j, "status"), "true");
}

// Test when key exists and holds an object
TEST(JSONToolsTest, ParseAsStringWithKey_ObjectValue) {
    nlohmann::json j = { {"data", {{"x", 1}, {"y", 2}}} };
    EXPECT_EQ(JSON_ParseAsString(j, "data"), "{\"x\":1,\"y\":2}");
}

// Test when key does not exist
TEST(JSONToolsTest, ParseAsStringWithKey_MissingKey) {
    nlohmann::json j = { {"someKey", 42} };
    EXPECT_EQ(JSON_ParseAsString(j, "missingKey"), "");
}

// Test when key exists but value is null
TEST(JSONToolsTest, ParseAsStringWithKey_NullValue) {
    nlohmann::json j = { {"nothing", nullptr} };
    EXPECT_EQ(JSON_ParseAsString(j, "nothing"), "null");
}

// Test when JSON is empty
TEST(JSONToolsTest, ParseAsStringWithKey_EmptyJSON) {
    nlohmann::json j;
    EXPECT_EQ(JSON_ParseAsString(j, "anyKey"), "");
}




//================================================================
// bool JSON_FromFile(nlohmann::json& data, std::string targetFile)



//???



//================================================================
// bool JSON_ToFile(nlohmann::json& data, std::string targetFile)



//???



//================================================================
// bool JSON_isNumber(const nlohmann::json& item)



// Test when item is an integer
TEST(JSONToolsTest, IsNumber_Integer) {
    nlohmann::json j = 42;
    EXPECT_TRUE(JSON_isNumber(j));
}

// Test when item is a float
TEST(JSONToolsTest, IsNumber_Float) {
    nlohmann::json j = 3.1415;
    EXPECT_TRUE(JSON_isNumber(j));
}

// Test when item is a numeric string
TEST(JSONToolsTest, IsNumber_StringValue) {
    nlohmann::json j = "123.45";
    EXPECT_FALSE(JSON_isNumber(j));
}

// Test when item is a boolean true
TEST(JSONToolsTest, IsNumber_BooleanTrue) {
    nlohmann::json j = true;
    EXPECT_FALSE(JSON_isNumber(j));
}

// Test when item is a boolean false
TEST(JSONToolsTest, IsNumber_BooleanFalse) {
    nlohmann::json j = false;
    EXPECT_FALSE(JSON_isNumber(j));
}

// Test when item is a null value
TEST(JSONToolsTest, IsNumber_Null) {
    nlohmann::json j = nullptr;
    EXPECT_FALSE(JSON_isNumber(j));
}

// Test when item is an array
TEST(JSONToolsTest, IsNumber_Array) {
    nlohmann::json j = {1, 2, 3};
    EXPECT_FALSE(JSON_isNumber(j));
}

// Test when item is an object
TEST(JSONToolsTest, IsNumber_Object) {
    nlohmann::json j = { {"a", 1}, {"b", 2} };
    EXPECT_FALSE(JSON_isNumber(j));
}



//================================================================
// bool JSON_isNumber(const nlohmann::json& item, const std::string keyName)



// Test when key exists and value is an integer
TEST(JSONToolsTest, IsNumber_Key_Integer) {
    nlohmann::json j = { {"value", 42} };
    EXPECT_TRUE(JSON_isNumber(j, "value"));
}

// Test when key exists and value is a float
TEST(JSONToolsTest, IsNumber_Key_Float) {
    nlohmann::json j = { {"value", 3.1415} };
    EXPECT_TRUE(JSON_isNumber(j, "value"));
}

// Test when key exists and value is a numeric string
TEST(JSONToolsTest, IsNumber_Key_StringValue) {
    nlohmann::json j = { {"value", "123.45"} };
    EXPECT_FALSE(JSON_isNumber(j, "value"));
}

// Test when key exists and value is boolean true
TEST(JSONToolsTest, IsNumber_Key_BooleanTrue) {
    nlohmann::json j = { {"value", true} };
    EXPECT_FALSE(JSON_isNumber(j, "value"));
}

// Test when key exists and value is boolean false
TEST(JSONToolsTest, IsNumber_Key_BooleanFalse) {
    nlohmann::json j = { {"value", false} };
    EXPECT_FALSE(JSON_isNumber(j, "value"));
}

// Test when key exists and value is null
TEST(JSONToolsTest, IsNumber_Key_Null) {
    nlohmann::json j = { {"value", nullptr} };
    EXPECT_FALSE(JSON_isNumber(j, "value"));
}

// Test when key exists and value is an array
TEST(JSONToolsTest, IsNumber_Key_Array) {
    nlohmann::json j = { {"value", nlohmann::json::array({1, 2, 3})} };
    EXPECT_FALSE(JSON_isNumber(j, "value"));
}

// Test when key exists and value is an object
TEST(JSONToolsTest, IsNumber_Key_Object) {
    nlohmann::json j = { {"value", {{"a", 1}, {"b", 2}}} };
    EXPECT_FALSE(JSON_isNumber(j, "value"));
}

// Test when key does not exist
TEST(JSONToolsTest, IsNumber_Key_NotExists) {
    nlohmann::json j = { {"anotherValue", 42} };
    EXPECT_FALSE(JSON_isNumber(j, "value"));
}



//================================================================
// void JSON_Unique(nlohmann::json& jsonArray, const std::string& key)



TEST(JSONToolsTest, Unique_RemovesDuplicatesByKey) {
    nlohmann::json j = {
        {{"id", 1}, {"name", "A"}},
        {{"id", 2}, {"name", "B"}},
        {{"id", 1}, {"name", "C"}}
    };

    JSON_Unique(j, "id");

    ASSERT_EQ(j.size(), 2);
    EXPECT_EQ(j[0]["id"], 1);
    EXPECT_EQ(j[1]["id"], 2);
}

TEST(JSONToolsTest, Unique_IgnoresItemsWithoutKey) {
    nlohmann::json j = {
        {{"id", 1}, {"name", "A"}},
        {{"name", "B"}}, // no "id"
        {{"id", 1}, {"name", "C"}}
    };

    JSON_Unique(j, "id");

    ASSERT_EQ(j.size(), 2);
    EXPECT_EQ(j[0]["id"], 1);
    EXPECT_TRUE(j[1].contains("name"));
    EXPECT_FALSE(j[1].contains("id"));
}

TEST(JSONToolsTest, Unique_EmptyArray) {
    nlohmann::json j = nlohmann::json::array();
    JSON_Unique(j, "id");
    EXPECT_EQ(j.size(), 0);
}

TEST(JSONToolsTest, Unique_NoDuplicates) {
    nlohmann::json j = {
        {{"id", 1}},
        {{"id", 2}},
        {{"id", 3}}
    };

    JSON_Unique(j, "id");

    EXPECT_EQ(j.size(), 3);
    EXPECT_EQ(j[0]["id"], 1);
    EXPECT_EQ(j[1]["id"], 2);
    EXPECT_EQ(j[2]["id"], 3);
}



//================================================================
// size_t JSON_Find(const std::string& keyValueDumped, const std::string& keyName, const nlohmann::json& arr)



TEST(JSONToolsTest, Find_FindsExistingValue) {
    nlohmann::json arr = {
        {{"id", 1}, {"name", "A"}},
        {{"id", 2}, {"name", "B"}},
        {{"id", 3}, {"name", "C"}}
    };

    // searching for dumped value "2" under key "id"
    size_t index = JSON_Find("2", "id", arr);
    EXPECT_EQ(index, 2);
}

TEST(JSONToolsTest, Find_ReturnsZeroIfNotFound) {
    nlohmann::json arr = {
        {{"id", 1}, {"name", "A"}},
        {{"id", 2}, {"name", "B"}}
    };

    size_t index = JSON_Find("5", "id", arr);
    EXPECT_EQ(index, 0);
}

TEST(JSONToolsTest, Find_SkipsMissingKeys) {
    nlohmann::json arr = {
        {{"id", 1}},
        {{"name", "B"}},
        {{"id", 2}}
    };

    size_t index = JSON_Find("2", "id", arr);
    EXPECT_EQ(index, 3); // 3rd element has id=2
}

TEST(JSONToolsTest, Find_EmptyArray) {
    nlohmann::json arr = nlohmann::json::array();
    size_t index = JSON_Find("1", "id", arr);
    EXPECT_EQ(index, 0);
}

TEST(JSONToolsTest, Find_MatchesStringifiedValue) {
    nlohmann::json arr = {
        {{"id", "1"}},
        {{"id", 2}}
    };

    // keyValueDumped should match JSON dump of "1"
    size_t index = JSON_Find("\"1\"", "id", arr);
    EXPECT_EQ(index, 1);

    // keyValueDumped for 2
    index = JSON_Find("2", "id", arr);
    EXPECT_EQ(index, 2);
}



//================================================================
// void JSON_UpdateArray(nlohmann::json& arrPresent, const nlohmann::json& arrNew, const std::string& uniqueKeyName)



TEST(JSONToolsTest, UpdateArray_UpdatesExistingItems) {
    nlohmann::json arrPresent = {
        {{"id", 1}, {"name", "A"}},
        {{"id", 2}, {"name", "B"}}
    };
    nlohmann::json arrNew = {
        {{"id", 1}, {"name", "Updated A"}},
        {{"id", 3}, {"name", "C"}}
    };

    // Update arrPresent with arrNew based on "id" key
    JSON_UpdateArray(arrPresent, arrNew, "id");

    // Check that item with id 1 was updated
    EXPECT_EQ(arrPresent[0]["name"], "Updated A");
    // Check that item with id 2 remains the same
    EXPECT_EQ(arrPresent[1]["name"], "B");
    // Check that item with id 3 was added
    EXPECT_EQ(arrPresent[2]["name"], "C");
}

TEST(JSONToolsTest, UpdateArray_AddsNewItems) {
    nlohmann::json arrPresent = {
        {{"id", 1}, {"name", "A"}},
        {{"id", 2}, {"name", "B"}}
    };
    nlohmann::json arrNew = {
        {{"id", 3}, {"name", "C"}}
    };

    JSON_UpdateArray(arrPresent, arrNew, "id");

    // Check that the new item with id 3 is added
    EXPECT_EQ(arrPresent.size(), 3);
    EXPECT_EQ(arrPresent[2]["name"], "C");
}

TEST(JSONToolsTest, UpdateArray_UpdatesMultipleItems) {
    nlohmann::json arrPresent = {
        {{"id", 1}, {"name", "A"}},
        {{"id", 2}, {"name", "B"}}
    };
    nlohmann::json arrNew = {
        {{"id", 1}, {"name", "Updated A"}},
        {{"id", 2}, {"name", "Updated B"}}
    };

    JSON_UpdateArray(arrPresent, arrNew, "id");

    // Both items should be updated
    EXPECT_EQ(arrPresent[0]["name"], "Updated A");
    EXPECT_EQ(arrPresent[1]["name"], "Updated B");
}

TEST(JSONToolsTest, UpdateArray_NoUpdatesIfSameData) {
    nlohmann::json arrPresent = {
        {{"id", 1}, {"name", "A"}},
        {{"id", 2}, {"name", "B"}}
    };
    nlohmann::json arrNew = {
        {{"id", 1}, {"name", "A"}},
        {{"id", 2}, {"name", "B"}}
    };

    JSON_UpdateArray(arrPresent, arrNew, "id");

    // No updates should happen, data remains the same
    EXPECT_EQ(arrPresent[0]["name"], "A");
    EXPECT_EQ(arrPresent[1]["name"], "B");
}

TEST(JSONToolsTest, UpdateArray_HandlesEmptyArrays) {
    nlohmann::json arrPresent = nlohmann::json::array();
    nlohmann::json arrNew = {
        {{"id", 1}, {"name", "A"}},
        {{"id", 2}, {"name", "B"}}
    };

    JSON_UpdateArray(arrPresent, arrNew, "id");

    // arrPresent should now contain the new items
    EXPECT_EQ(arrPresent.size(), 2);
    EXPECT_EQ(arrPresent[0]["name"], "A");
    EXPECT_EQ(arrPresent[1]["name"], "B");
}

TEST(JSONToolsTest, UpdateArray_HandlesEmptyNewArray) {
    nlohmann::json arrPresent = {
        {{"id", 1}, {"name", "A"}},
        {{"id", 2}, {"name", "B"}}
    };
    nlohmann::json arrNew = nlohmann::json::array();

    JSON_UpdateArray(arrPresent, arrNew, "id");

    // arrPresent should remain unchanged
    EXPECT_EQ(arrPresent.size(), 2);
    EXPECT_EQ(arrPresent[0]["name"], "A");
    EXPECT_EQ(arrPresent[1]["name"], "B");
}



//================================================================
// bool parseDateTime(const std::string& datetime, std::tm& tm)



TEST(ParseDateTimeTest, ValidDateTime) {
    std::string datetime = "2025-04-16 12:30:00";
    std::tm tm = {};

    bool result = parseDateTime(datetime, tm);

    // Check that the parsing is successful and the tm structure is correct
    EXPECT_TRUE(result);
    EXPECT_EQ(tm.tm_year, 2025 - 1900); // tm_year is years since 1900
    EXPECT_EQ(tm.tm_mon, 4 - 1); // tm_mon is 0-based (0 = January)
    EXPECT_EQ(tm.tm_mday, 16);
    EXPECT_EQ(tm.tm_hour, 12);
    EXPECT_EQ(tm.tm_min, 30);
    EXPECT_EQ(tm.tm_sec, 0);
}

TEST(ParseDateTimeTest, InvalidDateTime) {
    std::string datetime = "invalid-date-time";
    std::tm tm = {};

    bool result = parseDateTime(datetime, tm);

    // Check that parsing fails
    EXPECT_FALSE(result);
}

TEST(ParseDateTimeTest, EdgeCaseNoTime) {
    std::string datetime = "2025-04-16";
    std::tm tm = {};

    bool result = parseDateTime(datetime, tm);

    // Check that parsing is successful even if there's no time
    EXPECT_TRUE(result);
    EXPECT_EQ(tm.tm_year, 2025 - 1900); // tm_year is years since 1900
    EXPECT_EQ(tm.tm_mon, 4 - 1); // tm_mon is 0-based (0 = January)
    EXPECT_EQ(tm.tm_mday, 16);
    EXPECT_EQ(tm.tm_hour, 0); // Default time is set to 00:00:00
    EXPECT_EQ(tm.tm_min, 0);
    EXPECT_EQ(tm.tm_sec, 0);
}


TEST(ParseDateTimeTest, EdgeCaseLeapYear) {
    std::string datetime = "2024-02-29 23:59:59";
    std::tm tm = {};

    bool result = parseDateTime(datetime, tm);

    // Check that parsing is successful for a valid leap year date
    EXPECT_TRUE(result);
    EXPECT_EQ(tm.tm_year, 2024 - 1900);
    EXPECT_EQ(tm.tm_mon, 2 - 1); // February
    EXPECT_EQ(tm.tm_mday, 29);
}

TEST(ParseDateTimeTest, InvalidMonth) {
    std::string datetime = "2025-13-16 12:30:00"; // Invalid month
    std::tm tm = {};

    bool result = parseDateTime(datetime, tm);

    // Check that parsing fails for an invalid month
    EXPECT_FALSE(result);
}

TEST(ParseDateTimeTest, InvalidDay) {
    std::string datetime = "2025-04-32 12:30:00"; // Invalid day
    std::tm tm = {};

    bool result = parseDateTime(datetime, tm);

    // Check that parsing fails for an invalid day
    EXPECT_FALSE(result);
}


