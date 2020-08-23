set(BINARY ${CMAKE_PROJECT_NAME}_test)

set(SOURCES
    testmain.cpp
    CObjectStore_UnitTests.cpp
    CObjectIndex_UnitTests.cpp
    CClangSymbolsInMemoryDB_UnitTests.cpp
    CCamelCaseKeyGenerator_UnitTests.cpp
)

add_executable(${BINARY} ${SOURCES})

add_test(NAME ${BINARY} COMMAND ${BINARY})

target_link_libraries(${BINARY} PUBLIC ${CMAKE_PROJECT_NAME}_lib gtest)