#include <vector>
#include <memory>
#include <filesystem>
#include "gtest/gtest.h"
#include "IStoreObject.h"
#include "CClangSymbolsInMemoryDB.h"
#include "CSymbolInfo.h"

using gintel::storage::CSymbolInfo;
using gintel::storage::IStoreObject;
using gintel::storage::SymbolType;
using gintel::storage::CClangSymbolsInMemoryDB;

std::vector<std::shared_ptr<CSymbolInfo>> createDummyInMemoryDBEntries()
{
    std::vector<std::shared_ptr<CSymbolInfo>> result;

    auto createObject {[](
        const std::string& name,
        SymbolType type,
        const std::filesystem::path& filePath) {

        return std::make_shared<CSymbolInfo>(
                "Shape", name, type, filePath);
    }};

    result.push_back(createObject("Shape", SymbolType::Class, "shape/Shape.h"));
    result.push_back(createObject("Shape::Size", SymbolType::Method, "shape/Shape.h"));
    result.push_back(createObject("createShapeInstance", SymbolType::GlobalFunction, "shape/Shape.cpp"));
    result.push_back(createObject("Rectangle", SymbolType::Class, "shape/Rectangle.h"));

    return result;
}

TEST(CClangSymbolsInMemoryDB_UnitTests, Input_Validations)
{
    CClangSymbolsInMemoryDB store;
    ASSERT_THROW(store.add(std::shared_ptr<CSymbolInfo>()), std::invalid_argument);
}

TEST(CClangSymbolsInMemoryDB_UnitTests, Simple_Search)
{
    auto dummyObjects {createDummyInMemoryDBEntries()};
    CClangSymbolsInMemoryDB store;

    std::for_each(dummyObjects.begin(), dummyObjects.end(),
        [&](std::shared_ptr<CSymbolInfo> object) {
            store.add(object);
        });

    auto result {store.search("Shape")};
    ASSERT_EQ(result.size(), 3);
    ASSERT_EQ(result[0]->m_name, "Shape");
}

TEST(CClangSymbolsInMemoryDB_UnitTests, Multiple_Keys)
{
    auto dummyObjects {createDummyInMemoryDBEntries()};
    CClangSymbolsInMemoryDB store;

    std::for_each(dummyObjects.begin(), dummyObjects.end(),
        [&](std::shared_ptr<CSymbolInfo> object) {
            store.add(object);
        });

    //  Shape
    auto searchResults {store.search("Shape")};
    ASSERT_EQ(searchResults.size(), 3);

    ASSERT_EQ(
        *searchResults[0],
        CSymbolInfo(
            "Shape", "Shape", SymbolType::Class, "shape/Shape.h"));

    ASSERT_EQ(
        *searchResults[1],
        CSymbolInfo(
            "Shape", "Shape::Size", SymbolType::Method, "shape/Shape.h"));

    ASSERT_EQ(
        *searchResults[2],
        CSymbolInfo(
            "Shape", "createShapeInstance", SymbolType::GlobalFunction, "shape/Shape.cpp"));

    //  createShapeInstance
    searchResults = store.search("create");
    ASSERT_EQ(searchResults.size(), 1);

    ASSERT_EQ(
        *searchResults[0],
        CSymbolInfo(
            "Shape", "createShapeInstance", SymbolType::GlobalFunction, "shape/Shape.cpp"));
}

TEST(CClangSymbolsInMemoryDB_UnitTests, Case_Sensitivity)
{
    CClangSymbolsInMemoryDB store;
    store.add(
        std::make_shared<CSymbolInfo>(
            "Shape", "Shape", SymbolType::Class, "testfile"));

    auto searchResults {store.search("shape")};
    ASSERT_EQ(searchResults.size(), 1);
    ASSERT_EQ(*searchResults[0], CSymbolInfo(
            "Shape", "Shape", SymbolType::Class, "testfile"));

    store.add(
        std::make_shared<CSymbolInfo>(
            "Shape", "createShapeInstance", SymbolType::GlobalFunction, "shapeFile.cpp"));

    auto results {store.search("Shape")};
    ASSERT_EQ(results.size(), 2);
    ASSERT_EQ(results[0]->m_location.file, "testfile");
    ASSERT_EQ(results[1]->m_name, "createShapeInstance");
}
