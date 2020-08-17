#include <vector>
#include <memory>
#include "gtest/gtest.h"
#include "CObjectIndex.h"

using gintel::storage::CObjectIndex;

TEST(CObjectIndex_UnitTest, Input_Validations)
{
    CObjectIndex index;
    ASSERT_THROW(index.add("", "empty key"), std::invalid_argument);
    ASSERT_THROW(index.add("", 200), std::invalid_argument);
    ASSERT_THROW(index.add("", 4.5), std::invalid_argument);
}

TEST(CObjectIndex_UnitTest, Basic_Add_and_Fetch_Test)
{
    int value {2};
    CObjectIndex obIndex;

    obIndex.add("key1", value);
    auto searchResult {obIndex.search("key1")};

    ASSERT_EQ(searchResult.size(), 1);
    ASSERT_EQ(std::any_cast<int>(searchResult[0]), value);
}

TEST(CObjectIndex_UnitTest, Non_Existing_Key)
{
    int value {2};
    CObjectIndex obIndex;

    obIndex.add("key1", value);
    ASSERT_TRUE(obIndex.search("key").empty());
    ASSERT_TRUE(obIndex.search("ke1").empty());
    ASSERT_TRUE(obIndex.search("Key1").empty());
}

TEST(CObjectIndex_UnitTest, Mixed_Value_Types_Same_Index)
{
    int value {2};
    CObjectIndex obIndex;
    std::string stringValue{"string_1"};

    obIndex.add("key1", value);
    obIndex.add("key1", stringValue);

    auto searchResult {obIndex.search("key1")};
    ASSERT_TRUE(searchResult.size() == 2);
    ASSERT_TRUE(std::any_cast<int>(searchResult[0]) == 2);
    ASSERT_TRUE(std::any_cast<std::string>(searchResult[1]) == stringValue);
}

TEST(CObjectIndex_UnitTest, Various_Value_Types_Different_Index)
{
    struct DummyValue
    {
        int val;
        std::string data;

        bool operator ==(const DummyValue& right)
        {
            return (val == right.val && data == right.data);
        }
    };

    CObjectIndex obIndex1;
    CObjectIndex obIndex2;

    DummyValue dummyVal {200, "two hundred"};

    obIndex1.add("string", std::string("value1"));
    obIndex2.add("struct", dummyVal);

    auto result1 {obIndex1.search("string")};
    auto result2 {obIndex2.search("struct")};

    ASSERT_EQ(result1.size(), 1);
    ASSERT_EQ(result2.size(), 1);

    ASSERT_EQ(std::any_cast<std::string>(result1[0]), "value1");
    ASSERT_TRUE(std::any_cast<DummyValue>(result2[0]) == dummyVal);
}

TEST(CObjectIndex_UnitTest, One_Key_Multiple_Values)
{
    CObjectIndex obIndex;

    obIndex.add("100", std::string("one hundred"));
    obIndex.add("100", std::string("one zero zero"));
    obIndex.add("100", std::string("ten and a zero"));

    auto result {obIndex.search("100")};
    ASSERT_EQ(result.size(), 3);

    ASSERT_EQ(std::any_cast<std::string>(result[0]), "one hundred");
    ASSERT_EQ(std::any_cast<std::string>(result[1]), "one zero zero");
    ASSERT_EQ(std::any_cast<std::string>(result[2]), "ten and a zero");
}
