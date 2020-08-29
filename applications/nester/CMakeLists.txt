CMAKE_MINIMUM_REQUIRED(VERSION 3.10)

project(nester)

add_executable(nester main_nester.cpp  nester_geometry.cpp convexpolygonselector.cpp convexpolygonplacer.cpp convexpolygonnester.cpp)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND cp ${PROJECT_BINARY_DIR}/${PROJECT_NAME}  ${CMAKE_BINARY_DIR}/bin/${PROJECT_NAME}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMENT "Copying ${PROJECT_NAME} to binary directory"
        )

target_sources(nester
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/nester.h
        ${CMAKE_CURRENT_LIST_DIR}/nester_geometry.h
        ${CMAKE_CURRENT_LIST_DIR}/convexpolygonselector.h
        ${CMAKE_CURRENT_LIST_DIR}/convexpolygonplacer.h
        ${CMAKE_CURRENT_LIST_DIR}/convexpolygonnester.h
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/main_nester.cpp
        ${CMAKE_CURRENT_LIST_DIR}/nester_geometry.cpp
        ${CMAKE_CURRENT_LIST_DIR}/nester.cpp
        ${CMAKE_CURRENT_LIST_DIR}/convexpolygonselector.cpp
        ${CMAKE_CURRENT_LIST_DIR}/convexpolygonplacer.cpp
        ${CMAKE_CURRENT_LIST_DIR}/convexpolygonnester.cpp
)

target_link_libraries(nester cvs_utils corecvs)
target_include_directories(nester PUBLIC ${corecvs_SOURCE_DIR} ${cvs_utils_SOURCE_DIR} .)
