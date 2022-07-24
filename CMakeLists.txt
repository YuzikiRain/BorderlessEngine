cmake_minimum_required(VERSION 3.5)
project(borderlessengine)

set(PACKAGE_PATH ${CMAKE_SOURCE_DIR}/Packages)

# runtime
set(borderlessengine_runtime borderlessengine_runtime)
set(borderlessengine_runtime_directory ${PROJECT_SOURCE_DIR}/Sources/Runtime)
add_subdirectory(${PROJECT_SOURCE_DIR}/Sources/Runtime)
# editor
set(borderlessengine_editor borderlessengine_editor)
set(borderlessengine_editor_directory ${PROJECT_SOURCE_DIR}/Sources/Editor)
add_subdirectory(${PROJECT_SOURCE_DIR}/Sources/Editor)

set(EXE_SOURCES main.cpp)

add_executable(LaunchBorderlessEngine ${EXE_SOURCES})
# runtime
target_include_directories(LaunchBorderlessEngine PUBLIC ${borderlessengine_runtime_directory})
target_link_libraries(LaunchBorderlessEngine PRIVATE ${borderlessengine_runtime})
# editor
target_include_directories(LaunchBorderlessEngine PUBLIC ${borderlessengine_editor_directory})
target_link_libraries(LaunchBorderlessEngine PRIVATE ${borderlessengine_editor})