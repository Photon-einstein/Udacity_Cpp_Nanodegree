# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.18

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/tiago/Desktop/Udacity_courses/1-C++_Developer/5-CppND-Capstone

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/tiago/Desktop/Udacity_courses/1-C++_Developer/5-CppND-Capstone/build

# Include any dependencies generated for this target.
include CMakeFiles/capstone.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/capstone.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/capstone.dir/flags.make

CMakeFiles/capstone.dir/src/CapstoneParser.cpp.o: CMakeFiles/capstone.dir/flags.make
CMakeFiles/capstone.dir/src/CapstoneParser.cpp.o: ../src/CapstoneParser.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tiago/Desktop/Udacity_courses/1-C++_Developer/5-CppND-Capstone/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/capstone.dir/src/CapstoneParser.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/capstone.dir/src/CapstoneParser.cpp.o -c /home/tiago/Desktop/Udacity_courses/1-C++_Developer/5-CppND-Capstone/src/CapstoneParser.cpp

CMakeFiles/capstone.dir/src/CapstoneParser.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/capstone.dir/src/CapstoneParser.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tiago/Desktop/Udacity_courses/1-C++_Developer/5-CppND-Capstone/src/CapstoneParser.cpp > CMakeFiles/capstone.dir/src/CapstoneParser.cpp.i

CMakeFiles/capstone.dir/src/CapstoneParser.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/capstone.dir/src/CapstoneParser.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tiago/Desktop/Udacity_courses/1-C++_Developer/5-CppND-Capstone/src/CapstoneParser.cpp -o CMakeFiles/capstone.dir/src/CapstoneParser.cpp.s

CMakeFiles/capstone.dir/src/Elevator.cpp.o: CMakeFiles/capstone.dir/flags.make
CMakeFiles/capstone.dir/src/Elevator.cpp.o: ../src/Elevator.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tiago/Desktop/Udacity_courses/1-C++_Developer/5-CppND-Capstone/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/capstone.dir/src/Elevator.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/capstone.dir/src/Elevator.cpp.o -c /home/tiago/Desktop/Udacity_courses/1-C++_Developer/5-CppND-Capstone/src/Elevator.cpp

CMakeFiles/capstone.dir/src/Elevator.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/capstone.dir/src/Elevator.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tiago/Desktop/Udacity_courses/1-C++_Developer/5-CppND-Capstone/src/Elevator.cpp > CMakeFiles/capstone.dir/src/Elevator.cpp.i

CMakeFiles/capstone.dir/src/Elevator.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/capstone.dir/src/Elevator.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tiago/Desktop/Udacity_courses/1-C++_Developer/5-CppND-Capstone/src/Elevator.cpp -o CMakeFiles/capstone.dir/src/Elevator.cpp.s

CMakeFiles/capstone.dir/src/Floor.cpp.o: CMakeFiles/capstone.dir/flags.make
CMakeFiles/capstone.dir/src/Floor.cpp.o: ../src/Floor.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tiago/Desktop/Udacity_courses/1-C++_Developer/5-CppND-Capstone/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/capstone.dir/src/Floor.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/capstone.dir/src/Floor.cpp.o -c /home/tiago/Desktop/Udacity_courses/1-C++_Developer/5-CppND-Capstone/src/Floor.cpp

CMakeFiles/capstone.dir/src/Floor.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/capstone.dir/src/Floor.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tiago/Desktop/Udacity_courses/1-C++_Developer/5-CppND-Capstone/src/Floor.cpp > CMakeFiles/capstone.dir/src/Floor.cpp.i

CMakeFiles/capstone.dir/src/Floor.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/capstone.dir/src/Floor.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tiago/Desktop/Udacity_courses/1-C++_Developer/5-CppND-Capstone/src/Floor.cpp -o CMakeFiles/capstone.dir/src/Floor.cpp.s

