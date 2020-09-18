cmake_minimum_required(VERSION 3.16)

set(LIBRARY ${CMAKE_PROJECT_NAME})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SOURCES
	CClangParser.cpp
	CGintelEngine.cpp
	CSourceEnumerator.cpp
	CClangUtil.cpp
	CObjectStore.cpp
	CClangSymbolsInMemoryDB.cpp
	CObjectIndex.cpp
	CCamelCaseKeyGenerator.cpp
	CSymbolInfo.cpp
	IGintelEngine.cpp)

add_library(${LIBRARY} SHARED ${SOURCES})

find_library(CLANG_LIB NAME clang)
target_link_libraries(${LIBRARY} PUBLIC ${CLANG_LIB})
