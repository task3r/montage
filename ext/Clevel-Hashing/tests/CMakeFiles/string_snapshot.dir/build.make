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
include tests/CMakeFiles/string_snapshot.dir/depend.make

# Include the progress variables for this target.
include tests/CMakeFiles/string_snapshot.dir/progress.make

# Include the compile flags for this target's objects.
include tests/CMakeFiles/string_snapshot.dir/flags.make

tests/CMakeFiles/string_snapshot.dir/string_snapshot/string_snapshot.cpp.o: tests/CMakeFiles/string_snapshot.dir/flags.make
tests/CMakeFiles/string_snapshot.dir/string_snapshot/string_snapshot.cpp.o: tests/string_snapshot/string_snapshot.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/localdisk/rsanna/Montage/ext/Clevel-Hashing/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object tests/CMakeFiles/string_snapshot.dir/string_snapshot/string_snapshot.cpp.o"
	cd /localdisk/rsanna/Montage/ext/Clevel-Hashing/tests && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/string_snapshot.dir/string_snapshot/string_snapshot.cpp.o -c /localdisk/rsanna/Montage/ext/Clevel-Hashing/tests/string_snapshot/string_snapshot.cpp

tests/CMakeFiles/string_snapshot.dir/string_snapshot/string_snapshot.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/string_snapshot.dir/string_snapshot/string_snapshot.cpp.i"
	cd /localdisk/rsanna/Montage/ext/Clevel-Hashing/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /localdisk/rsanna/Montage/ext/Clevel-Hashing/tests/string_snapshot/string_snapshot.cpp > CMakeFiles/string_snapshot.dir/string_snapshot/string_snapshot.cpp.i

tests/CMakeFiles/string_snapshot.dir/string_snapshot/string_snapshot.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/string_snapshot.dir/string_snapshot/string_snapshot.cpp.s"
	cd /localdisk/rsanna/Montage/ext/Clevel-Hashing/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /localdisk/rsanna/Montage/ext/Clevel-Hashing/tests/string_snapshot/string_snapshot.cpp -o CMakeFiles/string_snapshot.dir/string_snapshot/string_snapshot.cpp.s

# Object files for target string_snapshot
string_snapshot_OBJECTS = \
"CMakeFiles/string_snapshot.dir/string_snapshot/string_snapshot.cpp.o"

# External object files for target string_snapshot
string_snapshot_EXTERNAL_OBJECTS =

tests/string_snapshot: tests/CMakeFiles/string_snapshot.dir/string_snapshot/string_snapshot.cpp.o
tests/string_snapshot: tests/CMakeFiles/string_snapshot.dir/build.make
tests/string_snapshot: /usr/lib64/libpmemobj.so
tests/string_snapshot: /usr/lib64/libpmem.so
tests/string_snapshot: tests/libtest_backtrace.a
tests/string_snapshot: tests/libvalgrind_internal.a
tests/string_snapshot: tests/CMakeFiles/string_snapshot.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/localdisk/rsanna/Montage/ext/Clevel-Hashing/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable string_snapshot"
	cd /localdisk/rsanna/Montage/ext/Clevel-Hashing/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/string_snapshot.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tests/CMakeFiles/string_snapshot.dir/build: tests/string_snapshot

.PHONY : tests/CMakeFiles/string_snapshot.dir/build

tests/CMakeFiles/string_snapshot.dir/clean:
	cd /localdisk/rsanna/Montage/ext/Clevel-Hashing/tests && $(CMAKE_COMMAND) -P CMakeFiles/string_snapshot.dir/cmake_clean.cmake
.PHONY : tests/CMakeFiles/string_snapshot.dir/clean

tests/CMakeFiles/string_snapshot.dir/depend:
	cd /localdisk/rsanna/Montage/ext/Clevel-Hashing && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /localdisk/rsanna/Montage/ext/Clevel-Hashing /localdisk/rsanna/Montage/ext/Clevel-Hashing/tests /localdisk/rsanna/Montage/ext/Clevel-Hashing /localdisk/rsanna/Montage/ext/Clevel-Hashing/tests /localdisk/rsanna/Montage/ext/Clevel-Hashing/tests/CMakeFiles/string_snapshot.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tests/CMakeFiles/string_snapshot.dir/depend

