
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
#set(CMAKE_MACOSX_RPATH 1)
MESSAGE("${CMAKE_MODULE_PATH}")


################################################################################
SET(CMAKE_CXX_FLAGS "-std=c++14")

################################################################################
SET(_project "metaSensingTest")
PROJECT(${_project} CXX)

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

####################################################  Program(s)
#file(GLOB ODE_SRCs "src/*.cpp" ) # <= not preferred here because not all srcs are used for all subprojects
add_library(pLib src/consumer.cpp
                 src/producer.cpp
            )


add_executable( ${_project}  main.cpp  )
target_link_libraries (${_project} PUBLIC pLib)
