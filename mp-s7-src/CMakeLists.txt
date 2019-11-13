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

#Generate the MP moduledefs header file:
# TODO: generate or at least make an array for this file list, I think I need it more spots then here
add_custom_target(
 gen_moduledefs ALL
 COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/../micropython/py/makemoduledefs.py --vpath="${CMAKE_CURRENT_SOURCE_DIR},${CMAKE_CURRENT_SOURCE_DIR}/../micropython," py/mpstate.c py/malloc.c py/gc.c py/pystack.c py/qstr.c py/vstr.c py/mpprint.c py/unicode.c py/mpz.c py/reader.c py/lexer.c py/parse.c py/scope.c py/compile.c py/emitcommon.c py/emitbc.c py/asmbase.c py/asmx64.c py/emitnx64.c py/asmx86.c py/emitnx86.c py/asmthumb.c py/emitnthumb.c py/emitinlinethumb.c py/asmarm.c py/emitnarm.c py/asmxtensa.c py/emitnxtensa.c py/emitinlinextensa.c py/emitnxtensawin.c py/formatfloat.c py/parsenumbase.c py/parsenum.c py/emitglue.c py/persistentcode.c py/runtime.c py/runtime_utils.c py/scheduler.c py/nativeglue.c py/ringbuf.c py/stackctrl.c py/argcheck.c py/warning.c py/profile.c py/map.c py/obj.c py/objarray.c py/objattrtuple.c py/objbool.c py/objboundmeth.c py/objcell.c py/objclosure.c py/objcomplex.c py/objdeque.c py/objdict.c py/objenumerate.c py/objexcept.c py/objfilter.c py/objfloat.c py/objfun.c py/objgenerator.c py/objgetitemiter.c py/objint.c py/objint_longlong.c py/objint_mpz.c py/objlist.c py/objmap.c py/objmodule.c py/objobject.c py/objpolyiter.c py/objproperty.c py/objnone.c py/objnamedtuple.c py/objrange.c py/objreversed.c py/objset.c py/objsingleton.c py/objslice.c py/objstr.c py/objstrunicode.c py/objstringio.c py/objtuple.c py/objtype.c py/objzip.c py/opmethods.c py/sequence.c py/stream.c py/binary.c py/builtinimport.c py/builtinevex.c py/builtinhelp.c py/modarray.c py/modbuiltins.c py/modcollections.c py/modgc.c py/modio.c py/modmath.c py/modcmath.c py/modmicropython.c py/modstruct.c py/modsys.c py/moduerrno.c py/modthread.c py/vm.c py/bc.c py/showbc.c py/repl.c py/smallint.c py/frozenmod.c extmod/moductypes.c extmod/modujson.c extmod/modure.c extmod/moduzlib.c extmod/moduheapq.c extmod/modutimeq.c extmod/moduhashlib.c extmod/moducryptolib.c extmod/modubinascii.c extmod/virtpin.c extmod/machine_mem.c extmod/machine_pinbase.c extmod/machine_signal.c extmod/machine_pulse.c extmod/machine_i2c.c extmod/machine_spi.c extmod/modbluetooth.c extmod/modussl_axtls.c extmod/modussl_mbedtls.c extmod/modurandom.c extmod/moduselect.c extmod/moduwebsocket.c extmod/modwebrepl.c extmod/modframebuf.c extmod/vfs.c extmod/vfs_blockdev.c extmod/vfs_reader.c extmod/vfs_posix.c extmod/vfs_posix_file.c extmod/vfs_fat.c extmod/vfs_fat_diskio.c extmod/vfs_fat_file.c extmod/vfs_lfs.c extmod/utime_mphal.c extmod/uos_dupterm.c lib/embed/abort_.c lib/utils/printf.c build/genhdr/moduledefs.h > ${PROJECT_BINARY_DIR}/genhdr/moduledefs.h
 BYPRODUCTS ${PROJECT_BINARY_DIR}/genhdr/moduledefs.h
 COMMENT "Generating moduledefs.h"
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
	gen_moduledefs
	)

target_link_libraries(MicroPython 
	RetroConsole
	mp_lib_utils
	mp_lib_readline
	mp_py
	)

