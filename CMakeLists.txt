cmake_minimum_required(VERSION 3.5)
project(borderlessengine)

set(borderlessengine_directory ${PROJECT_SOURCE_DIR}/Sources)
# MESSAGE( STATUS "${PROJECT_SOURCE_DIR}/Sources ${PROJECT_SOURCE_DIR}/Sources")
add_subdirectory(${borderlessengine_directory})

set(EXE_SOURCES main.cpp)

add_executable(LaunchBorderlessEngine ${EXE_SOURCES})
target_include_directories(LaunchBorderlessEngine PUBLIC ${borderlessengine_directory})
target_link_libraries(LaunchBorderlessEngine PRIVATE borderlessengine_runtime)