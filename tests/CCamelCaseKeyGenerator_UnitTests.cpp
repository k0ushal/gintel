
#include "gtest/gtest.h"
#include "CCamelCaseKeyGenerator.h"
#include <iostream>

using gintel::modules::CCamelCaseKeyGenerator;

TEST(CCamelCaseKeyGenerator_UnitTests, Basic_Function)
{
    auto result {CCamelCaseKeyGenerator::createKeys("CamelCaseInput")};

    ASSERT_EQ(result.size(), 3);
    ASSERT_EQ(result[0], "Camel");
    ASSERT_EQ(result[1], "Case");
    ASSERT_EQ(result[2], "Input");
}

TEST(CCamelCaseKeyGenerator_UnitTests, All_Lowercase)
{
    std::string input{"lowercaseinput"};
    auto result {CCamelCaseKeyGenerator::createKeys(input)};

    ASSERT_EQ(result.size(), 1);
    ASSERT_EQ(result[0], input);
}

TEST(CCamelCaseKeyGenerator_UnitTests, All_Uppercase)
{
    std::string input{"UPPERCASEINPUT"};
    auto result {CCamelCaseKeyGenerator::createKeys(input)};

    ASSERT_EQ(result.size(), 1);
    ASSERT_EQ(result[0], input);
}

TEST(CCamelCaseKeyGenerator_UnitTests, Multiple_Uppercase_Followed_By_Lowercase)
{
    std::string input{"CSINewYork"};
    auto result {CCamelCaseKeyGenerator::createKeys(input)};

    ASSERT_EQ(result.size(), 2);
    ASSERT_EQ(result[0], "CSINew");
    ASSERT_EQ(result[1], "York");
}

TEST(CCamelCaseKeyGenerator_UnitTests, Multiple_Lowercase_Followed_By_Uppercase)
{
    std::string input{"thisIsAfunctionName"};
    auto result {CCamelCaseKeyGenerator::createKeys(input)};

    ASSERT_EQ(result.size(), 4);
    ASSERT_EQ(result[0], "this");
    ASSERT_EQ(result[1], "Is");
    ASSERT_EQ(result[2], "Afunction");
    ASSERT_EQ(result[3], "Name");
}

TEST(CCamelCaseKeyGenerator_UnitTests, Non_Alphabetic_Characters_1)
{
    std::string input{"Shape::Draw"};
    auto result {CCamelCaseKeyGenerator::createKeys(input)};

    ASSERT_EQ(result.size(), 2);
    ASSERT_EQ(result[0], "Shape");
    ASSERT_EQ(result[1], "Draw");
}

TEST(CCamelCaseKeyGenerator_UnitTests, Non_Alphabetic_Characters_2)
{
    std::string input{"Shape_Draw"};
    auto result {CCamelCaseKeyGenerator::createKeys(input)};

    ASSERT_EQ(result.size(), 2);
    ASSERT_EQ(result[0], "Shape");
    ASSERT_EQ(result[1], "Draw");
}

TEST(CCamelCaseKeyGenerator_UnitTests, Non_Alphabetic_Characters_In_The_Beginning)
{
    std::string input{"_this_Is1A_Shape_Draw"};
    auto result {CCamelCaseKeyGenerator::createKeys(input)};

    ASSERT_EQ(result.size(), 5);
    ASSERT_EQ(result[0], "this");
    ASSERT_EQ(result[1], "Is");
    ASSERT_EQ(result[2], "A");
    ASSERT_EQ(result[3], "Shape");
    ASSERT_EQ(result[4], "Draw");
}
