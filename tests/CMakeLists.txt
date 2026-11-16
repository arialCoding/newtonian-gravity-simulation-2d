add_executable(testVector test_vector.c)

target_link_libraries(testVector PRIVATE core)

add_test(NAME VectorLogicTest COMMAND testVector)