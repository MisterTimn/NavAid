# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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
CMAKE_SOURCE_DIR = /home/g/Dropbox/project_beeldverwerking/Detectors/KleineVierkanteTegelDetectorPieter

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/g/Dropbox/project_beeldverwerking/Detectors/KleineVierkanteTegelDetectorPieter

# Include any dependencies generated for this target.
include CMakeFiles/KleineVierkanteTegelDetectorPieter.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/KleineVierkanteTegelDetectorPieter.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/KleineVierkanteTegelDetectorPieter.dir/flags.make

CMakeFiles/KleineVierkanteTegelDetectorPieter.dir/main.cpp.o: CMakeFiles/KleineVierkanteTegelDetectorPieter.dir/flags.make
CMakeFiles/KleineVierkanteTegelDetectorPieter.dir/main.cpp.o: main.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/g/Dropbox/project_beeldverwerking/Detectors/KleineVierkanteTegelDetectorPieter/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/KleineVierkanteTegelDetectorPieter.dir/main.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/KleineVierkanteTegelDetectorPieter.dir/main.cpp.o -c /home/g/Dropbox/project_beeldverwerking/Detectors/KleineVierkanteTegelDetectorPieter/main.cpp

CMakeFiles/KleineVierkanteTegelDetectorPieter.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/KleineVierkanteTegelDetectorPieter.dir/main.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/g/Dropbox/project_beeldverwerking/Detectors/KleineVierkanteTegelDetectorPieter/main.cpp > CMakeFiles/KleineVierkanteTegelDetectorPieter.dir/main.cpp.i

CMakeFiles/KleineVierkanteTegelDetectorPieter.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/KleineVierkanteTegelDetectorPieter.dir/main.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/g/Dropbox/project_beeldverwerking/Detectors/KleineVierkanteTegelDetectorPieter/main.cpp -o CMakeFiles/KleineVierkanteTegelDetectorPieter.dir/main.cpp.s

CMakeFiles/KleineVierkanteTegelDetectorPieter.dir/main.cpp.o.requires:
.PHONY : CMakeFiles/KleineVierkanteTegelDetectorPieter.dir/main.cpp.o.requires

CMakeFiles/KleineVierkanteTegelDetectorPieter.dir/main.cpp.o.provides: CMakeFiles/KleineVierkanteTegelDetectorPieter.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/KleineVierkanteTegelDetectorPieter.dir/build.make CMakeFiles/KleineVierkanteTegelDetectorPieter.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/KleineVierkanteTegelDetectorPieter.dir/main.cpp.o.provides

CMakeFiles/KleineVierkanteTegelDetectorPieter.dir/main.cpp.o.provides.build: CMakeFiles/KleineVierkanteTegelDetectorPieter.dir/main.cpp.o

# Object files for target KleineVierkanteTegelDetectorPieter
KleineVierkanteTegelDetectorPieter_OBJECTS = \
"CMakeFiles/KleineVierkanteTegelDetectorPieter.dir/main.cpp.o"

# External object files for target KleineVierkanteTegelDetectorPieter
KleineVierkanteTegelDetectorPieter_EXTERNAL_OBJECTS =

KleineVierkanteTegelDetectorPieter: CMakeFiles/KleineVierkanteTegelDetectorPieter.dir/main.cpp.o
KleineVierkanteTegelDetectorPieter: CMakeFiles/KleineVierkanteTegelDetectorPieter.dir/build.make
KleineVierkanteTegelDetectorPieter: CMakeFiles/KleineVierkanteTegelDetectorPieter.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable KleineVierkanteTegelDetectorPieter"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/KleineVierkanteTegelDetectorPieter.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/KleineVierkanteTegelDetectorPieter.dir/build: KleineVierkanteTegelDetectorPieter
.PHONY : CMakeFiles/KleineVierkanteTegelDetectorPieter.dir/build

CMakeFiles/KleineVierkanteTegelDetectorPieter.dir/requires: CMakeFiles/KleineVierkanteTegelDetectorPieter.dir/main.cpp.o.requires
.PHONY : CMakeFiles/KleineVierkanteTegelDetectorPieter.dir/requires

CMakeFiles/KleineVierkanteTegelDetectorPieter.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/KleineVierkanteTegelDetectorPieter.dir/cmake_clean.cmake
.PHONY : CMakeFiles/KleineVierkanteTegelDetectorPieter.dir/clean

CMakeFiles/KleineVierkanteTegelDetectorPieter.dir/depend:
	cd /home/g/Dropbox/project_beeldverwerking/Detectors/KleineVierkanteTegelDetectorPieter && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/g/Dropbox/project_beeldverwerking/Detectors/KleineVierkanteTegelDetectorPieter /home/g/Dropbox/project_beeldverwerking/Detectors/KleineVierkanteTegelDetectorPieter /home/g/Dropbox/project_beeldverwerking/Detectors/KleineVierkanteTegelDetectorPieter /home/g/Dropbox/project_beeldverwerking/Detectors/KleineVierkanteTegelDetectorPieter /home/g/Dropbox/project_beeldverwerking/Detectors/KleineVierkanteTegelDetectorPieter/CMakeFiles/KleineVierkanteTegelDetectorPieter.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/KleineVierkanteTegelDetectorPieter.dir/depend
