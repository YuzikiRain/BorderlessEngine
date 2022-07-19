cmake_minimum_required(VERSION 3.5)
project(borderlessengine_runtime)

add_library(borderlessengine_runtime STATIC ${PROJECT_SOURCE_DIR}/BorderlessEngine.cpp)
target_compile_definitions(borderlessengine_runtime PRIVATE BUILD_DLL)
target_include_directories(borderlessengine_runtime PUBLIC ${PROJECT_SOURCE_DIR})
target_include_directories(borderlessengine_runtime PUBLIC ${CMAKE_SOURCE_DIR}/lib)
set(LIBS glfw3)
set( _glfw3_LIB_SEARCH_DIRS
"/usr/lib"
"/usr/local/lib"
"${CMAKE_SOURCE_DIR}/lib"
"C:/Program Files (x86)/glfw/lib-msvc110" )
FIND_LIBRARY(GLFW3_LIBRARY NAMES glfw3 glfw
PATHS ${_glfw3_LIB_SEARCH_DIRS} )
find_package(GLFW3 REQUIRED)
message(STATUS "Found GLFW3 in ${GLFW3_INCLUDE_DIR}")
target_link_libraries(borderlessengine_runtime ${LIBS})
message(STATUS "qqqqqqqqqq ${CMAKE_SOURCE_DIR}/lib")