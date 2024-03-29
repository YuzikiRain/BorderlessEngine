cmake_minimum_required(VERSION 3.5)
project(${borderlessengine_runtime})

set(PROJECT_LIBRARIES)
set(PROJECT_INCLUDE)
set(PROJECT_SOURCE)
set(PACKAGE_PATH ${CMAKE_SOURCE_DIR}/ThirdParty)
set(PACKAGE_INCLUDE_PATH ${PACKAGE_PATH}/Include)
set(PACKAGE_SOURCE_PATH ${PACKAGE_PATH}/Source)
set(PACKAGE_LIBRARY_PATH ${PACKAGE_PATH}/Library)
set(BORDERLESSENGINE_EDITOR ${CMAKE_SOURCE_DIR}/Sources/Editor)

list(APPEND PROJECT_INCLUDE ${PROJECT_SOURCE_DIR})
list(APPEND PROJECT_INCLUDE ${BORDERLESSENGINE_EDITOR})
list(APPEND PROJECT_INCLUDE ${PACKAGE_INCLUDE_PATH})

# GLFW
set(GLFW_LIB ${PACKAGE_LIBRARY_PATH}/GLFW/glfw3dll.lib)
list(APPEND PROJECT_LIBRARIES ${GLFW_LIB})

# glad
set(GLAD_INCLUDE ${PACKAGE_INCLUDE_PATH}/glad)
set(GLAD_SRC ${PACKAGE_SOURCE_PATH}/glad)
list(APPEND PROJECT_SOURCE ${GLAD_SRC}/glad.c)

# assimp
set(ASSIMP_LIB ${PACKAGE_LIBRARY_PATH}/assimp/libassimp.dll)
# set(ASSIMP_LIB ${PACKAGE_LIBRARY_PATH}/assimp/assimp-vc142-mtd.lib)
# set(ASSIMP_LIB ${PACKAGE_LIBRARY_PATH}/assimp/assimp-vc142-mtd.dll)
# set(ASSIMP_LIB ${PACKAGE_LIBRARY_PATH}/assimp/assimp-vc140-mt.dll)
# set(ASSIMP_LIB ${PACKAGE_LIBRARY_PATH}/assimp/libassimp-5.dll)
list(APPEND PROJECT_LIBRARIES ${ASSIMP_LIB})

# stb_image
list(APPEND PROJECT_INCLUDE ${PACKAGE_INCLUDE_PATH}/stb-image)
list(APPEND PROJECT_INCLUDE ${PACKAGE_INCLUDE_PATH}/stb-image/)

# rttr
file(GLOB_RECURSE RTTR_SOURCE ${PACKAGE_INCLUDE_PATH}/rttr/*.cpp)
list(APPEND PROJECT_LIBRARIES ${PACKAGE_LIBRARY_PATH}/rttr/librttr_core.dll)
list(APPEND PROJECT_INCLUDE ${PACKAGE_INCLUDE_PATH}/rttr)
file(GLOB_RECURSE BORDERLESSENGINE_RUNTIME_SOURCE ${RTTR_SOURCE})
# message(${RTTR_SOURCE})

#other
file(GLOB_RECURSE BORDERLESSENGINE_RUNTIME_SOURCE ${PROJECT_SOURCE}/*.cpp)
list(APPEND PROJECT_SOURCE ${BORDERLESSENGINE_RUNTIME_SOURCE})

add_library(${PROJECT_NAME} STATIC ${PROJECT_SOURCE})
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_INCLUDE})
target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_LIBRARIES})

# find_package(GLFW3 REQUIRED)
# if(GLFW3_FOUND)
# message(STATUS "Found GLFW3 in ${GLFW3_INCLUDE_DIR}")
#     target_include_directories(${PROJECT_NAME} PRIVATE ${GLFW3_INCLUDE_DIR})
#     target_link_libraries(glfw3 ${GLFW3_LIBRARY})
# else(GLFW3_FOUND)
#     message(FATAL_ERROR "GLFW3 not found")
# endif(GLFW3_FOUND)