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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.14.3/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.14.3/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/dzhiblavi/Documents/prog/cpp/clion/big_integer

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/dzhiblavi/Documents/prog/cpp/clion/big_integer/build

# Include any dependencies generated for this target.
include CMakeFiles/big_integer.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/big_integer.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/big_integer.dir/flags.make

CMakeFiles/big_integer.dir/big_integer_testing.cpp.o: CMakeFiles/big_integer.dir/flags.make
CMakeFiles/big_integer.dir/big_integer_testing.cpp.o: ../big_integer_testing.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/dzhiblavi/Documents/prog/cpp/clion/big_integer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/big_integer.dir/big_integer_testing.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/big_integer.dir/big_integer_testing.cpp.o -c /Users/dzhiblavi/Documents/prog/cpp/clion/big_integer/big_integer_testing.cpp

CMakeFiles/big_integer.dir/big_integer_testing.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/big_integer.dir/big_integer_testing.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/dzhiblavi/Documents/prog/cpp/clion/big_integer/big_integer_testing.cpp > CMakeFiles/big_integer.dir/big_integer_testing.cpp.i

CMakeFiles/big_integer.dir/big_integer_testing.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/big_integer.dir/big_integer_testing.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/dzhiblavi/Documents/prog/cpp/clion/big_integer/big_integer_testing.cpp -o CMakeFiles/big_integer.dir/big_integer_testing.cpp.s

CMakeFiles/big_integer.dir/big_integer.cpp.o: CMakeFiles/big_integer.dir/flags.make
CMakeFiles/big_integer.dir/big_integer.cpp.o: ../big_integer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/dzhiblavi/Documents/prog/cpp/clion/big_integer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/big_integer.dir/big_integer.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/big_integer.dir/big_integer.cpp.o -c /Users/dzhiblavi/Documents/prog/cpp/clion/big_integer/big_integer.cpp

CMakeFiles/big_integer.dir/big_integer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/big_integer.dir/big_integer.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/dzhiblavi/Documents/prog/cpp/clion/big_integer/big_integer.cpp > CMakeFiles/big_integer.dir/big_integer.cpp.i

CMakeFiles/big_integer.dir/big_integer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/big_integer.dir/big_integer.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/dzhiblavi/Documents/prog/cpp/clion/big_integer/big_integer.cpp -o CMakeFiles/big_integer.dir/big_integer.cpp.s

CMakeFiles/big_integer.dir/gtest/gtest-all.cc.o: CMakeFiles/big_integer.dir/flags.make
CMakeFiles/big_integer.dir/gtest/gtest-all.cc.o: ../gtest/gtest-all.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/dzhiblavi/Documents/prog/cpp/clion/big_integer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/big_integer.dir/gtest/gtest-all.cc.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/big_integer.dir/gtest/gtest-all.cc.o -c /Users/dzhiblavi/Documents/prog/cpp/clion/big_integer/gtest/gtest-all.cc

CMakeFiles/big_integer.dir/gtest/gtest-all.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/big_integer.dir/gtest/gtest-all.cc.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/dzhiblavi/Documents/prog/cpp/clion/big_integer/gtest/gtest-all.cc > CMakeFiles/big_integer.dir/gtest/gtest-all.cc.i

CMakeFiles/big_integer.dir/gtest/gtest-all.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/big_integer.dir/gtest/gtest-all.cc.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/dzhiblavi/Documents/prog/cpp/clion/big_integer/gtest/gtest-all.cc -o CMakeFiles/big_integer.dir/gtest/gtest-all.cc.s

CMakeFiles/big_integer.dir/gtest/gtest_main.cc.o: CMakeFiles/big_integer.dir/flags.make
CMakeFiles/big_integer.dir/gtest/gtest_main.cc.o: ../gtest/gtest_main.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/dzhiblavi/Documents/prog/cpp/clion/big_integer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/big_integer.dir/gtest/gtest_main.cc.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/big_integer.dir/gtest/gtest_main.cc.o -c /Users/dzhiblavi/Documents/prog/cpp/clion/big_integer/gtest/gtest_main.cc

CMakeFiles/big_integer.dir/gtest/gtest_main.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/big_integer.dir/gtest/gtest_main.cc.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/dzhiblavi/Documents/prog/cpp/clion/big_integer/gtest/gtest_main.cc > CMakeFiles/big_integer.dir/gtest/gtest_main.cc.i

