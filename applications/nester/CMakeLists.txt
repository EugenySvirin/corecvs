CMAKE_MINIMUM_REQUIRED(VERSION 3.10)

project(nester)
include_directories(include)

add_executable(nester main_nester.cpp NesterCore/nester_geometry.cpp NesterCore/convexpolygonselector.cpp NesterCore/convexpolygonplacer.cpp
    NesterCore/convexpolygonnester.cpp nesterhelpfulmethods.cpp Tests/nestertests.cpp)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND cp ${PROJECT_BINARY_DIR}/${PROJECT_NAME}  ${CMAKE_BINARY_DIR}/bin/${PROJECT_NAME}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMENT "Copying ${PROJECT_NAME} to binary directory"
        )

target_sources(nester
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/LegacyCode/nester.h
        ${CMAKE_CURRENT_LIST_DIR}/NesterCore/nester_geometry.h
        ${CMAKE_CURRENT_LIST_DIR}/NesterCore/convexpolygonselector.h
        ${CMAKE_CURRENT_LIST_DIR}/NesterCore/convexpolygonplacer.h
        ${CMAKE_CURRENT_LIST_DIR}/NesterCore/convexpolygonnester.h
        ${CMAKE_CURRENT_LIST_DIR}/nesterhelpfulmethods.h
        ${CMAKE_CURRENT_LIST_DIR}/Tests/NesterTests.h
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/main_nester.cpp
        ${CMAKE_CURRENT_LIST_DIR}/NesterCore/nester_geometry.cpp
        ${CMAKE_CURRENT_LIST_DIR}/LegacyCode/nester.cpp
        ${CMAKE_CURRENT_LIST_DIR}/NesterCore/convexpolygonselector.cpp
        ${CMAKE_CURRENT_LIST_DIR}/NesterCore/convexpolygonplacer.cpp
        ${CMAKE_CURRENT_LIST_DIR}/NesterCore/convexpolygonnester.cpp
        ${CMAKE_CURRENT_LIST_DIR}/nesterhelpfulmethods.cpp
        ${CMAKE_CURRENT_LIST_DIR}/Tests/nestertests.cpp
)

target_link_libraries(nester cvs_utils corecvs)
target_include_directories(nester PUBLIC ${corecvs_SOURCE_DIR} ${cvs_utils_SOURCE_DIR} .)
