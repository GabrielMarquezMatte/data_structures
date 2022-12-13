cmake_minimum_required(VERSION 3.22.0)
project(structures VERSION 0.1.0 LANGUAGES C)

include(CTest)
enable_testing()

add_subdirectory(include)

add_library(${PROJECT_NAME} structures.c structures.h)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(${PROJECT_NAME} PRIVATE vector_type string_type hash_table)

add_subdirectory(test)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
