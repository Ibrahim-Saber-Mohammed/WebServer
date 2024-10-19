# CMakeList.txt : CMake project for WebServer, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.22)

set(This Uri)

# Add source to this project's executable.
set(Headers
    ${CMAKE_SOURCE_DIR}/include/Uri/Uri.hpp
)

set(Sources 
	${CMAKE_SOURCE_DIR}/src/Uri.cpp
)

add_library(${This} STATIC ${Sources} ${Headers})
set_target_properties(${This} PROPERTIES
    FOLDER Libraries
)

target_include_directories(${This} PUBLIC include)


