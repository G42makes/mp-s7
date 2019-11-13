cmake_minimum_required(VERSION 3.0)
project(MicroPython VERSION 0.0.1 LANGUAGES C CXX)

find_package(PythonInterp)

#Create a location to store the generated header files
#Ref: https://stackoverflow.com/a/3702233
file(MAKE_DIRECTORY ${PROJECT_BINARY_DIR}/genhdr)

#Generage the MP version header file:
add_custom_target(
 gen_mpversion ALL
 COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/../micropython/py/makeversionhdr.py ${PROJECT_BINARY_DIR}/genhdr/mpversion.h
 BYPRODUCTS ${PROJECT_BINARY_DIR}/genhdr/mpversion.h
 COMMENT "Generating mpversion.h"
)

#Retro68 Console library - modififed
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

#micropython/lib/utils - library
add_library(mp_lib_utils
        ../micropython/lib/utils/stdout_helpers.c
	../micropython/lib/utils/pyexec.h
	../micropython/lib/utils/pyexec.c
	)
target_include_directories(mp_lib_utils PUBLIC
	../micropython/
	../micropython/ports/minimal/build/
	./
	)

#micropython/lib/mp-readline - library
add_library(mp_lib_readline
	../micropython/lib/mp-readline/readline.h
	../micropython/lib/mp-readline/readline.c
	)
target_include_directories(mp_lib_readline PUBLIC
        ../micropython/
        ../micropython/ports/minimal/build/
        ./
        )

#micropython/py - main codebase
file(GLOB mp_py_SRC
        "../micropython/py/*.c"
        ../micropython/lib/utils/stdout_helpers.c		#TODO: can I get rid of this line?
	#../micropython/ports/minimal/build/_frozen_mpy.c
	mpconfigport.h
	mphalport.h
	stringio.cc
	)
add_library(mp_py ${mp_py_SRC})
target_include_directories(mp_py PUBLIC
	../micropython/
        ../micropython/ports/minimal/build/
        ./
        )


#App parts

file(GLOB micropython_SRC
	#../micropython/ports/minimal/build/_frozen_mpy.c
	mpconfigport.h
	mphalport.h
	mphalport.c
	stringio.cc
	main.cc
	)
add_application(MicroPython ${micropython_SRC})

target_include_directories(MicroPython
        PUBLIC ../micropython/
	./
	../micropython/ports/minimal/build/
    )

add_dependencies(MicroPython 
	gen_mpversion
	)

target_link_libraries(MicroPython 
	RetroConsole
	mp_lib_utils
	mp_lib_readline
	mp_py
	)

