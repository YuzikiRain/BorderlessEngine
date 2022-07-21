cmake_minimum_required(VERSION 3.5)
project(borderlessengine_runtime)


# set (PROJECT_LIBRARIES)
set(PROJECT_INCLUDE)
set(PROJECT_SOURCE)
set(PACKAGE_PATH ${CMAKE_SOURCE_DIR}/packages)

list(APPEND PROJECT_INCLUDE ${PROJECT_SOURCE_DIR})
list(APPEND PROJECT_INCLUDE ${PACKAGE_PATH})
list(APPEND PROJECT_SOURCE ${PROJECT_SOURCE_DIR}/BorderlessEngine.cpp)

# GLFW
set(GLFW_PATH ${PACKAGE_PATH}/GLFW)
set(GLFW_INCLUDE ${GLFW_PATH}/include)
set(GLFW_LIB ${GLFW_PATH}/lib/glfw3dll.lib)
# list(APPEND PROJECT_INCLUDE ${GLFW_INCLUDE})
# list(APPEND PROJECT_LIBRARIES ${GLFW_LIB})

# glad
set(GLAD_PATH ${PACKAGE_PATH}/glad)
set(GLAD_INCLUDE ${GLAD_PATH})
set(GLAD_SRC ${GLAD_PATH})
# list(APPEND PROJECT_INCLUDE ${GLAD_INCLUDE})
list(APPEND PROJECT_SOURCE ${GLAD_SRC}/glad.c)

# 模块
file ( GLOB_RECURSE Module_SOURCE true RELATIVE ${PROJECT_SOURCE_DIR} *.cpp )
message( STATUS "Files are ${PROJECT_SOURCE}" )


add_library(${PROJECT_NAME} STATIC ${Module_SOURCE} ${PROJECT_SOURCE})
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_INCLUDE})
target_link_libraries(${PROJECT_NAME} PRIVATE ${GLFW_LIB})

# find_package(GLFW3 REQUIRED)
# if(GLFW3_FOUND)
# message(STATUS "Found GLFW3 in ${GLFW3_INCLUDE_DIR}")
#     target_include_directories(${PROJECT_NAME} PRIVATE ${GLFW3_INCLUDE_DIR})
#     target_link_libraries(glfw3 ${GLFW3_LIBRARY})
# else(GLFW3_FOUND)
#     message(FATAL_ERROR "GLFW3 not found")
# endif(GLFW3_FOUND)