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
CMAKE_COMMAND = /home/christophe/snap/clion/clion-2019.2.2/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/christophe/snap/clion/clion-2019.2.2/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/christophe/algoprog2/projetblockchain

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/christophe/algoprog2/projetblockchain/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/projetblockchain.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/projetblockchain.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/projetblockchain.dir/flags.make

CMakeFiles/projetblockchain.dir/main.c.o: CMakeFiles/projetblockchain.dir/flags.make
CMakeFiles/projetblockchain.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/christophe/algoprog2/projetblockchain/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/projetblockchain.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/projetblockchain.dir/main.c.o   -c /home/christophe/algoprog2/projetblockchain/main.c

CMakeFiles/projetblockchain.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/projetblockchain.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/christophe/algoprog2/projetblockchain/main.c > CMakeFiles/projetblockchain.dir/main.c.i

CMakeFiles/projetblockchain.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/projetblockchain.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/christophe/algoprog2/projetblockchain/main.c -o CMakeFiles/projetblockchain.dir/main.c.s

CMakeFiles/projetblockchain.dir/blockchain.c.o: CMakeFiles/projetblockchain.dir/flags.make
CMakeFiles/projetblockchain.dir/blockchain.c.o: ../blockchain.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/christophe/algoprog2/projetblockchain/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/projetblockchain.dir/blockchain.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/projetblockchain.dir/blockchain.c.o   -c /home/christophe/algoprog2/projetblockchain/blockchain.c

CMakeFiles/projetblockchain.dir/blockchain.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/projetblockchain.dir/blockchain.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/christophe/algoprog2/projetblockchain/blockchain.c > CMakeFiles/projetblockchain.dir/blockchain.c.i

CMakeFiles/projetblockchain.dir/blockchain.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/projetblockchain.dir/blockchain.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/christophe/algoprog2/projetblockchain/blockchain.c -o CMakeFiles/projetblockchain.dir/blockchain.c.s

# Object files for target projetblockchain
projetblockchain_OBJECTS = \
"CMakeFiles/projetblockchain.dir/main.c.o" \
"CMakeFiles/projetblockchain.dir/blockchain.c.o"

# External object files for target projetblockchain
projetblockchain_EXTERNAL_OBJECTS =

projetblockchain: CMakeFiles/projetblockchain.dir/main.c.o
projetblockchain: CMakeFiles/projetblockchain.dir/blockchain.c.o
projetblockchain: CMakeFiles/projetblockchain.dir/build.make
projetblockchain: /usr/lib/x86_64-linux-gnu/libssl.so
projetblockchain: /usr/lib/x86_64-linux-gnu/libcrypto.so
projetblockchain: CMakeFiles/projetblockchain.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/christophe/algoprog2/projetblockchain/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable projetblockchain"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/projetblockchain.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/projetblockchain.dir/build: projetblockchain

.PHONY : CMakeFiles/projetblockchain.dir/build

CMakeFiles/projetblockchain.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/projetblockchain.dir/cmake_clean.cmake
.PHONY : CMakeFiles/projetblockchain.dir/clean

CMakeFiles/projetblockchain.dir/depend:
	cd /home/christophe/algoprog2/projetblockchain/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/christophe/algoprog2/projetblockchain /home/christophe/algoprog2/projetblockchain /home/christophe/algoprog2/projetblockchain/cmake-build-debug /home/christophe/algoprog2/projetblockchain/cmake-build-debug /home/christophe/algoprog2/projetblockchain/cmake-build-debug/CMakeFiles/projetblockchain.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/projetblockchain.dir/depend

