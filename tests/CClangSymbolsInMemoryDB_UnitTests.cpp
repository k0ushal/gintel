#include <vector>
#include <memory>
#include "gtest/gtest.h"
#include "CClangParser.h"
#include "IStoreObject.h"
#include "CClangSymbolsInMemoryDB.h"

using gintel::storage::IStoreObject;
using gintel::modules::CClangParser;
using gintel::storage::CClangSymbolsInMemoryDB;

std::vector<std::shared_ptr<CClangParser::CObjectInfo>> addDummyInMemoryDBEntries()
{
    std::vector<std::shared_ptr<CClangParser::CObjectInfo>> result;

    auto createObject {[](
        const std::string& name,
        CClangParser::ObjectType type,
        const std::filesystem::path& filePath) {

        return std::make_shared<CClangParser::CObjectInfo>(
                name, type, filePath);
    }};

    result.push_back(createObject("Shape", CClangParser::ObjectType::Class, "shape/Shape.h"));
    result.push_back(createObject("Shape::Size", CClangParser::ObjectType::Method, "shape/Shape.h"));
    result.push_back(createObject("createShapeInstance", CClangParser::ObjectType::GlobalFunction, "shape/Shape.cpp"));
    result.push_back(createObject("Rectangle", CClangParser::ObjectType::Class, "shape/Rectangle.h"));

    return result;
}

TEST(CClangSymbolsInMemoryDB_UnitTests, Input_Validations)
{
    CClangSymbolsInMemoryDB store;
    ASSERT_THROW(store.add(std::shared_ptr<CClangParser::CObjectInfo>()), std::invalid_argument);
}

TEST(CClangSymbolsInMemoryDB_UnitTests, Simple_Search)
{
    auto dummyObjects {addDummyInMemoryDBEntries()};
    CClangSymbolsInMemoryDB store;

    std::for_each(dummyObjects.begin(), dummyObjects.end(),
        [&](std::shared_ptr<CClangParser::CObjectInfo> object) {
            store.add(object);
        });

    auto searchResults {store.search("Shape")};
    ASSERT_EQ(searchResults.size(), 1);
    ASSERT_TRUE(searchResults[0]->name() == "Shape");
    ASSERT_TRUE(searchResults[0]->m_type == CClangParser::ObjectType::Class);
    ASSERT_TRUE(searchResults[0]->m_location.file == "shape/Shape.h");

    searchResults = store.search("createShapeInstance");
    ASSERT_EQ(searchResults.size(), 1);
    ASSERT_TRUE(searchResults[0]->name() == "createShapeInstance");
    ASSERT_TRUE(searchResults[0]->m_type == CClangParser::ObjectType::GlobalFunction);
    ASSERT_TRUE(searchResults[0]->m_location.file == "shape/Shape.cpp");

    searchResults = store.search("Rectangle");
    ASSERT_EQ(searchResults.size(), 1);
    ASSERT_EQ(searchResults[0]->name(), "Rectangle");
    ASSERT_EQ(searchResults[0]->m_type, CClangParser::ObjectType::Class);
    ASSERT_EQ(searchResults[0]->m_location.file, "shape/Rectangle.h");

    searchResults = store.search("shape");
    ASSERT_TRUE(searchResults.empty());
}

TEST(CClangSymbolsInMemoryDB_UnitTests, Case_Sensitivity)
{
    CClangSymbolsInMemoryDB store;
    store.add(
        std::make_shared<CClangParser::CObjectInfo>(
            "Shape", CClangParser::ObjectType::GlobalFunction, "testfile"));

    auto searchResults {store.search("shape")};
    ASSERT_TRUE(searchResults.empty());

    store.add(
        std::make_shared<CClangParser::CObjectInfo>(
            "shape", CClangParser::ObjectType::GlobalFunction, "shapeFile.cpp"));
    auto results {store.search("shape")};
    ASSERT_EQ(results.size(), 1);
    ASSERT_EQ(results[0]->m_location.file, "shapeFile.cpp");
}
