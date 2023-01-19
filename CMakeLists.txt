#General settings
CMAKE_MINIMUM_REQUIRED(VERSION 3.9)
PROJECT(Mde4cppApi)

#Set variables
SET(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_FLAGS "-Wall -Wno-overloaded-virtual -Wdeprecated-declarations -fmax-errors=5")
SET(CMAKE_FIND_LIBRARY_SUFFIXES ".dll")
SET(BOOST_ROOT "C:/Program Files/boost")
SET(SOURCE_FILES Main.cpp api/libraryModel_genericApi.cpp api/libraryModel_modelApi.cpp api/libraryModel_mixedApi.cpp)

#Find packages and include directories
FIND_PACKAGE(Boost)
INCLUDE_DIRECTORIES(
        ${Boost_INCLUDE_DIRS}
        include
)
FIND_LIBRARY(ECORE_RELEASE ecore bin)
FIND_LIBRARY(TYPES_RELEASE types bin)
FIND_LIBRARY(LIBRARYMODEL_ECORE_RELEASE libraryModel_ecore bin)

#Copy DLL-Files to build directory
FILE(COPY ${ECORE_RELEASE} DESTINATION ${PROJECT_BINARY_DIR})
FILE(COPY ${TYPES_RELEASE} DESTINATION ${PROJECT_BINARY_DIR})
FILE(COPY ${LIBRARYMODEL_ECORE_RELEASE} DESTINATION ${PROJECT_BINARY_DIR})

#Add executable
ADD_EXECUTABLE(${PROJECT_NAME} ${SOURCE_FILES})

#Link libraries
TARGET_LINK_LIBRARIES(${PROJECT_NAME}
        PUBLIC ${ECORE_RELEASE}
        PUBLIC ${TYPES_RELEASE}
        PUBLIC ${LIBRARYMODEL_ECORE_RELEASE}
        PUBLIC ${Boost_LIBRARIES}
        PUBLIC ws2_32
        PUBLIC wsock32
        )