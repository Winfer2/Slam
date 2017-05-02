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
include g2o/examples/data_fitting/CMakeFiles/circle_fit.dir/depend.make

# Include the progress variables for this target.
include g2o/examples/data_fitting/CMakeFiles/circle_fit.dir/progress.make

# Include the compile flags for this target's objects.
include g2o/examples/data_fitting/CMakeFiles/circle_fit.dir/flags.make

g2o/examples/data_fitting/CMakeFiles/circle_fit.dir/circle_fit.cpp.o: g2o/examples/data_fitting/CMakeFiles/circle_fit.dir/flags.make
g2o/examples/data_fitting/CMakeFiles/circle_fit.dir/circle_fit.cpp.o: g2o/examples/data_fitting/circle_fit.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/rodrigocoelho/Área de Trabalho/g2o-master/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object g2o/examples/data_fitting/CMakeFiles/circle_fit.dir/circle_fit.cpp.o"
	cd "/home/rodrigocoelho/Área de Trabalho/g2o-master/g2o/examples/data_fitting" && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/circle_fit.dir/circle_fit.cpp.o -c "/home/rodrigocoelho/Área de Trabalho/g2o-master/g2o/examples/data_fitting/circle_fit.cpp"

g2o/examples/data_fitting/CMakeFiles/circle_fit.dir/circle_fit.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/circle_fit.dir/circle_fit.cpp.i"
	cd "/home/rodrigocoelho/Área de Trabalho/g2o-master/g2o/examples/data_fitting" && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/rodrigocoelho/Área de Trabalho/g2o-master/g2o/examples/data_fitting/circle_fit.cpp" > CMakeFiles/circle_fit.dir/circle_fit.cpp.i

g2o/examples/data_fitting/CMakeFiles/circle_fit.dir/circle_fit.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/circle_fit.dir/circle_fit.cpp.s"
	cd "/home/rodrigocoelho/Área de Trabalho/g2o-master/g2o/examples/data_fitting" && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/rodrigocoelho/Área de Trabalho/g2o-master/g2o/examples/data_fitting/circle_fit.cpp" -o CMakeFiles/circle_fit.dir/circle_fit.cpp.s

g2o/examples/data_fitting/CMakeFiles/circle_fit.dir/circle_fit.cpp.o.requires:

.PHONY : g2o/examples/data_fitting/CMakeFiles/circle_fit.dir/circle_fit.cpp.o.requires

g2o/examples/data_fitting/CMakeFiles/circle_fit.dir/circle_fit.cpp.o.provides: g2o/examples/data_fitting/CMakeFiles/circle_fit.dir/circle_fit.cpp.o.requires
	$(MAKE) -f g2o/examples/data_fitting/CMakeFiles/circle_fit.dir/build.make g2o/examples/data_fitting/CMakeFiles/circle_fit.dir/circle_fit.cpp.o.provides.build
.PHONY : g2o/examples/data_fitting/CMakeFiles/circle_fit.dir/circle_fit.cpp.o.provides

g2o/examples/data_fitting/CMakeFiles/circle_fit.dir/circle_fit.cpp.o.provides.build: g2o/examples/data_fitting/CMakeFiles/circle_fit.dir/circle_fit.cpp.o


# Object files for target circle_fit
circle_fit_OBJECTS = \
"CMakeFiles/circle_fit.dir/circle_fit.cpp.o"

# External object files for target circle_fit
circle_fit_EXTERNAL_OBJECTS =

bin/circle_fit: g2o/examples/data_fitting/CMakeFiles/circle_fit.dir/circle_fit.cpp.o
bin/circle_fit: g2o/examples/data_fitting/CMakeFiles/circle_fit.dir/build.make
bin/circle_fit: lib/libg2o_solver_csparse.so
bin/circle_fit: lib/libg2o_core.so
bin/circle_fit: lib/libg2o_stuff.so
bin/circle_fit: lib/libg2o_csparse_extension.so
bin/circle_fit: /usr/lib/x86_64-linux-gnu/libcxsparse.so
bin/circle_fit: g2o/examples/data_fitting/CMakeFiles/circle_fit.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/rodrigocoelho/Área de Trabalho/g2o-master/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../../../bin/circle_fit"
	cd "/home/rodrigocoelho/Área de Trabalho/g2o-master/g2o/examples/data_fitting" && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/circle_fit.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
g2o/examples/data_fitting/CMakeFiles/circle_fit.dir/build: bin/circle_fit

.PHONY : g2o/examples/data_fitting/CMakeFiles/circle_fit.dir/build

g2o/examples/data_fitting/CMakeFiles/circle_fit.dir/requires: g2o/examples/data_fitting/CMakeFiles/circle_fit.dir/circle_fit.cpp.o.requires

.PHONY : g2o/examples/data_fitting/CMakeFiles/circle_fit.dir/requires

g2o/examples/data_fitting/CMakeFiles/circle_fit.dir/clean:
	cd "/home/rodrigocoelho/Área de Trabalho/g2o-master/g2o/examples/data_fitting" && $(CMAKE_COMMAND) -P CMakeFiles/circle_fit.dir/cmake_clean.cmake
.PHONY : g2o/examples/data_fitting/CMakeFiles/circle_fit.dir/clean

g2o/examples/data_fitting/CMakeFiles/circle_fit.dir/depend:
	cd "/home/rodrigocoelho/Área de Trabalho/g2o-master" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/rodrigocoelho/Área de Trabalho/g2o-master" "/home/rodrigocoelho/Área de Trabalho/g2o-master/g2o/examples/data_fitting" "/home/rodrigocoelho/Área de Trabalho/g2o-master" "/home/rodrigocoelho/Área de Trabalho/g2o-master/g2o/examples/data_fitting" "/home/rodrigocoelho/Área de Trabalho/g2o-master/g2o/examples/data_fitting/CMakeFiles/circle_fit.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : g2o/examples/data_fitting/CMakeFiles/circle_fit.dir/depend

