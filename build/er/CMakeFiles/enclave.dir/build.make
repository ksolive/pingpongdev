# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_SOURCE_DIR = /home/azureuser/test/helloworld

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/azureuser/test/helloworld/build

# Include any dependencies generated for this target.
include er/CMakeFiles/enclave.dir/depend.make

# Include the progress variables for this target.
include er/CMakeFiles/enclave.dir/progress.make

# Include the compile flags for this target's objects.
include er/CMakeFiles/enclave.dir/flags.make

er/er_t.h: ../er.edl
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/azureuser/test/helloworld/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Generating er_t.h, er_t.c, er_args.h"
	cd /home/azureuser/test/helloworld/build/er && /opt/openenclave/bin/oeedger8r --trusted /home/azureuser/test/helloworld/er.edl --search-path /opt/openenclave/include --search-path /opt/openenclave/include/openenclave/edl/sgx

er/er_t.c: er/er_t.h
	@$(CMAKE_COMMAND) -E touch_nocreate er/er_t.c

er/er_args.h: er/er_t.h
	@$(CMAKE_COMMAND) -E touch_nocreate er/er_args.h

er/CMakeFiles/enclave.dir/enc.cpp.o: er/CMakeFiles/enclave.dir/flags.make
er/CMakeFiles/enclave.dir/enc.cpp.o: ../er/enc.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/azureuser/test/helloworld/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object er/CMakeFiles/enclave.dir/enc.cpp.o"
	cd /home/azureuser/test/helloworld/build/er && /usr/bin/clang++-11  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/enclave.dir/enc.cpp.o -c /home/azureuser/test/helloworld/er/enc.cpp

er/CMakeFiles/enclave.dir/enc.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/enclave.dir/enc.cpp.i"
	cd /home/azureuser/test/helloworld/build/er && /usr/bin/clang++-11 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/azureuser/test/helloworld/er/enc.cpp > CMakeFiles/enclave.dir/enc.cpp.i

er/CMakeFiles/enclave.dir/enc.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/enclave.dir/enc.cpp.s"
	cd /home/azureuser/test/helloworld/build/er && /usr/bin/clang++-11 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/azureuser/test/helloworld/er/enc.cpp -o CMakeFiles/enclave.dir/enc.cpp.s

er/CMakeFiles/enclave.dir/er_t.c.o: er/CMakeFiles/enclave.dir/flags.make
er/CMakeFiles/enclave.dir/er_t.c.o: er/er_t.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/azureuser/test/helloworld/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object er/CMakeFiles/enclave.dir/er_t.c.o"
	cd /home/azureuser/test/helloworld/build/er && /usr/bin/clang-11 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/enclave.dir/er_t.c.o   -c /home/azureuser/test/helloworld/build/er/er_t.c

er/CMakeFiles/enclave.dir/er_t.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/enclave.dir/er_t.c.i"
	cd /home/azureuser/test/helloworld/build/er && /usr/bin/clang-11 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/azureuser/test/helloworld/build/er/er_t.c > CMakeFiles/enclave.dir/er_t.c.i

er/CMakeFiles/enclave.dir/er_t.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/enclave.dir/er_t.c.s"
	cd /home/azureuser/test/helloworld/build/er && /usr/bin/clang-11 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/azureuser/test/helloworld/build/er/er_t.c -o CMakeFiles/enclave.dir/er_t.c.s

er/CMakeFiles/enclave.dir/oht_crypto_impl.cpp.o: er/CMakeFiles/enclave.dir/flags.make
er/CMakeFiles/enclave.dir/oht_crypto_impl.cpp.o: ../er/oht_crypto_impl.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/azureuser/test/helloworld/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object er/CMakeFiles/enclave.dir/oht_crypto_impl.cpp.o"
	cd /home/azureuser/test/helloworld/build/er && /usr/bin/clang++-11  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/enclave.dir/oht_crypto_impl.cpp.o -c /home/azureuser/test/helloworld/er/oht_crypto_impl.cpp

er/CMakeFiles/enclave.dir/oht_crypto_impl.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/enclave.dir/oht_crypto_impl.cpp.i"
	cd /home/azureuser/test/helloworld/build/er && /usr/bin/clang++-11 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/azureuser/test/helloworld/er/oht_crypto_impl.cpp > CMakeFiles/enclave.dir/oht_crypto_impl.cpp.i

er/CMakeFiles/enclave.dir/oht_crypto_impl.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/enclave.dir/oht_crypto_impl.cpp.s"
	cd /home/azureuser/test/helloworld/build/er && /usr/bin/clang++-11 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/azureuser/test/helloworld/er/oht_crypto_impl.cpp -o CMakeFiles/enclave.dir/oht_crypto_impl.cpp.s

