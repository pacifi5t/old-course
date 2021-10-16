cmake_minimum_required(VERSION 3.20.0)
project(old-course VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SFML COMPONENTS REQUIRED system window graphics)

file(GLOB_RECURSE sources "src/*.cpp")
include_directories("include")

add_executable(${PROJECT_NAME} ${sources})
target_link_libraries(${PROJECT_NAME} PUBLIC ${CMAKE_DL_LIBS} sfml-system sfml-window sfml-graphics)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND cp ${PROJECT_NAME} ../${PROJECT_NAME}
)