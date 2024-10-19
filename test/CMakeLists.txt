cmake_minimum_required(VERSION 3.22)
PROJECT(UriTest)

SET(SOURCE 
    ${CMAKE_SOURCE_DIR}/test/UriTest.cpp
)
add_executable(${PROJECT_NAME} ${SOURCE})

set_target_properties(${PROJECT_NAME} PROPERTIES
    FOLDER Tests
)
enable_testing()
find_package(GTest REQUIRED)
target_link_libraries(${PROJECT_NAME} PUBLIC 
    GTest::gtest GTest::gtest_main
    Uri
)

target_include_directories(${PROJECT_NAME} PRIVATE
    GTEST_INCLUDE_DIRS
    ${CMAKE_SOURCE_DIR}/incude/
    ${CMAKE_SOURCE_DIR}/src/
)
gtest_discover_tests(${PROJECT_NAME})