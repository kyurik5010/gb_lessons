# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.20

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
CMAKE_SOURCE_DIR = /Users/urijmihajlovic/gb_lessons/lesson_3

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/urijmihajlovic/gb_lessons/lesson_3/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/lsn3.dir/depend.make
# Include the progress variables for this target.
include CMakeFiles/lsn3.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/lsn3.dir/flags.make

CMakeFiles/lsn3.dir/lsn3_main.cpp.o: CMakeFiles/lsn3.dir/flags.make
CMakeFiles/lsn3.dir/lsn3_main.cpp.o: ../lsn3_main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/urijmihajlovic/gb_lessons/lesson_3/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/lsn3.dir/lsn3_main.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/lsn3.dir/lsn3_main.cpp.o -c /Users/urijmihajlovic/gb_lessons/lesson_3/lsn3_main.cpp

CMakeFiles/lsn3.dir/lsn3_main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/lsn3.dir/lsn3_main.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/urijmihajlovic/gb_lessons/lesson_3/lsn3_main.cpp > CMakeFiles/lsn3.dir/lsn3_main.cpp.i

CMakeFiles/lsn3.dir/lsn3_main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/lsn3.dir/lsn3_main.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/urijmihajlovic/gb_lessons/lesson_3/lsn3_main.cpp -o CMakeFiles/lsn3.dir/lsn3_main.cpp.s

CMakeFiles/lsn3.dir/lsn3_mod.cpp.o: CMakeFiles/lsn3.dir/flags.make
CMakeFiles/lsn3.dir/lsn3_mod.cpp.o: ../lsn3_mod.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/urijmihajlovic/gb_lessons/lesson_3/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/lsn3.dir/lsn3_mod.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/lsn3.dir/lsn3_mod.cpp.o -c /Users/urijmihajlovic/gb_lessons/lesson_3/lsn3_mod.cpp

CMakeFiles/lsn3.dir/lsn3_mod.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/lsn3.dir/lsn3_mod.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/urijmihajlovic/gb_lessons/lesson_3/lsn3_mod.cpp > CMakeFiles/lsn3.dir/lsn3_mod.cpp.i

CMakeFiles/lsn3.dir/lsn3_mod.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/lsn3.dir/lsn3_mod.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/urijmihajlovic/gb_lessons/lesson_3/lsn3_mod.cpp -o CMakeFiles/lsn3.dir/lsn3_mod.cpp.s

# Object files for target lsn3
lsn3_OBJECTS = \
"CMakeFiles/lsn3.dir/lsn3_main.cpp.o" \
"CMakeFiles/lsn3.dir/lsn3_mod.cpp.o"

# External object files for target lsn3
lsn3_EXTERNAL_OBJECTS =

lsn3: CMakeFiles/lsn3.dir/lsn3_main.cpp.o
lsn3: CMakeFiles/lsn3.dir/lsn3_mod.cpp.o
lsn3: CMakeFiles/lsn3.dir/build.make
lsn3: CMakeFiles/lsn3.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/urijmihajlovic/gb_lessons/lesson_3/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable lsn3"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/lsn3.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/lsn3.dir/build: lsn3
.PHONY : CMakeFiles/lsn3.dir/build

CMakeFiles/lsn3.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/lsn3.dir/cmake_clean.cmake
.PHONY : CMakeFiles/lsn3.dir/clean

CMakeFiles/lsn3.dir/depend:
	cd /Users/urijmihajlovic/gb_lessons/lesson_3/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/urijmihajlovic/gb_lessons/lesson_3 /Users/urijmihajlovic/gb_lessons/lesson_3 /Users/urijmihajlovic/gb_lessons/lesson_3/cmake-build-debug /Users/urijmihajlovic/gb_lessons/lesson_3/cmake-build-debug /Users/urijmihajlovic/gb_lessons/lesson_3/cmake-build-debug/CMakeFiles/lsn3.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/lsn3.dir/depend

