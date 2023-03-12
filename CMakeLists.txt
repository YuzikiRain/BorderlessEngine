cmake_minimum_required(VERSION 3.5)
project(borderlessengine)

# #c++ standard
# set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_STANDARD_REQUIRED True)

set(PACKAGE_PATH ${CMAKE_SOURCE_DIR}/Packages)

# runtime
set(borderlessengine_runtime borderlessengine_runtime)
set(borderlessengine_runtime_directory ${PROJECT_SOURCE_DIR}/Sources/Runtime)
add_subdirectory(${PROJECT_SOURCE_DIR}/Sources/Runtime)
# editor
set(borderlessengine_editor borderlessengine_editor)
set(borderlessengine_editor_directory ${PROJECT_SOURCE_DIR}/Sources/Editor)
add_subdirectory(${PROJECT_SOURCE_DIR}/Sources/Editor)

# exe
set(EXE_SOURCES main.cpp)
add_executable(LaunchBorderlessEngine ${EXE_SOURCES})

# 链接runtime
target_include_directories(LaunchBorderlessEngine PUBLIC ${borderlessengine_runtime_directory})
target_link_libraries(LaunchBorderlessEngine PRIVATE ${borderlessengine_runtime})
# 链接editor
target_include_directories(LaunchBorderlessEngine PUBLIC ${borderlessengine_editor_directory})
target_link_libraries(LaunchBorderlessEngine PRIVATE ${borderlessengine_editor})

# 拷贝dll
file(GLOB_RECURSE allCopyFiles ${CMAKE_SOURCE_DIR}/ThirdParty *.dll)
message(${allCopyFiles})
file(COPY ${allCopyFiles} DESTINATION ${CMAKE_BINARY_DIR})