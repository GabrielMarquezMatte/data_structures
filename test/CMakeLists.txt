add_executable(${PROJECT_NAME}_test test.c)
target_link_libraries(${PROJECT_NAME}_test PRIVATE ${PROJECT_NAME})
target_include_directories(${PROJECT_NAME}_test PRIVATE ${CMAKE_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR})

add_test(NAME Vector_Test COMMAND ${PROJECT_NAME}_test 100 -v)
add_test(NAME Hash_Test COMMAND ${PROJECT_NAME}_test 100 --hash)
add_test(NAME Set_Test COMMAND ${PROJECT_NAME}_test 100 --set)
add_test(NAME Hash_Vector_Test COMMAND ${PROJECT_NAME}_test 100 --hash_vector)