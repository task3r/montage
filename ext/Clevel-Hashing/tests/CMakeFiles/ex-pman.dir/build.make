# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.14

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
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
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /localdisk/rsanna/Montage/ext/Clevel-Hashing

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /localdisk/rsanna/Montage/ext/Clevel-Hashing

# Include any dependencies generated for this target.
include tests/CMakeFiles/ex-pman.dir/depend.make

# Include the progress variables for this target.
include tests/CMakeFiles/ex-pman.dir/progress.make

# Include the compile flags for this target's objects.
include tests/CMakeFiles/ex-pman.dir/flags.make

tests/CMakeFiles/ex-pman.dir/__/examples/pman/pman.cpp.o: tests/CMakeFiles/ex-pman.dir/flags.make
tests/CMakeFiles/ex-pman.dir/__/examples/pman/pman.cpp.o: examples/pman/pman.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/localdisk/rsanna/Montage/ext/Clevel-Hashing/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object tests/CMakeFiles/ex-pman.dir/__/examples/pman/pman.cpp.o"
	cd /localdisk/rsanna/Montage/ext/Clevel-Hashing/tests && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ex-pman.dir/__/examples/pman/pman.cpp.o -c /localdisk/rsanna/Montage/ext/Clevel-Hashing/examples/pman/pman.cpp

tests/CMakeFiles/ex-pman.dir/__/examples/pman/pman.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ex-pman.dir/__/examples/pman/pman.cpp.i"
	cd /localdisk/rsanna/Montage/ext/Clevel-Hashing/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /localdisk/rsanna/Montage/ext/Clevel-Hashing/examples/pman/pman.cpp > CMakeFiles/ex-pman.dir/__/examples/pman/pman.cpp.i

tests/CMakeFiles/ex-pman.dir/__/examples/pman/pman.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ex-pman.dir/__/examples/pman/pman.cpp.s"
	cd /localdisk/rsanna/Montage/ext/Clevel-Hashing/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /localdisk/rsanna/Montage/ext/Clevel-Hashing/examples/pman/pman.cpp -o CMakeFiles/ex-pman.dir/__/examples/pman/pman.cpp.s

# Object files for target ex-pman
ex__pman_OBJECTS = \
"CMakeFiles/ex-pman.dir/__/examples/pman/pman.cpp.o"

# External object files for target ex-pman
ex__pman_EXTERNAL_OBJECTS =

tests/ex-pman: tests/CMakeFiles/ex-pman.dir/__/examples/pman/pman.cpp.o
tests/ex-pman: tests/CMakeFiles/ex-pman.dir/build.make
tests/ex-pman: /usr/lib64/libpmemobj.so
tests/ex-pman: /usr/lib64/libpmem.so
tests/ex-pman: tests/CMakeFiles/ex-pman.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/localdisk/rsanna/Montage/ext/Clevel-Hashing/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ex-pman"
	cd /localdisk/rsanna/Montage/ext/Clevel-Hashing/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ex-pman.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tests/CMakeFiles/ex-pman.dir/build: tests/ex-pman

.PHONY : tests/CMakeFiles/ex-pman.dir/build

tests/CMakeFiles/ex-pman.dir/clean:
	cd /localdisk/rsanna/Montage/ext/Clevel-Hashing/tests && $(CMAKE_COMMAND) -P CMakeFiles/ex-pman.dir/cmake_clean.cmake
.PHONY : tests/CMakeFiles/ex-pman.dir/clean

tests/CMakeFiles/ex-pman.dir/depend:
	cd /localdisk/rsanna/Montage/ext/Clevel-Hashing && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /localdisk/rsanna/Montage/ext/Clevel-Hashing /localdisk/rsanna/Montage/ext/Clevel-Hashing/tests /localdisk/rsanna/Montage/ext/Clevel-Hashing /localdisk/rsanna/Montage/ext/Clevel-Hashing/tests /localdisk/rsanna/Montage/ext/Clevel-Hashing/tests/CMakeFiles/ex-pman.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tests/CMakeFiles/ex-pman.dir/depend

