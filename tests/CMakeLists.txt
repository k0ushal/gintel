set(BINARY ${CMAKE_PROJECT_NAME}_tst)

set(SOURCES
    testmain.cpp
    DummyTest.cpp
    CObjectStore_UnitTest.cpp
    CObjectIndex_UnitTest.cpp
)

add_executable(${BINARY} ${SOURCES})

add_test(NAME ${BINARY} COMMAND ${BINARY})

target_link_libraries(${BINARY} PUBLIC ${CMAKE_PROJECT_NAME}_lib gtest)