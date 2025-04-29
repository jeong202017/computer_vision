cmake_minimum_required(VERSION 3.10)
project(opencv_test)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenCV REQUIRED)

add_executable(assignment7-1 Assignment_7th_1.cpp)
add_executable(assignment7-2 Assignment_7th_2.cpp)


target_link_libraries(assignment7-1 ${OpenCV_LIBS})
target_include_directories(assignment7-1 PUBLIC ${OpenCV_LIBS})

target_link_libraries(assignment7-2 ${OpenCV_LIBS})
target_include_directories(assignment7-2 PUBLIC ${OpenCV_LIBS})