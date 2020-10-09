
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
#set(CMAKE_MACOSX_RPATH 1)
MESSAGE("${CMAKE_MODULE_PATH}")


################################################################################
SET(CMAKE_CXX_FLAGS "-std=c++14")

################################################################################
SET(_project "metaSensingTest")
PROJECT(${_project} CXX)
set(THREADS_PREFER_PTHREAD_FLAG ON)
MESSAGE( "  ")
MESSAGE(STATUS "###############################################################")
MESSAGE( "  ")
MESSAGE(STATUS "  ${_project} ")
MESSAGE(STATUS "###############################################################")
MESSAGE( "  ")
################################################################################

# Include files:
################################################################################
INCLUDE_DIRECTORIES("include")


################################################################################
# Program
add_library(
            pLib src/consumer.cpp
                 src/producer.cpp
            )


find_package(Threads REQUIRED)

add_executable( ${_project}  main.cpp  )
target_link_libraries (${_project} PUBLIC pLib PRIVATE Threads::Threads)
