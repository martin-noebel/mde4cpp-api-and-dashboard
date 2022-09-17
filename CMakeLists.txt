# general settings
cmake_minimum_required(VERSION 3.9)
project(Mde4cppApi)
set(CMAKE_CXX_STANDARD 17)
# set mde4cpp environment variable
string(REPLACE "\\" "/" MDE4CPP_HOME $ENV{MDE4CPP_HOME})
# set dll suffix for libraries
set(CMAKE_FIND_LIBRARY_SUFFIXES ".dll")
# find ecore library
find_library(ECORE ecore ${MDE4CPP_HOME}/application/bin)
# find boost library
set(BOOST_ROOT "C:/Program Files/boost_1_79_0")
find_package(Boost 1.79 REQUIRED)
if(Boost_FOUND AND ECORE)
    # copy dll to build directory
    file(COPY ${ECORE} DESTINATION ${PROJECT_BINARY_DIR})
    # include the files
    include_directories(${Boost_INCLUDE_DIRS} ${MDE4CPP_HOME}/application/include)
    # add executable
    add_executable(${PROJECT_NAME} Main.cpp)
    # link boost, ecore and other libraries
    target_link_libraries(${PROJECT_NAME} ${ECORE} ${Boost_LIBRARIES} ws2_32 wsock32)
endif()