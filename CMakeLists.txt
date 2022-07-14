cmake_minimum_required(VERSION 3.5)
project(BorderlessEngineProject VERSION 0.1.0)

add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/BorderlessEngine/Runtime borderless_engine_runtime)
add_subdirectory(borderless_engine_editor)