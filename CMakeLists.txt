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

target_include_directories(gintel PUBLIC "/usr/lib/llvm-10/include")

find_library(CLANG_LIB clang HINTS "/usr/lib/llvm-10/lib") 

target_link_libraries(gintel
		PRIVATE
		${CLANG_LIB}
		)
