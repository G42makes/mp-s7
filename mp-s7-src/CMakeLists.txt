cmake_minimum_required(VERSION 3.0)
project(MPTests VERSION 0.1 LANGUAGES C CXX)

add_library(RetroConsole
    retro/Console.cc
    retro/Console.h
    retro/ConsoleWindow.cc
    retro/ConsoleWindow.h
    retro/MacUtils.h
    retro/InitConsole.cc
    )
set_target_properties(RetroConsole
    PROPERTIES
        COMPILE_OPTIONS -ffunction-sections)

# different library name for Carbon
# (Carbon shares the powerpc-apple-macos/ directory with Classic PPC)
if(CMAKE_SYSTEM_NAME MATCHES RetroCarbon)
    set_target_properties(RetroConsole PROPERTIES OUTPUT_NAME RetroConsoleCarbon)
endif()
target_include_directories(RetroConsole PUBLIC .)

install(TARGETS RetroConsole  DESTINATION lib)


#App parts

file(GLOB micropython_py_SRC
	"../micropython/py/*.h"
	"../micropython/py/*.c"
	../micropython/lib/utils/stdout_helpers.c
	../micropython/ports/minimal/build/_frozen_mpy.c
	mpconfigport.h
	mphalport.h
	stringio.c
	main.c
	)
add_application(MPTests ${micropython_py_SRC})

target_include_directories(MPTests
        PUBLIC ../micropython/
	../micropython/ports/minimal/build/
        ./
    )

target_link_libraries(MPTests 
	RetroConsole
	#	MP
	)

