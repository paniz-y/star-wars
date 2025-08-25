cmake_minimum_required(VERSION 3.15)

project(MyProject LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB SOURCES CONFIGURE_DEPENDS
    ${PROJECT_SOURCE_DIR}/src/*.cpp
)

add_executable(MyProject ${SOURCES})

target_include_directories(MyProject PUBLIC ${PROJECT_SOURCE_DIR}/include)