CMakeFiles/capstone.dir/src/Scheduler.cpp.o: CMakeFiles/capstone.dir/flags.make
CMakeFiles/capstone.dir/src/Scheduler.cpp.o: ../src/Scheduler.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tiago/Desktop/Udacity_courses/1-C++_Developer/5-CppND-Capstone/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/capstone.dir/src/Scheduler.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/capstone.dir/src/Scheduler.cpp.o -c /home/tiago/Desktop/Udacity_courses/1-C++_Developer/5-CppND-Capstone/src/Scheduler.cpp

CMakeFiles/capstone.dir/src/Scheduler.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/capstone.dir/src/Scheduler.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tiago/Desktop/Udacity_courses/1-C++_Developer/5-CppND-Capstone/src/Scheduler.cpp > CMakeFiles/capstone.dir/src/Scheduler.cpp.i

CMakeFiles/capstone.dir/src/Scheduler.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/capstone.dir/src/Scheduler.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tiago/Desktop/Udacity_courses/1-C++_Developer/5-CppND-Capstone/src/Scheduler.cpp -o CMakeFiles/capstone.dir/src/Scheduler.cpp.s

CMakeFiles/capstone.dir/src/main.cpp.o: CMakeFiles/capstone.dir/flags.make
CMakeFiles/capstone.dir/src/main.cpp.o: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tiago/Desktop/Udacity_courses/1-C++_Developer/5-CppND-Capstone/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/capstone.dir/src/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/capstone.dir/src/main.cpp.o -c /home/tiago/Desktop/Udacity_courses/1-C++_Developer/5-CppND-Capstone/src/main.cpp

CMakeFiles/capstone.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/capstone.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tiago/Desktop/Udacity_courses/1-C++_Developer/5-CppND-Capstone/src/main.cpp > CMakeFiles/capstone.dir/src/main.cpp.i

CMakeFiles/capstone.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/capstone.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tiago/Desktop/Udacity_courses/1-C++_Developer/5-CppND-Capstone/src/main.cpp -o CMakeFiles/capstone.dir/src/main.cpp.s

# Object files for target capstone
capstone_OBJECTS = \
"CMakeFiles/capstone.dir/src/CapstoneParser.cpp.o" \
"CMakeFiles/capstone.dir/src/Elevator.cpp.o" \
"CMakeFiles/capstone.dir/src/Floor.cpp.o" \
"CMakeFiles/capstone.dir/src/Scheduler.cpp.o" \
"CMakeFiles/capstone.dir/src/main.cpp.o"

# External object files for target capstone
capstone_EXTERNAL_OBJECTS =

capstone: CMakeFiles/capstone.dir/src/CapstoneParser.cpp.o
capstone: CMakeFiles/capstone.dir/src/Elevator.cpp.o
capstone: CMakeFiles/capstone.dir/src/Floor.cpp.o
capstone: CMakeFiles/capstone.dir/src/Scheduler.cpp.o
capstone: CMakeFiles/capstone.dir/src/main.cpp.o
capstone: CMakeFiles/capstone.dir/build.make
capstone: CMakeFiles/capstone.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/tiago/Desktop/Udacity_courses/1-C++_Developer/5-CppND-Capstone/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking CXX executable capstone"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/capstone.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/capstone.dir/build: capstone

.PHONY : CMakeFiles/capstone.dir/build

CMakeFiles/capstone.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/capstone.dir/cmake_clean.cmake
.PHONY : CMakeFiles/capstone.dir/clean

CMakeFiles/capstone.dir/depend:
	cd /home/tiago/Desktop/Udacity_courses/1-C++_Developer/5-CppND-Capstone/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/tiago/Desktop/Udacity_courses/1-C++_Developer/5-CppND-Capstone /home/tiago/Desktop/Udacity_courses/1-C++_Developer/5-CppND-Capstone /home/tiago/Desktop/Udacity_courses/1-C++_Developer/5-CppND-Capstone/build /home/tiago/Desktop/Udacity_courses/1-C++_Developer/5-CppND-Capstone/build /home/tiago/Desktop/Udacity_courses/1-C++_Developer/5-CppND-Capstone/build/CMakeFiles/capstone.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/capstone.dir/depend
