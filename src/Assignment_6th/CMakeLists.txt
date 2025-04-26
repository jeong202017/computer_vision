cmake_minimum_required(VERSION 3.10)
project(opencv_test)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenCV REQUIRED)

add_executable(assignment6-1 Assignment_6th_1.cpp)
add_executable(assignment6-2 Assignment_6th_2.cpp)
add_executable(assignment6-3 Assignment_6th_3.cpp)
add_executable(assignment6-4 Assignment_6th_4.cpp)
add_executable(assignment6-5 Assignment_6th_5.cpp)
add_executable(assignment6-6 Assignment_6th_6.cpp)


target_link_libraries(assignment6-1 ${OpenCV_LIBS})
target_include_directories(assignment6-1 PUBLIC ${OpenCV_LIBS})
target_link_libraries(assignment6-2 ${OpenCV_LIBS})
target_include_directories(assignment6-2 PUBLIC ${OpenCV_LIBS})
target_link_libraries(assignment6-3 ${OpenCV_LIBS})
target_include_directories(assignment6-3 PUBLIC ${OpenCV_LIBS})
target_link_libraries(assignment6-4 ${OpenCV_LIBS})
target_include_directories(assignment6-4 PUBLIC ${OpenCV_LIBS})
target_link_libraries(assignment6-5 ${OpenCV_LIBS})
target_include_directories(assignment6-5 PUBLIC ${OpenCV_LIBS})
target_link_libraries(assignment6-6 ${OpenCV_LIBS})
target_include_directories(assignment6-6 PUBLIC ${OpenCV_LIBS})