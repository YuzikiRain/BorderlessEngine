cmake_minimum_required(VERSION 3.5)
project(borderlessengine_runtime)

add_library(borderlessengine_runtime STATIC ${PROJECT_SOURCE_DIR}/BorderlessEngine.cpp)
target_include_directories(borderlessengine_runtime PUBLIC ${PROJECT_SOURCE_DIR})
message(STATUS "qqqqqqqqqq ${PROJECT_SOURCE_DIR}/BorderlessEngine.cpp")