er/CMakeFiles/enclave.dir/snoopy_par_obl_primitives_impl.cpp.o: er/CMakeFiles/enclave.dir/flags.make
er/CMakeFiles/enclave.dir/snoopy_par_obl_primitives_impl.cpp.o: ../er/snoopy_par_obl_primitives_impl.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/azureuser/test/helloworld/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object er/CMakeFiles/enclave.dir/snoopy_par_obl_primitives_impl.cpp.o"
	cd /home/azureuser/test/helloworld/build/er && /usr/bin/clang++-11  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/enclave.dir/snoopy_par_obl_primitives_impl.cpp.o -c /home/azureuser/test/helloworld/er/snoopy_par_obl_primitives_impl.cpp

er/CMakeFiles/enclave.dir/snoopy_par_obl_primitives_impl.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/enclave.dir/snoopy_par_obl_primitives_impl.cpp.i"
	cd /home/azureuser/test/helloworld/build/er && /usr/bin/clang++-11 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/azureuser/test/helloworld/er/snoopy_par_obl_primitives_impl.cpp > CMakeFiles/enclave.dir/snoopy_par_obl_primitives_impl.cpp.i

er/CMakeFiles/enclave.dir/snoopy_par_obl_primitives_impl.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/enclave.dir/snoopy_par_obl_primitives_impl.cpp.s"
	cd /home/azureuser/test/helloworld/build/er && /usr/bin/clang++-11 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/azureuser/test/helloworld/er/snoopy_par_obl_primitives_impl.cpp -o CMakeFiles/enclave.dir/snoopy_par_obl_primitives_impl.cpp.s

# Object files for target enclave
enclave_OBJECTS = \
"CMakeFiles/enclave.dir/enc.cpp.o" \
"CMakeFiles/enclave.dir/er_t.c.o" \
"CMakeFiles/enclave.dir/oht_crypto_impl.cpp.o" \
"CMakeFiles/enclave.dir/snoopy_par_obl_primitives_impl.cpp.o"

# External object files for target enclave
enclave_EXTERNAL_OBJECTS =

er/enclave: er/CMakeFiles/enclave.dir/enc.cpp.o
er/enclave: er/CMakeFiles/enclave.dir/er_t.c.o
er/enclave: er/CMakeFiles/enclave.dir/oht_crypto_impl.cpp.o
er/enclave: er/CMakeFiles/enclave.dir/snoopy_par_obl_primitives_impl.cpp.o
er/enclave: er/CMakeFiles/enclave.dir/build.make
er/enclave: /opt/openenclave/lib/openenclave/enclave/liboeenclave.a
er/enclave: /opt/openenclave/lib/openenclave/enclave/liboecryptombedtls.a
er/enclave: /opt/openenclave/lib/openenclave/enclave/liboelibc.a
er/enclave: /opt/openenclave/lib/openenclave/enclave/liboelibcxx.a
er/enclave: /opt/openenclave/lib/openenclave/enclave/libmbedtls.a
er/enclave: /opt/openenclave/lib/openenclave/enclave/libmbedx509.a
er/enclave: /opt/openenclave/lib/openenclave/enclave/libmbedcrypto.a
er/enclave: /opt/openenclave/lib/openenclave/enclave/liboelibc.a
er/enclave: /opt/openenclave/lib/openenclave/enclave/liboesyscall.a
er/enclave: /opt/openenclave/lib/openenclave/enclave/liboecore.a
er/enclave: er/CMakeFiles/enclave.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/azureuser/test/helloworld/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking CXX executable enclave"
	cd /home/azureuser/test/helloworld/build/er && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/enclave.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
er/CMakeFiles/enclave.dir/build: er/enclave

.PHONY : er/CMakeFiles/enclave.dir/build

er/CMakeFiles/enclave.dir/clean:
	cd /home/azureuser/test/helloworld/build/er && $(CMAKE_COMMAND) -P CMakeFiles/enclave.dir/cmake_clean.cmake
.PHONY : er/CMakeFiles/enclave.dir/clean

er/CMakeFiles/enclave.dir/depend: er/er_t.h
er/CMakeFiles/enclave.dir/depend: er/er_t.c
er/CMakeFiles/enclave.dir/depend: er/er_args.h
	cd /home/azureuser/test/helloworld/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/azureuser/test/helloworld /home/azureuser/test/helloworld/er /home/azureuser/test/helloworld/build /home/azureuser/test/helloworld/build/er /home/azureuser/test/helloworld/build/er/CMakeFiles/enclave.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : er/CMakeFiles/enclave.dir/depend

