#include <vector>
#include <memory>
#include "gtest/gtest.h"
#include "IStoreObject.h"
#include "CObjectStore.h"
#include "CClangParser.h"
#include "CSymbolInfo.h"

using gintel::storage::CObjectStore;
using gintel::storage::CSymbolInfo;
using gintel::storage::IStoreObject;
using gintel::storage::SymbolType;
using gintel::modules::CClangParser;

std::vector<std::shared_ptr<CSymbolInfo>> addDummyObjectStoreEntries()
{
    std::vector<std::shared_ptr<CSymbolInfo>> result;

    auto createObject {[](const std::string& name, SymbolType type, const std::filesystem::path& filePath) {
        return std::make_shared<CSymbolInfo>("Shape", name, type, filePath);
    }};

    result.push_back(createObject("Shape", SymbolType::Class, "shape/Shape.h"));
    result.push_back(createObject("Shape::Draw", SymbolType::Method, "shape/Shape.h"));
    result.push_back(createObject("Shape::Size", SymbolType::Method, "shape/Shape.h"));
    result.push_back(createObject("createShapeInstance", SymbolType::GlobalFunction, "shape/Shape.cpp"));
    result.push_back(createObject("Rectangle", SymbolType::Class, "shape/Rectangle.h"));

    return result;
}

TEST(CObjectStore_UnitTest, Input_Validations)
{
    CObjectStore store;
    ASSERT_THROW(store.add(std::shared_ptr<IStoreObject>()), std::invalid_argument);
}

TEST(CObjectStore_UnitTest, Basic_Add_and_Fetch_Test)
{
    std::vector<std::any> objectIds;
    CObjectStore obStore;

    auto entries {addDummyObjectStoreEntries()};
    std::for_each(entries.begin(), entries.end(), [&](const auto entry) {
        objectIds.push_back(
            obStore.add(
                std::dynamic_pointer_cast<IStoreObject>(
                    entry)
                    ));
    });

    auto index {0};

    std::for_each(objectIds.begin(), objectIds.end(), [&](const std::any objectId) {
        auto object {obStore.get(objectId)};

        auto left {entries[index].get()};
        auto right {std::dynamic_pointer_cast<CSymbolInfo>(object).get()};

        ASSERT_TRUE(*left == *right);

        index++;
    });
}

TEST(CObjectStore_UnitTest, Invalid_Object_Id_Test)
{
    CObjectStore obStore;
    auto entries {addDummyObjectStoreEntries()};

    auto objectId {obStore.add(entries[0])};

    ASSERT_THROW(obStore.get(2), std::bad_any_cast);
    ASSERT_THROW(obStore.get(entries[0]->name()), std::bad_any_cast);
    ASSERT_THROW(obStore.get(entries[0]), std::bad_any_cast);
    ASSERT_THROW(obStore.get(entries[0].get()), std::bad_any_cast);
}

TEST(CObjectStore_UnitTest, Removal_Test)
{
    CObjectStore obStore;
    auto entries {addDummyObjectStoreEntries()};

    auto objectId {obStore.add(entries[0])};
    ASSERT_THROW(obStore.remove(objectId), std::bad_function_call);
}
