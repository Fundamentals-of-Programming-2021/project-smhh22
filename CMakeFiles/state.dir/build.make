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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/a/Desktop/Sharif/1/Proj/state.io

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/a/Desktop/Sharif/1/Proj/state.io

# Include any dependencies generated for this target.
include CMakeFiles/state.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/state.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/state.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/state.dir/flags.make

CMakeFiles/state.dir/src/main.c.o: CMakeFiles/state.dir/flags.make
CMakeFiles/state.dir/src/main.c.o: src/main.c
CMakeFiles/state.dir/src/main.c.o: CMakeFiles/state.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/a/Desktop/Sharif/1/Proj/state.io/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/state.dir/src/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/state.dir/src/main.c.o -MF CMakeFiles/state.dir/src/main.c.o.d -o CMakeFiles/state.dir/src/main.c.o -c /home/a/Desktop/Sharif/1/Proj/state.io/src/main.c

CMakeFiles/state.dir/src/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/state.dir/src/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/a/Desktop/Sharif/1/Proj/state.io/src/main.c > CMakeFiles/state.dir/src/main.c.i

CMakeFiles/state.dir/src/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/state.dir/src/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/a/Desktop/Sharif/1/Proj/state.io/src/main.c -o CMakeFiles/state.dir/src/main.c.s

# Object files for target state
state_OBJECTS = \
"CMakeFiles/state.dir/src/main.c.o"

# External object files for target state
state_EXTERNAL_OBJECTS =

state: CMakeFiles/state.dir/src/main.c.o
state: CMakeFiles/state.dir/build.make
state: CMakeFiles/state.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/a/Desktop/Sharif/1/Proj/state.io/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable state"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/state.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/state.dir/build: state
.PHONY : CMakeFiles/state.dir/build

CMakeFiles/state.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/state.dir/cmake_clean.cmake
.PHONY : CMakeFiles/state.dir/clean

CMakeFiles/state.dir/depend:
	cd /home/a/Desktop/Sharif/1/Proj/state.io && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/a/Desktop/Sharif/1/Proj/state.io /home/a/Desktop/Sharif/1/Proj/state.io /home/a/Desktop/Sharif/1/Proj/state.io /home/a/Desktop/Sharif/1/Proj/state.io /home/a/Desktop/Sharif/1/Proj/state.io/CMakeFiles/state.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/state.dir/depend

