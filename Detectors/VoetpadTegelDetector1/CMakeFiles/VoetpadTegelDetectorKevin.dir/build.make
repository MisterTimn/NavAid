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
CMAKE_SOURCE_DIR = /home/g/Dropbox/project_beeldverwerking/Detectors/VoetpadTegelDetectorKevin

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/g/Dropbox/project_beeldverwerking/Detectors/VoetpadTegelDetectorKevin

# Include any dependencies generated for this target.
include CMakeFiles/VoetpadTegelDetectorKevin.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/VoetpadTegelDetectorKevin.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/VoetpadTegelDetectorKevin.dir/flags.make

CMakeFiles/VoetpadTegelDetectorKevin.dir/main.cpp.o: CMakeFiles/VoetpadTegelDetectorKevin.dir/flags.make
CMakeFiles/VoetpadTegelDetectorKevin.dir/main.cpp.o: main.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/g/Dropbox/project_beeldverwerking/Detectors/VoetpadTegelDetectorKevin/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/VoetpadTegelDetectorKevin.dir/main.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/VoetpadTegelDetectorKevin.dir/main.cpp.o -c /home/g/Dropbox/project_beeldverwerking/Detectors/VoetpadTegelDetectorKevin/main.cpp

CMakeFiles/VoetpadTegelDetectorKevin.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/VoetpadTegelDetectorKevin.dir/main.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/g/Dropbox/project_beeldverwerking/Detectors/VoetpadTegelDetectorKevin/main.cpp > CMakeFiles/VoetpadTegelDetectorKevin.dir/main.cpp.i

CMakeFiles/VoetpadTegelDetectorKevin.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/VoetpadTegelDetectorKevin.dir/main.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/g/Dropbox/project_beeldverwerking/Detectors/VoetpadTegelDetectorKevin/main.cpp -o CMakeFiles/VoetpadTegelDetectorKevin.dir/main.cpp.s

CMakeFiles/VoetpadTegelDetectorKevin.dir/main.cpp.o.requires:
.PHONY : CMakeFiles/VoetpadTegelDetectorKevin.dir/main.cpp.o.requires

CMakeFiles/VoetpadTegelDetectorKevin.dir/main.cpp.o.provides: CMakeFiles/VoetpadTegelDetectorKevin.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/VoetpadTegelDetectorKevin.dir/build.make CMakeFiles/VoetpadTegelDetectorKevin.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/VoetpadTegelDetectorKevin.dir/main.cpp.o.provides

CMakeFiles/VoetpadTegelDetectorKevin.dir/main.cpp.o.provides.build: CMakeFiles/VoetpadTegelDetectorKevin.dir/main.cpp.o

# Object files for target VoetpadTegelDetectorKevin
VoetpadTegelDetectorKevin_OBJECTS = \
"CMakeFiles/VoetpadTegelDetectorKevin.dir/main.cpp.o"

# External object files for target VoetpadTegelDetectorKevin
VoetpadTegelDetectorKevin_EXTERNAL_OBJECTS =

VoetpadTegelDetectorKevin: CMakeFiles/VoetpadTegelDetectorKevin.dir/main.cpp.o
VoetpadTegelDetectorKevin: CMakeFiles/VoetpadTegelDetectorKevin.dir/build.make
VoetpadTegelDetectorKevin: CMakeFiles/VoetpadTegelDetectorKevin.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable VoetpadTegelDetectorKevin"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/VoetpadTegelDetectorKevin.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/VoetpadTegelDetectorKevin.dir/build: VoetpadTegelDetectorKevin
.PHONY : CMakeFiles/VoetpadTegelDetectorKevin.dir/build

CMakeFiles/VoetpadTegelDetectorKevin.dir/requires: CMakeFiles/VoetpadTegelDetectorKevin.dir/main.cpp.o.requires
.PHONY : CMakeFiles/VoetpadTegelDetectorKevin.dir/requires

CMakeFiles/VoetpadTegelDetectorKevin.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/VoetpadTegelDetectorKevin.dir/cmake_clean.cmake
.PHONY : CMakeFiles/VoetpadTegelDetectorKevin.dir/clean

CMakeFiles/VoetpadTegelDetectorKevin.dir/depend:
	cd /home/g/Dropbox/project_beeldverwerking/Detectors/VoetpadTegelDetectorKevin && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/g/Dropbox/project_beeldverwerking/Detectors/VoetpadTegelDetectorKevin /home/g/Dropbox/project_beeldverwerking/Detectors/VoetpadTegelDetectorKevin /home/g/Dropbox/project_beeldverwerking/Detectors/VoetpadTegelDetectorKevin /home/g/Dropbox/project_beeldverwerking/Detectors/VoetpadTegelDetectorKevin /home/g/Dropbox/project_beeldverwerking/Detectors/VoetpadTegelDetectorKevin/CMakeFiles/VoetpadTegelDetectorKevin.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/VoetpadTegelDetectorKevin.dir/depend

