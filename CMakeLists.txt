cmake_minimum_required(VERSION 3.16)

set(CMAKE_PROJECT_NAME gintel)
project(${CMAKE_PROJECT_NAME})

set(CMAKE_CXX_STANDARD 17)
set(ADDITIONAL_INCLUDE_DIR "/usr/local/include")
set(ADDITIONAL_LIBRARY_DIR "/usr/local/lib")
set(PROJECT_INCLUDE_DIR "${CMAKE_BINARY_DIR}/src/include")
set(PROJECT_BUILD_DIR "${CMAKE_BINARY_DIR}/build")

add_custom_target(build-time-make-directory ALL
    COMMAND ${CMAKE_COMMAND} -E make_directory ${PROJECT_BUILD_DIR})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BUILD_DIR})	#	binary path
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BUILD_DIR})	#	.so path
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BUILD_DIR})	#	.a path

execute_process(COMMAND llvm-config --libdir OUTPUT_VARIABLE LLVM_LIB_DIR OUTPUT_STRIP_TRAILING_WHITESPACE)
execute_process(COMMAND llvm-config --includedir OUTPUT_VARIABLE LLVM_INCLUDE_DIR OUTPUT_STRIP_TRAILING_WHITESPACE)

include_directories(src/gintel ${ADDITIONAL_INCLUDE_DIR} ${PROJECT_INCLUDE_DIR} ${LLVM_INCLUDE_DIR})
link_directories(${ADDITIONAL_LIBRARY_DIR} ${LLVM_LIB_DIR})

add_subdirectory(src/gintel)
add_subdirectory(src/testapp)
add_subdirectory(tests)
