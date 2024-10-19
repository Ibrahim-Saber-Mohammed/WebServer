# CMakeList.txt : CMake project for WebServer, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("Uri")

# Organize applications, libraries, etc. in folders in the IDE.
   set_property(GLOBAL PROPERTY USE_FOLDERS ON)


# Add source to this project's executable.
add_executable (WebServer "WebServer.cpp" "WebServer.h" )

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET WebServer PROPERTY CXX_STANDARD 11)
endif()

# TODO: Add tests and install targets if needed.
# Add source to this project's executable.
set(Headers
    ${CMAKE_SOURCE_DIR}/include/Uri/Uri.hpp
)

set(Sources 
	${CMAKE_SOURCE_DIR}/src/Uri.cpp
)


add_library(${PROJECT_NAME} STATIC ${Sources} ${Headers})
set_target_properties(${PROJECT_NAME} PROPERTIES
    FOLDER Libraries
)

target_include_directories(${PROJECT_NAME} PUBLIC include)

add_subdirectory(test)