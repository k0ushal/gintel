cmake_minimum_required(VERSION 3.16)

set(BINARY ${CMAKE_PROJECT_NAME})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SOURCES
	main.cpp
	CClangParser.cpp
	CGintelEngine.cpp
	CSourceEnumerator.cpp
	CClangUtil.cpp
	CObjectStore.cpp
	CClangSymbolsInMemoryDB.cpp
	CObjectIndex.cpp
	CCamelCaseKeyGenerator.cpp)

add_executable(${BINARY} ${SOURCES})
add_library(${BINARY}_lib STATIC ${SOURCES})

find_library(CLANG_LIB NAME clang)

target_link_libraries(${BINARY} PUBLIC ${CLANG_LIB})
