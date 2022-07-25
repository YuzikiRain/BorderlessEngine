# yaml-cpp
project (yaml-cpp LANGUAGES CXX )

set(PACKAGE_PATH ${CMAKE_SOURCE_DIR}/Packages)
set(PACKAGE_INCLUDE_PATH ${PACKAGE_PATH}/Include)
set(PACKAGE_LIBRARY_PATH ${PACKAGE_PATH}/Library)

# include path
list(APPEND PROJECT_INCLUDE ${PACKAGE_INCLUDE_PATH}/yaml-cpp)
list(APPEND PROJECT_LIBRARIES ${PACKAGE_LIBRARY_PATH}/yaml-cpp/yaml-cppd.lib)

# add_library( ${PROJECT_NAME} STATIC ${PROJECT_SOURCE} )
add_library( ${PROJECT_NAME} STATIC ${CMAKE_CURRENT_SOURCE_DIR}/yaml.h )

target_include_directories ( ${PROJECT_NAME}
        PUBLIC 
        ${PROJECT_INCLUDE}
)

target_link_libraries(${PROJECT_NAME} PUBLIC ${PROJECT_LIBRARIES})