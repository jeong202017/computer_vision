cmake_minimum_required(VERSION 3.10)
project(opencv_test)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenCV REQUIRED)

add_executable(Assignment_5th_1 Assignment_5th_1.cpp)
# add_executable(assignment4-2 Assignment_4th_2.cpp)
# add_executable(assignment4-3 Assignment_4th_3.cpp)
# add_executable(assignment4-4 Assignment_4th_4.cpp)
# add_executable(assignment4-5 Assignment_4th_5.cpp)


target_link_libraries(assignment5-1 ${OpenCV_LIBS})
target_include_directories(assignment5-1 PUBLIC ${OpenCV_LIBS})

