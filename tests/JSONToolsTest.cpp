#include <gtest/gtest.h>
#include "JSONTools.h"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

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
