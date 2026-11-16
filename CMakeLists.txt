cmake_minimum_required(VERSION 4.3.0 )

project(GRAVITY)

set(INCLUDE_DIR
    ${CMAKE_HOME_DIRECTORY}/include
    ${CMAKE_HOME_DIRECTORY}/vendor/RAYLIB/include
)

set(LINK_DIR
    ${CMAKE_HOME_DIRECTORY}/vendor/RAYLIB/lib
)

set(LINK_LIB
    raylib
)

add_executable(${PROJECT_NAME} src/main.c)

target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDE_DIR})
target_link_directories(${PROJECT_NAME} PRIVATE ${LINK_DIR})
target_link_libraries(${PROJECT_NAME} PRIVATE ${LINK_LIB})
