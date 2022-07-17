cmake_minimum_required(VERSION 3.5)
project(borderless_engine)

set(STATIC_BORDERLESSENGINE_RUNTIME_LIB_SOURCES Sources/BorderlessEngine.cpp)
set(EXE_SOURCES main.cpp)

add_library(hello_static_library SHARED ${STATIC_BORDERLESSENGINE_RUNTIME_LIB_SOURCES})
target_include_directories(hello_static_library PUBLIC ${PROJECT_SOURCE_DIR}/Sources)

add_executable(BorderlessEngine ${EXE_SOURCES})

target_include_directories(BorderlessEngine PRIVATE ${PROJECT_SOURCE_DIR}/Sources)
target_link_libraries(BorderlessEngine PRIVATE hello_static_library)

MESSAGE( STATUS "CMAKE_SOURCE_DIR}/Sources/Runtime ${CMAKE_SOURCE_DIR}/Sources/Runtime")