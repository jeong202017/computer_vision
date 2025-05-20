cmake_minimum_required(VERSION 3.10)
project(opencv_test)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenCV REQUIRED)

add_executable(assignment9-1 Assignment_9th_1.cpp)
add_executable(assignment9-2 Assignment_9th_2.cpp)
add_executable(assignment9-3 Assignment_9th_3.cpp)
add_executable(assignment9-4 Assignment_9th_4.cpp)
add_executable(image_editer image_slider.cpp)
add_executable(assignment9-5 Assignment_9th_5.cpp)
add_executable(assignment9-6 Assignment_9th_6.cpp)


# 공통 설정 함수
macro(link_and_include target)
    target_link_libraries(${target} ${OpenCV_LIBS})
    target_include_directories(${target} PUBLIC ${OpenCV_INCLUDE_DIRS})
endmacro()

# 각 타겟에 적용
link_and_include(assignment9-1)
link_and_include(assignment9-2)
link_and_include(assignment9-3)
link_and_include(assignment9-4)
link_and_include(image_editer)
link_and_include(assignment9-5)
link_and_include(assignment9-6)