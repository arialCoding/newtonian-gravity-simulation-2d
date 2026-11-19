add_library(core STATIC
    core/object.c
    core/vector.c
    core/force.c
    core/calculations.c
    core/world.c

    core/object.h
    core/vector.h
    core/force.h
    core/color.h
    core/calculations.h
    ${PROJECT_SOURCE_DIR}/include/GRV/world.h
)

target_include_directories(core PUBLIC 
    "${PROJECT_SOURCE_DIR}/include"
    "${RAYLIB_INCLUDE_DIR}"
)

target_link_directories(core PUBLIC 
    "${RAYLIB_LIB_DIR}"
)

target_link_libraries(core PUBLIC raylib m)


add_executable(${PROJECT_NAME} main.c)

target_link_libraries(${PROJECT_NAME} PRIVATE core)