cmake_minimum_required(VERSION 3.16)

project(mygame LANGUAGES CXX   VERSION 0.1.0)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
include_directories(include ${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})

add_subdirectory(src)
target_link_libraries(app.out ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARY})
set_target_properties(app.out PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")