CMakeFiles/big_integer.dir/gtest/gtest_main.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/big_integer.dir/gtest/gtest_main.cc.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/dzhiblavi/Documents/prog/cpp/clion/big_integer/gtest/gtest_main.cc -o CMakeFiles/big_integer.dir/gtest/gtest_main.cc.s

CMakeFiles/big_integer.dir/engine/_asm_vector.asm.o: CMakeFiles/big_integer.dir/flags.make
CMakeFiles/big_integer.dir/engine/_asm_vector.asm.o: ../engine/_asm_vector.asm
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/dzhiblavi/Documents/prog/cpp/clion/big_integer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building ASM_NASM object CMakeFiles/big_integer.dir/engine/_asm_vector.asm.o"
	/usr/local/bin/nasm $(ASM_NASM_INCLUDES) $(ASM_NASM_FLAGS) -f macho64 -o CMakeFiles/big_integer.dir/engine/_asm_vector.asm.o /Users/dzhiblavi/Documents/prog/cpp/clion/big_integer/engine/_asm_vector.asm

CMakeFiles/big_integer.dir/_core_arithmetics.cpp.o: CMakeFiles/big_integer.dir/flags.make
CMakeFiles/big_integer.dir/_core_arithmetics.cpp.o: ../_core_arithmetics.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/dzhiblavi/Documents/prog/cpp/clion/big_integer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/big_integer.dir/_core_arithmetics.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/big_integer.dir/_core_arithmetics.cpp.o -c /Users/dzhiblavi/Documents/prog/cpp/clion/big_integer/_core_arithmetics.cpp

CMakeFiles/big_integer.dir/_core_arithmetics.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/big_integer.dir/_core_arithmetics.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/dzhiblavi/Documents/prog/cpp/clion/big_integer/_core_arithmetics.cpp > CMakeFiles/big_integer.dir/_core_arithmetics.cpp.i

CMakeFiles/big_integer.dir/_core_arithmetics.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/big_integer.dir/_core_arithmetics.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/dzhiblavi/Documents/prog/cpp/clion/big_integer/_core_arithmetics.cpp -o CMakeFiles/big_integer.dir/_core_arithmetics.cpp.s

# Object files for target big_integer
big_integer_OBJECTS = \
"CMakeFiles/big_integer.dir/big_integer_testing.cpp.o" \
"CMakeFiles/big_integer.dir/big_integer.cpp.o" \
"CMakeFiles/big_integer.dir/gtest/gtest-all.cc.o" \
"CMakeFiles/big_integer.dir/gtest/gtest_main.cc.o" \
"CMakeFiles/big_integer.dir/engine/_asm_vector.asm.o" \
"CMakeFiles/big_integer.dir/_core_arithmetics.cpp.o"

# External object files for target big_integer
big_integer_EXTERNAL_OBJECTS =

big_integer: CMakeFiles/big_integer.dir/big_integer_testing.cpp.o
big_integer: CMakeFiles/big_integer.dir/big_integer.cpp.o
big_integer: CMakeFiles/big_integer.dir/gtest/gtest-all.cc.o
big_integer: CMakeFiles/big_integer.dir/gtest/gtest_main.cc.o
big_integer: CMakeFiles/big_integer.dir/engine/_asm_vector.asm.o
big_integer: CMakeFiles/big_integer.dir/_core_arithmetics.cpp.o
big_integer: CMakeFiles/big_integer.dir/build.make
big_integer: CMakeFiles/big_integer.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/dzhiblavi/Documents/prog/cpp/clion/big_integer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking CXX executable big_integer"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/big_integer.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/big_integer.dir/build: big_integer

.PHONY : CMakeFiles/big_integer.dir/build

CMakeFiles/big_integer.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/big_integer.dir/cmake_clean.cmake
.PHONY : CMakeFiles/big_integer.dir/clean

CMakeFiles/big_integer.dir/depend:
	cd /Users/dzhiblavi/Documents/prog/cpp/clion/big_integer/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/dzhiblavi/Documents/prog/cpp/clion/big_integer /Users/dzhiblavi/Documents/prog/cpp/clion/big_integer /Users/dzhiblavi/Documents/prog/cpp/clion/big_integer/build /Users/dzhiblavi/Documents/prog/cpp/clion/big_integer/build /Users/dzhiblavi/Documents/prog/cpp/clion/big_integer/build/CMakeFiles/big_integer.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/big_integer.dir/depend

