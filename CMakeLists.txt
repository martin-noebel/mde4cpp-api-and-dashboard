# general settings
cmake_minimum_required(VERSION 3.9)
project(LibraryExample)
# set variables
set(CMAKE_CXX_STANDARD 17)
string(REPLACE "\\" "/" MDE4CPP_HOME $ENV{MDE4CPP_HOME})
set(CMAKE_FIND_LIBRARY_SUFFIXES ".dll")
set(BOOST_ROOT "C:/Program Files/boost_1_79_0")
# find libraries
find_library(ECORE ecore ${MDE4CPP_HOME}/application/bin)
find_library(TYPES types ${MDE4CPP_HOME}/application/bin)
find_library(MODEL libraryModel_ecore ${MDE4CPP_HOME}/application/bin)
find_package(Boost 1.79.0 REQUIRED)
if(Boost_FOUND AND ECORE AND TYPES AND MODEL)
    # copy dlls to build directory
    file(COPY ${ECORE} DESTINATION ${PROJECT_BINARY_DIR})
    file(COPY ${TYPES} DESTINATION ${PROJECT_BINARY_DIR})
    file(COPY ${MODEL} DESTINATION ${PROJECT_BINARY_DIR})
    # include the files
    include_directories(${Boost_INCLUDE_DIRS} ${MDE4CPP_HOME}/application/include)
    # add executable
    add_executable(${PROJECT_NAME} Main.cpp)
    # link boost, ecore and other libraries
    target_link_libraries(${PROJECT_NAME}
            PUBLIC ${ECORE}
            PUBLIC ${TYPES}
            PUBLIC ${MODEL}
            PUBLIC ${Boost_LIBRARIES}
            PUBLIC ws2_32
            PUBLIC wsock32
    )
endif()