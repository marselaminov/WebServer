# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.19

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/marselaminov/CLionProjects/WebServer

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/marselaminov/CLionProjects/WebServer/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/WebServer.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/WebServer.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/WebServer.dir/flags.make

CMakeFiles/WebServer.dir/main.cpp.o: CMakeFiles/WebServer.dir/flags.make
CMakeFiles/WebServer.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/marselaminov/CLionProjects/WebServer/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/WebServer.dir/main.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/WebServer.dir/main.cpp.o -c /Users/marselaminov/CLionProjects/WebServer/main.cpp

CMakeFiles/WebServer.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/WebServer.dir/main.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/marselaminov/CLionProjects/WebServer/main.cpp > CMakeFiles/WebServer.dir/main.cpp.i

CMakeFiles/WebServer.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/WebServer.dir/main.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/marselaminov/CLionProjects/WebServer/main.cpp -o CMakeFiles/WebServer.dir/main.cpp.s

CMakeFiles/WebServer.dir/Server.cpp.o: CMakeFiles/WebServer.dir/flags.make
CMakeFiles/WebServer.dir/Server.cpp.o: ../Server.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/marselaminov/CLionProjects/WebServer/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/WebServer.dir/Server.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/WebServer.dir/Server.cpp.o -c /Users/marselaminov/CLionProjects/WebServer/Server.cpp

CMakeFiles/WebServer.dir/Server.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/WebServer.dir/Server.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/marselaminov/CLionProjects/WebServer/Server.cpp > CMakeFiles/WebServer.dir/Server.cpp.i

CMakeFiles/WebServer.dir/Server.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/WebServer.dir/Server.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/marselaminov/CLionProjects/WebServer/Server.cpp -o CMakeFiles/WebServer.dir/Server.cpp.s

CMakeFiles/WebServer.dir/Parser.cpp.o: CMakeFiles/WebServer.dir/flags.make
CMakeFiles/WebServer.dir/Parser.cpp.o: ../Parser.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/marselaminov/CLionProjects/WebServer/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/WebServer.dir/Parser.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/WebServer.dir/Parser.cpp.o -c /Users/marselaminov/CLionProjects/WebServer/Parser.cpp

CMakeFiles/WebServer.dir/Parser.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/WebServer.dir/Parser.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/marselaminov/CLionProjects/WebServer/Parser.cpp > CMakeFiles/WebServer.dir/Parser.cpp.i

CMakeFiles/WebServer.dir/Parser.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/WebServer.dir/Parser.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/marselaminov/CLionProjects/WebServer/Parser.cpp -o CMakeFiles/WebServer.dir/Parser.cpp.s

# Object files for target WebServer
WebServer_OBJECTS = \
"CMakeFiles/WebServer.dir/main.cpp.o" \
"CMakeFiles/WebServer.dir/Server.cpp.o" \
"CMakeFiles/WebServer.dir/Parser.cpp.o"

# External object files for target WebServer
WebServer_EXTERNAL_OBJECTS =

WebServer: CMakeFiles/WebServer.dir/main.cpp.o
WebServer: CMakeFiles/WebServer.dir/Server.cpp.o
WebServer: CMakeFiles/WebServer.dir/Parser.cpp.o
WebServer: CMakeFiles/WebServer.dir/build.make
WebServer: CMakeFiles/WebServer.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/marselaminov/CLionProjects/WebServer/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable WebServer"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/WebServer.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/WebServer.dir/build: WebServer

.PHONY : CMakeFiles/WebServer.dir/build

CMakeFiles/WebServer.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/WebServer.dir/cmake_clean.cmake
.PHONY : CMakeFiles/WebServer.dir/clean

CMakeFiles/WebServer.dir/depend:
	cd /Users/marselaminov/CLionProjects/WebServer/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/marselaminov/CLionProjects/WebServer /Users/marselaminov/CLionProjects/WebServer /Users/marselaminov/CLionProjects/WebServer/cmake-build-debug /Users/marselaminov/CLionProjects/WebServer/cmake-build-debug /Users/marselaminov/CLionProjects/WebServer/cmake-build-debug/CMakeFiles/WebServer.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/WebServer.dir/depend
