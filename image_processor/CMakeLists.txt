cmake_minimum_required(VERSION 3.10)
project(image_processor)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "src/*.cpp")
list(REMOVE_ITEM SOURCES "image_processor.cpp")
add_library(libimageprocessor ${SOURCES})
target_include_directories(libimageprocessor PUBLIC include)

add_executable(image_processor image_processor.cpp)
target_link_libraries(image_processor libimageprocessor)

option(BUILD_TESTS "Build unit tests" ON)

if(BUILD_TESTS)
    enable_testing()

    add_executable(test_color tests/test_color.cpp)
    target_link_libraries(test_color libimageprocessor)
    target_include_directories(test_color PRIVATE include)
    add_test(NAME ColorTests COMMAND test_color)

    add_executable(test_image tests/test_image.cpp)
    target_link_libraries(test_image libimageprocessor)
    target_include_directories(test_image PRIVATE include)
    add_test(NAME ImageTests COMMAND test_image)
endif()