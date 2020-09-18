cmake_minimum_required(VERSION 3.16)

set(BINARY ${CMAKE_PROJECT_NAME}_testapp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SOURCES
	main.cpp)

add_executable(${BINARY} ${SOURCES})

set(GINTEL_LIB ${CMAKE_PROJECT_NAME})
#target_link_libraries(${BINARY} PUBLIC ${CLANG_LIB})
target_link_libraries(${BINARY} PUBLIC ${GINTEL_LIB})
