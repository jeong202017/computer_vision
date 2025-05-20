cmake_minimum_required(VERSION 3.10)
project(opencv_test)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenCV REQUIRED)

add_executable(assignment8-1 Assignment_8th_1.cpp)
add_executable(assignment8-2 Assignment_8th_2.cpp)
add_executable(assignment8-3 Assignment_8th_3.cpp)
add_executable(assignment8-4 Assignment_8th_4.cpp)

target_link_libraries(assignment8-1 ${OpenCV_LIBS})
target_include_directories(assignment8-1 PUBLIC ${OpenCV_LIBS})

target_link_libraries(assignment8-2 ${OpenCV_LIBS})
target_include_directories(assignment8-2 PUBLIC ${OpenCV_LIBS})

target_link_libraries(assignment8-3 ${OpenCV_LIBS})
target_include_directories(assignment8-3 PUBLIC ${OpenCV_LIBS})

target_link_libraries(assignment8-4 ${OpenCV_LIBS})
target_include_directories(assignment8-4 PUBLIC ${OpenCV_LIBS})

# target_link_libraries(assignment7-2 ${OpenCV_LIBS})
# target_include_directories(assignment7-2 PUBLIC ${OpenCV_LIBS})