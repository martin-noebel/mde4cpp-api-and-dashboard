# general settings
cmake_minimum_required(VERSION 3.9)
project(LibraryExample)
set(CMAKE_CXX_STANDARD 17)
# set mde4cpp environment variable
string(REPLACE "\\" "/" MDE4CPP_HOME $ENV{MDE4CPP_HOME})
# set dll suffix for libraries
set(CMAKE_FIND_LIBRARY_SUFFIXES ".dll")
# find all libraries
find_library(ECORE ecore ${MDE4CPP_HOME}/application/bin)
find_library(TYPES types ${MDE4CPP_HOME}/application/bin)
find_library(MODEL libraryModel_ecore ${MDE4CPP_HOME}/application/bin)
find_package(oatpp 1.3.0 REQUIRED)
if(oatpp_FOUND AND ECORE AND TYPES AND MODEL)
    # copy dlls to build directory
    file(COPY ${ECORE} DESTINATION ${PROJECT_BINARY_DIR})
    file(COPY ${TYPES} DESTINATION ${PROJECT_BINARY_DIR})
    file(COPY ${MODEL} DESTINATION ${PROJECT_BINARY_DIR})
    # include the files
    include_directories(${oatpp_INCLUDE_DIRS} ${MDE4CPP_HOME}/application/include)
    # add executable
    add_executable(${PROJECT_NAME} App.cpp)
    # link boost, ecore and other libraries
    target_link_libraries(${PROJECT_NAME}
            PUBLIC ${ECORE}
            PUBLIC ${TYPES}
            PUBLIC ${MODEL}
            PUBLIC oatpp::oatpp
            PUBLIC ws2_32
            PUBLIC wsock32
    )
endif()