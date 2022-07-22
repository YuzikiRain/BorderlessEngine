cmake_minimum_required(VERSION 3.5)
project(borderlessengine)

# # try conditional compilation
# include(CheckCXXCompilerFlag)
# CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
# CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)

# # check results and add flag
# if(COMPILER_SUPPORTS_CXX11)#
#     set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
# elseif(COMPILER_SUPPORTS_CXX0X)#
#     set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
# else()
#     message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
# endif()

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