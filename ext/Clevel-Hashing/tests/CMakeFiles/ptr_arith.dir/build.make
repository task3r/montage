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
include tests/CMakeFiles/ptr_arith.dir/depend.make

# Include the progress variables for this target.
include tests/CMakeFiles/ptr_arith.dir/progress.make

# Include the compile flags for this target's objects.
include tests/CMakeFiles/ptr_arith.dir/flags.make

tests/CMakeFiles/ptr_arith.dir/ptr_arith/ptr_arith.cpp.o: tests/CMakeFiles/ptr_arith.dir/flags.make
tests/CMakeFiles/ptr_arith.dir/ptr_arith/ptr_arith.cpp.o: tests/ptr_arith/ptr_arith.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/localdisk/rsanna/Montage/ext/Clevel-Hashing/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object tests/CMakeFiles/ptr_arith.dir/ptr_arith/ptr_arith.cpp.o"
	cd /localdisk/rsanna/Montage/ext/Clevel-Hashing/tests && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ptr_arith.dir/ptr_arith/ptr_arith.cpp.o -c /localdisk/rsanna/Montage/ext/Clevel-Hashing/tests/ptr_arith/ptr_arith.cpp

tests/CMakeFiles/ptr_arith.dir/ptr_arith/ptr_arith.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ptr_arith.dir/ptr_arith/ptr_arith.cpp.i"
	cd /localdisk/rsanna/Montage/ext/Clevel-Hashing/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /localdisk/rsanna/Montage/ext/Clevel-Hashing/tests/ptr_arith/ptr_arith.cpp > CMakeFiles/ptr_arith.dir/ptr_arith/ptr_arith.cpp.i

tests/CMakeFiles/ptr_arith.dir/ptr_arith/ptr_arith.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ptr_arith.dir/ptr_arith/ptr_arith.cpp.s"
	cd /localdisk/rsanna/Montage/ext/Clevel-Hashing/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /localdisk/rsanna/Montage/ext/Clevel-Hashing/tests/ptr_arith/ptr_arith.cpp -o CMakeFiles/ptr_arith.dir/ptr_arith/ptr_arith.cpp.s

# Object files for target ptr_arith
ptr_arith_OBJECTS = \
"CMakeFiles/ptr_arith.dir/ptr_arith/ptr_arith.cpp.o"

# External object files for target ptr_arith
ptr_arith_EXTERNAL_OBJECTS =

tests/ptr_arith: tests/CMakeFiles/ptr_arith.dir/ptr_arith/ptr_arith.cpp.o
tests/ptr_arith: tests/CMakeFiles/ptr_arith.dir/build.make
tests/ptr_arith: /usr/lib64/libpmemobj.so
tests/ptr_arith: /usr/lib64/libpmem.so
tests/ptr_arith: tests/libtest_backtrace.a
tests/ptr_arith: tests/libvalgrind_internal.a
tests/ptr_arith: tests/CMakeFiles/ptr_arith.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/localdisk/rsanna/Montage/ext/Clevel-Hashing/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ptr_arith"
	cd /localdisk/rsanna/Montage/ext/Clevel-Hashing/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ptr_arith.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tests/CMakeFiles/ptr_arith.dir/build: tests/ptr_arith

.PHONY : tests/CMakeFiles/ptr_arith.dir/build

tests/CMakeFiles/ptr_arith.dir/clean:
	cd /localdisk/rsanna/Montage/ext/Clevel-Hashing/tests && $(CMAKE_COMMAND) -P CMakeFiles/ptr_arith.dir/cmake_clean.cmake
.PHONY : tests/CMakeFiles/ptr_arith.dir/clean

tests/CMakeFiles/ptr_arith.dir/depend:
	cd /localdisk/rsanna/Montage/ext/Clevel-Hashing && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /localdisk/rsanna/Montage/ext/Clevel-Hashing /localdisk/rsanna/Montage/ext/Clevel-Hashing/tests /localdisk/rsanna/Montage/ext/Clevel-Hashing /localdisk/rsanna/Montage/ext/Clevel-Hashing/tests /localdisk/rsanna/Montage/ext/Clevel-Hashing/tests/CMakeFiles/ptr_arith.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tests/CMakeFiles/ptr_arith.dir/depend

