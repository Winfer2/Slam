# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

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
CMAKE_SOURCE_DIR = "/home/rodrigocoelho/Área de Trabalho/g2o-master"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/rodrigocoelho/Área de Trabalho/g2o-master"

# Include any dependencies generated for this target.
include g2o/examples/target/CMakeFiles/static_target.dir/depend.make

# Include the progress variables for this target.
include g2o/examples/target/CMakeFiles/static_target.dir/progress.make

# Include the compile flags for this target's objects.
include g2o/examples/target/CMakeFiles/static_target.dir/flags.make

g2o/examples/target/CMakeFiles/static_target.dir/static_target.cpp.o: g2o/examples/target/CMakeFiles/static_target.dir/flags.make
g2o/examples/target/CMakeFiles/static_target.dir/static_target.cpp.o: g2o/examples/target/static_target.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/rodrigocoelho/Área de Trabalho/g2o-master/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object g2o/examples/target/CMakeFiles/static_target.dir/static_target.cpp.o"
	cd "/home/rodrigocoelho/Área de Trabalho/g2o-master/g2o/examples/target" && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/static_target.dir/static_target.cpp.o -c "/home/rodrigocoelho/Área de Trabalho/g2o-master/g2o/examples/target/static_target.cpp"

g2o/examples/target/CMakeFiles/static_target.dir/static_target.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/static_target.dir/static_target.cpp.i"
	cd "/home/rodrigocoelho/Área de Trabalho/g2o-master/g2o/examples/target" && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/rodrigocoelho/Área de Trabalho/g2o-master/g2o/examples/target/static_target.cpp" > CMakeFiles/static_target.dir/static_target.cpp.i

g2o/examples/target/CMakeFiles/static_target.dir/static_target.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/static_target.dir/static_target.cpp.s"
	cd "/home/rodrigocoelho/Área de Trabalho/g2o-master/g2o/examples/target" && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/rodrigocoelho/Área de Trabalho/g2o-master/g2o/examples/target/static_target.cpp" -o CMakeFiles/static_target.dir/static_target.cpp.s

g2o/examples/target/CMakeFiles/static_target.dir/static_target.cpp.o.requires:

.PHONY : g2o/examples/target/CMakeFiles/static_target.dir/static_target.cpp.o.requires

g2o/examples/target/CMakeFiles/static_target.dir/static_target.cpp.o.provides: g2o/examples/target/CMakeFiles/static_target.dir/static_target.cpp.o.requires
	$(MAKE) -f g2o/examples/target/CMakeFiles/static_target.dir/build.make g2o/examples/target/CMakeFiles/static_target.dir/static_target.cpp.o.provides.build
.PHONY : g2o/examples/target/CMakeFiles/static_target.dir/static_target.cpp.o.provides

g2o/examples/target/CMakeFiles/static_target.dir/static_target.cpp.o.provides.build: g2o/examples/target/CMakeFiles/static_target.dir/static_target.cpp.o


# Object files for target static_target
static_target_OBJECTS = \
"CMakeFiles/static_target.dir/static_target.cpp.o"

# External object files for target static_target
static_target_EXTERNAL_OBJECTS =

bin/static_target: g2o/examples/target/CMakeFiles/static_target.dir/static_target.cpp.o
bin/static_target: g2o/examples/target/CMakeFiles/static_target.dir/build.make
bin/static_target: lib/libg2o_solver_cholmod.so
bin/static_target: lib/libg2o_core.so
bin/static_target: lib/libg2o_stuff.so
bin/static_target: /usr/lib/x86_64-linux-gnu/libcholmod.so
bin/static_target: /usr/lib/x86_64-linux-gnu/libamd.so
bin/static_target: /usr/lib/x86_64-linux-gnu/libcolamd.so
bin/static_target: /usr/lib/x86_64-linux-gnu/libcamd.so
bin/static_target: /usr/lib/x86_64-linux-gnu/libccolamd.so
bin/static_target: /usr/lib/x86_64-linux-gnu/libsuitesparseconfig.so
bin/static_target: /usr/lib/libblas.so
bin/static_target: /usr/lib/liblapack.so
bin/static_target: g2o/examples/target/CMakeFiles/static_target.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/rodrigocoelho/Área de Trabalho/g2o-master/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../../../bin/static_target"
	cd "/home/rodrigocoelho/Área de Trabalho/g2o-master/g2o/examples/target" && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/static_target.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
g2o/examples/target/CMakeFiles/static_target.dir/build: bin/static_target

.PHONY : g2o/examples/target/CMakeFiles/static_target.dir/build

g2o/examples/target/CMakeFiles/static_target.dir/requires: g2o/examples/target/CMakeFiles/static_target.dir/static_target.cpp.o.requires

.PHONY : g2o/examples/target/CMakeFiles/static_target.dir/requires

g2o/examples/target/CMakeFiles/static_target.dir/clean:
	cd "/home/rodrigocoelho/Área de Trabalho/g2o-master/g2o/examples/target" && $(CMAKE_COMMAND) -P CMakeFiles/static_target.dir/cmake_clean.cmake
.PHONY : g2o/examples/target/CMakeFiles/static_target.dir/clean

g2o/examples/target/CMakeFiles/static_target.dir/depend:
	cd "/home/rodrigocoelho/Área de Trabalho/g2o-master" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/rodrigocoelho/Área de Trabalho/g2o-master" "/home/rodrigocoelho/Área de Trabalho/g2o-master/g2o/examples/target" "/home/rodrigocoelho/Área de Trabalho/g2o-master" "/home/rodrigocoelho/Área de Trabalho/g2o-master/g2o/examples/target" "/home/rodrigocoelho/Área de Trabalho/g2o-master/g2o/examples/target/CMakeFiles/static_target.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : g2o/examples/target/CMakeFiles/static_target.dir/depend

