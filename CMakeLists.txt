cmake_minimum_required(VERSION 3.5)
project(borderlessengine)

set(borderlessengine_directory ${PROJECT_SOURCE_DIR}/Sources)
# MESSAGE( STATUS "${PROJECT_SOURCE_DIR}/Sources ${PROJECT_SOURCE_DIR}/Sources")
add_subdirectory(${borderlessengine_directory})

set(STATIC_BORDERLESSENGINE_RUNTIME_LIB_SOURCES Sources/BorderlessEngine.cpp)
set(EXE_SOURCES main.cpp)

add_executable(LaunchBorderlessEngine ${EXE_SOURCES})
target_link_libraries(LaunchBorderlessEngine PUBLIC borderlessengine_runtime)
target_include_directories(LaunchBorderlessEngine PUBLIC ${borderlessengine_directory})