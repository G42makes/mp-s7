#Initial version referenced from: https://github.com/macosten/PetProject-m68k/blob/master/CMakeLists.txt

# To use this example as a standalone project using CMake:
# mkdir build
# cd build
# cmake .. -DCMAKE_TOOLCHAIN_FILE=path/to/Retro68-build/toolchain/m68k-apple-macos/cmake/retro68.toolchain.cmake
# make

cmake_minimum_required(VERSION 2.8)

add_application(MicroPython
	main.c 
	uart_core.c 
	#lib/utils/printf.c 
	#lib/utils/stdout_helpers.c 
	#lib/utils/pyexec.c 
	#lib/libc/string0.c 
	#lib/mp-readline/readline.c 
	#$(BUILD)/_frozen_mpy.c 
	)

# Enable -ffunction-sections and -gc-sections to make the app as small as possible
# On 68K, also enable --mac-single to build it as a single-segment app (so that this code path doesn't rot)
set_target_properties(MicroPython PROPERTIES COMPILE_OPTIONS -ffunction-sections)
if(CMAKE_SYSTEM_NAME MATCHES Retro68)
	set_target_properties(MicroPython PROPERTIES LINK_FLAGS "-Wl,-gc-sections -Wl,--mac-single")

else()
	set_target_properties(MicroPython PROPERTIES LINK_FLAGS "-Wl,-gc-sections")
endif()
