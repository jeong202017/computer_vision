cmake_minimum_required(VERSION 3.10)
project(opencv_test)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenCV REQUIRED)

add_executable(assignment5-1 Assignment_5th_1.cpp)
add_executable(assignment5-2 Assignment_5th_2.cpp)
add_executable(assignment5-3 Assignment_5th_3.cpp)
add_executable(assignment5-4 Assignment_5th_4.cpp)
# add_executable(assignment4-5 Assignment_4th_5.cpp)


target_link_libraries(assignment5-1 ${OpenCV_LIBS})
target_include_directories(assignment5-1 PUBLIC ${OpenCV_LIBS})
target_link_libraries(assignment5-2 ${OpenCV_LIBS})
target_include_directories(assignment5-2 PUBLIC ${OpenCV_LIBS})
target_link_libraries(assignment5-3 ${OpenCV_LIBS})
target_include_directories(assignment5-3 PUBLIC ${OpenCV_LIBS})
target_link_libraries(assignment5-4 ${OpenCV_LIBS})
target_include_directories(assignment5-4 PUBLIC ${OpenCV_LIBS})