cmake_minimum_required(VERSION 3.16)

project(gintel)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(gintel
    src/main.cpp
	src/CClangParser.cpp
	src/CGintelEngine.cpp
	src/CSourceEnumerator.cpp
	src/CClangUtil.cpp
	)

execute_process(COMMAND llvm-config --includedir OUTPUT_VARIABLE INCLUDE_DIR OUTPUT_STRIP_TRAILING_WHITESPACE)
execute_process(COMMAND llvm-config --libdir OUTPUT_VARIABLE LIBRARIES_DIR OUTPUT_STRIP_TRAILING_WHITESPACE)

target_include_directories(gintel PUBLIC ${INCLUDE_DIR})

find_library(
	CLANG_LIB
	NAME clang
	PATHS ${LIBRARIES_DIR}
	)

target_link_libraries(
	gintel
	PUBLIC
	${CLANG_LIB}
	)
