# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/ibrahim/Desktop/WebServer

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ibrahim/Desktop/WebServer/build

# Include any dependencies generated for this target.
include test/CMakeFiles/UriTest.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include test/CMakeFiles/UriTest.dir/compiler_depend.make

# Include the progress variables for this target.
include test/CMakeFiles/UriTest.dir/progress.make

# Include the compile flags for this target's objects.
include test/CMakeFiles/UriTest.dir/flags.make

test/CMakeFiles/UriTest.dir/UriTest.cpp.o: test/CMakeFiles/UriTest.dir/flags.make
test/CMakeFiles/UriTest.dir/UriTest.cpp.o: ../test/UriTest.cpp
test/CMakeFiles/UriTest.dir/UriTest.cpp.o: test/CMakeFiles/UriTest.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ibrahim/Desktop/WebServer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object test/CMakeFiles/UriTest.dir/UriTest.cpp.o"
	cd /home/ibrahim/Desktop/WebServer/build/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT test/CMakeFiles/UriTest.dir/UriTest.cpp.o -MF CMakeFiles/UriTest.dir/UriTest.cpp.o.d -o CMakeFiles/UriTest.dir/UriTest.cpp.o -c /home/ibrahim/Desktop/WebServer/test/UriTest.cpp

test/CMakeFiles/UriTest.dir/UriTest.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/UriTest.dir/UriTest.cpp.i"
	cd /home/ibrahim/Desktop/WebServer/build/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ibrahim/Desktop/WebServer/test/UriTest.cpp > CMakeFiles/UriTest.dir/UriTest.cpp.i

test/CMakeFiles/UriTest.dir/UriTest.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/UriTest.dir/UriTest.cpp.s"
	cd /home/ibrahim/Desktop/WebServer/build/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ibrahim/Desktop/WebServer/test/UriTest.cpp -o CMakeFiles/UriTest.dir/UriTest.cpp.s

# Object files for target UriTest
UriTest_OBJECTS = \
"CMakeFiles/UriTest.dir/UriTest.cpp.o"

# External object files for target UriTest
UriTest_EXTERNAL_OBJECTS =

test/UriTest: test/CMakeFiles/UriTest.dir/UriTest.cpp.o
test/UriTest: test/CMakeFiles/UriTest.dir/build.make
test/UriTest: /usr/local/lib/libgtest.a
test/UriTest: /usr/local/lib/libgtest_main.a
test/UriTest: libUri.a
test/UriTest: /usr/local/lib/libgtest.a
test/UriTest: test/CMakeFiles/UriTest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ibrahim/Desktop/WebServer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable UriTest"
	cd /home/ibrahim/Desktop/WebServer/build/test && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/UriTest.dir/link.txt --verbose=$(VERBOSE)
	cd /home/ibrahim/Desktop/WebServer/build/test && /usr/bin/cmake -D TEST_TARGET=UriTest -D TEST_EXECUTABLE=/home/ibrahim/Desktop/WebServer/build/test/UriTest -D TEST_EXECUTOR= -D TEST_WORKING_DIR=/home/ibrahim/Desktop/WebServer/build/test -D TEST_EXTRA_ARGS= -D TEST_PROPERTIES= -D TEST_PREFIX= -D TEST_SUFFIX= -D TEST_FILTER= -D NO_PRETTY_TYPES=FALSE -D NO_PRETTY_VALUES=FALSE -D TEST_LIST=UriTest_TESTS -D CTEST_FILE=/home/ibrahim/Desktop/WebServer/build/test/UriTest[1]_tests.cmake -D TEST_DISCOVERY_TIMEOUT=5 -D TEST_XML_OUTPUT_DIR= -P /usr/share/cmake-3.22/Modules/GoogleTestAddTests.cmake

# Rule to build all files generated by this target.
test/CMakeFiles/UriTest.dir/build: test/UriTest
.PHONY : test/CMakeFiles/UriTest.dir/build

test/CMakeFiles/UriTest.dir/clean:
	cd /home/ibrahim/Desktop/WebServer/build/test && $(CMAKE_COMMAND) -P CMakeFiles/UriTest.dir/cmake_clean.cmake
.PHONY : test/CMakeFiles/UriTest.dir/clean

test/CMakeFiles/UriTest.dir/depend:
	cd /home/ibrahim/Desktop/WebServer/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ibrahim/Desktop/WebServer /home/ibrahim/Desktop/WebServer/test /home/ibrahim/Desktop/WebServer/build /home/ibrahim/Desktop/WebServer/build/test /home/ibrahim/Desktop/WebServer/build/test/CMakeFiles/UriTest.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : test/CMakeFiles/UriTest.dir/depend

