cmake_minimum_required(VERSION 3.0)
project(MicroPython VERSION 0.0.1 LANGUAGES C CXX)

find_package(PythonInterp)

#Create a location to store the generated header files
#Ref: https://stackoverflow.com/a/3702233
file(MAKE_DIRECTORY ${PROJECT_BINARY_DIR}/genhdr)

#Generage the MP version header file:
add_custom_command(
	OUTPUT ${PROJECT_BINARY_DIR}/genhdr/mpversion.h
	COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/../micropython/py/makeversionhdr.py ${PROJECT_BINARY_DIR}/genhdr/mpversion.h
	)
add_custom_target(
 	gen_mpversion ALL
 	DEPENDS ${PROJECT_BINARY_DIR}/genhdr/mpversion.h
)

#Generate the MP moduledefs header file:
# TODO: generate or at least make an array for this file list, I think I need it more spots then here
add_custom_command(
	OUTPUT ${PROJECT_BINARY_DIR}/genhdr/moduledefs.h
	COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/../micropython/py/makemoduledefs.py --vpath="${CMAKE_CURRENT_SOURCE_DIR},${CMAKE_CURRENT_SOURCE_DIR}/../micropython," py/mpstate.c py/malloc.c py/gc.c py/pystack.c py/qstr.c py/vstr.c py/mpprint.c py/unicode.c py/mpz.c py/reader.c py/lexer.c py/parse.c py/scope.c py/compile.c py/emitcommon.c py/emitbc.c py/asmbase.c py/asmx64.c py/emitnx64.c py/asmx86.c py/emitnx86.c py/asmthumb.c py/emitnthumb.c py/emitinlinethumb.c py/asmarm.c py/emitnarm.c py/asmxtensa.c py/emitnxtensa.c py/emitinlinextensa.c py/emitnxtensawin.c py/formatfloat.c py/parsenumbase.c py/parsenum.c py/emitglue.c py/persistentcode.c py/runtime.c py/runtime_utils.c py/scheduler.c py/nativeglue.c py/ringbuf.c py/stackctrl.c py/argcheck.c py/warning.c py/profile.c py/map.c py/obj.c py/objarray.c py/objattrtuple.c py/objbool.c py/objboundmeth.c py/objcell.c py/objclosure.c py/objcomplex.c py/objdeque.c py/objdict.c py/objenumerate.c py/objexcept.c py/objfilter.c py/objfloat.c py/objfun.c py/objgenerator.c py/objgetitemiter.c py/objint.c py/objint_longlong.c py/objint_mpz.c py/objlist.c py/objmap.c py/objmodule.c py/objobject.c py/objpolyiter.c py/objproperty.c py/objnone.c py/objnamedtuple.c py/objrange.c py/objreversed.c py/objset.c py/objsingleton.c py/objslice.c py/objstr.c py/objstrunicode.c py/objstringio.c py/objtuple.c py/objtype.c py/objzip.c py/opmethods.c py/sequence.c py/stream.c py/binary.c py/builtinimport.c py/builtinevex.c py/builtinhelp.c py/modarray.c py/modbuiltins.c py/modcollections.c py/modgc.c py/modio.c py/modmath.c py/modcmath.c py/modmicropython.c py/modstruct.c py/modsys.c py/moduerrno.c py/modthread.c py/vm.c py/bc.c py/showbc.c py/repl.c py/smallint.c py/frozenmod.c extmod/moductypes.c extmod/modujson.c extmod/modure.c extmod/moduzlib.c extmod/moduheapq.c extmod/modutimeq.c extmod/moduhashlib.c extmod/moducryptolib.c extmod/modubinascii.c extmod/virtpin.c extmod/machine_mem.c extmod/machine_pinbase.c extmod/machine_signal.c extmod/machine_pulse.c extmod/machine_i2c.c extmod/machine_spi.c extmod/modbluetooth.c extmod/modussl_axtls.c extmod/modussl_mbedtls.c extmod/modurandom.c extmod/moduselect.c extmod/moduwebsocket.c extmod/modwebrepl.c extmod/modframebuf.c extmod/vfs.c extmod/vfs_blockdev.c extmod/vfs_reader.c extmod/vfs_posix.c extmod/vfs_posix_file.c extmod/vfs_fat.c extmod/vfs_fat_diskio.c extmod/vfs_fat_file.c extmod/vfs_lfs.c extmod/utime_mphal.c extmod/uos_dupterm.c lib/embed/abort_.c lib/utils/printf.c build/genhdr/moduledefs.h > ${PROJECT_BINARY_DIR}/genhdr/moduledefs.h
	)
add_custom_target(
 	gen_moduledefs ALL
 	DEPENDS ${PROJECT_BINARY_DIR}/genhdr/moduledefs.h
)

#Generate the qstr.i.last file
#TODO: check if this list matches the list above
#TODO: check the include folders listed here, they need updating more
#TODO: verify this is the output we need, it's too big and dynamic to diff on the baseline
add_custom_command(
	OUTPUT ${PROJECT_BINARY_DIR}/genhdr/qstr.i.last
 	COMMAND ${CMAKE_C_COMPILER} -E -DNO_QSTR -Ibuild/tmp -I${CMAKE_CURRENT_SOURCE_DIR} -I${CMAKE_CURRENT_SOURCE_DIR}/../micropython -I${PROJECT_BINARY_DIR} -Wall -Werror -std=c99  -Os -DNDEBUG -fdata-sections -ffunction-sections ${CMAKE_CURRENT_SOURCE_DIR}/../micropython/py/mpstate.c ${CMAKE_CURRENT_SOURCE_DIR}/../micropython/py/malloc.c ${CMAKE_CURRENT_SOURCE_DIR}/../micropython/py/gc.c ${CMAKE_CURRENT_SOURCE_DIR}/../micropython/py/pystack.c ${CMAKE_CURRENT_SOURCE_DIR}/../micropython/py/qstr.c ${CMAKE_CURRENT_SOURCE_DIR}/../micropython/py/vstr.c ${CMAKE_CURRENT_SOURCE_DIR}/../micropython/py/mpprint.c ${CMAKE_CURRENT_SOURCE_DIR}/../micropython/py/unicode.c ${CMAKE_CURRENT_SOURCE_DIR}/../micropython/py/mpz.c ${CMAKE_CURRENT_SOURCE_DIR}/../micropython/py/reader.c ${CMAKE_CURRENT_SOURCE_DIR}/../micropython/py/lexer.c ${CMAKE_CURRENT_SOURCE_DIR}/../micropython/py/parse.c ${CMAKE_CURRENT_SOURCE_DIR}/../micropython/py/scope.c ${CMAKE_CURRENT_SOURCE_DIR}/../micropython/py/compile.c ${CMAKE_CURRENT_SOURCE_DIR}/../micropython/py/emitcommon.c ${CMAKE_CURRENT_SOURCE_DIR}/../micropython/py/emitbc.c ${CMAKE_CURRENT_SOURCE_DIR}/../micropython/py/asmbase.c ${CMAKE_CURRENT_SOURCE_DIR}/../micropython/py/asmx64.c ${CMAKE_CURRENT_SOURCE_DIR}/../micropython/py/emitnx64.c ${CMAKE_CURRENT_SOURCE_DIR}/../micropython/py/asmx86.c ${CMAKE_CURRENT_SOURCE_DIR}/../micropython/py/emitnx86.c ${CMAKE_CURRENT_SOURCE_DIR}/../micropython/py/asmthumb.c ${CMAKE_CURRENT_SOURCE_DIR}/../micropython/py/emitnthumb.c ${CMAKE_CURRENT_SOURCE_DIR}/../micropython/py/emitinlinethumb.c ${CMAKE_CURRENT_SOURCE_DIR}/../micropython/py/asmarm.c ${CMAKE_CURRENT_SOURCE_DIR}/../micropython/py/emitnarm.c ${CMAKE_CURRENT_SOURCE_DIR}/../micropython/py/asmxtensa.c ${CMAKE_CURRENT_SOURCE_DIR}/../micropython/py/emitnxtensa.c ${CMAKE_CURRENT_SOURCE_DIR}/../micropython/py/emitinlinextensa.c ${CMAKE_CURRENT_SOURCE_DIR}/../micropython/py/emitnxtensawin.c ${CMAKE_CURRENT_SOURCE_DIR}/../micropython/py/formatfloat.c ${CMAKE_CURRENT_SOURCE_DIR}/../micropython/py/parsenumbase.c ${CMAKE_CURRENT_SOURCE_DIR}/../micropython/py/parsenum.c ${CMAKE_CURRENT_SOURCE_DIR}/../micropython/py/emitglue.c ${CMAKE_CURRENT_SOURCE_DIR}/../micropython/py/persistentcode.c ${CMAKE_CURRENT_SOURCE_DIR}/../micropython/py/runtime.c ${CMAKE_CURRENT_SOURCE_DIR}/../micropython/py/runtime_utils.c ${CMAKE_CURRENT_SOURCE_DIR}/../micropython/py/scheduler.c ${CMAKE_CURRENT_SOURCE_DIR}/../micropython/py/nativeglue.c ${CMAKE_CURRENT_SOURCE_DIR}/../micropython/py/ringbuf.c ${CMAKE_CURRENT_SOURCE_DIR}/../micropython/py/stackctrl.c ${CMAKE_CURRENT_SOURCE_DIR}/../micropython/py/argcheck.c ${CMAKE_CURRENT_SOURCE_DIR}/../micropython/py/warning.c ${CMAKE_CURRENT_SOURCE_DIR}/../micropython/py/profile.c ${CMAKE_CURRENT_SOURCE_DIR}/../micropython/py/map.c ${CMAKE_CURRENT_SOURCE_DIR}/../micropython/py/obj.c ${CMAKE_CURRENT_SOURCE_DIR}/../micropython/py/objarray.c ${CMAKE_CURRENT_SOURCE_DIR}/../micropython/py/objattrtuple.c ${CMAKE_CURRENT_SOURCE_DIR}/../micropython/py/objbool.c ${CMAKE_CURRENT_SOURCE_DIR}/../micropython/py/objboundmeth.c ${CMAKE_CURRENT_SOURCE_DIR}/../micropython/py/objcell.c ${CMAKE_CURRENT_SOURCE_DIR}/../micropython/py/objclosure.c ${CMAKE_CURRENT_SOURCE_DIR}/../micropython/py/objcomplex.c ${CMAKE_CURRENT_SOURCE_DIR}/../micropython/py/objdeque.c ${CMAKE_CURRENT_SOURCE_DIR}/../micropython/py/objdict.c ${CMAKE_CURRENT_SOURCE_DIR}/../micropython/py/objenumerate.c ${CMAKE_CURRENT_SOURCE_DIR}/../micropython/py/objexcept.c ${CMAKE_CURRENT_SOURCE_DIR}/../micropython/py/objfilter.c ${CMAKE_CURRENT_SOURCE_DIR}/../micropython/py/objfloat.c ${CMAKE_CURRENT_SOURCE_DIR}/../micropython/py/objfun.c ${CMAKE_CURRENT_SOURCE_DIR}/../micropython/py/objgenerator.c ${CMAKE_CURRENT_SOURCE_DIR}/../micropython/py/objgetitemiter.c ${CMAKE_CURRENT_SOURCE_DIR}/../micropython/py/objint.c ${CMAKE_CURRENT_SOURCE_DIR}/../micropython/py/objint_longlong.c ${CMAKE_CURRENT_SOURCE_DIR}/../micropython/py/objint_mpz.c ${CMAKE_CURRENT_SOURCE_DIR}/../micropython/py/objlist.c ${CMAKE_CURRENT_SOURCE_DIR}/../micropython/py/objmap.c ${CMAKE_CURRENT_SOURCE_DIR}/../micropython/py/objmodule.c ${CMAKE_CURRENT_SOURCE_DIR}/../micropython/py/objobject.c ${CMAKE_CURRENT_SOURCE_DIR}/../micropython/py/objpolyiter.c ${CMAKE_CURRENT_SOURCE_DIR}/../micropython/py/objproperty.c ${CMAKE_CURRENT_SOURCE_DIR}/../micropython/py/objnone.c ${CMAKE_CURRENT_SOURCE_DIR}/../micropython/py/objnamedtuple.c ${CMAKE_CURRENT_SOURCE_DIR}/../micropython/py/objrange.c ${CMAKE_CURRENT_SOURCE_DIR}/../micropython/py/objreversed.c ${CMAKE_CURRENT_SOURCE_DIR}/../micropython/py/objset.c ${CMAKE_CURRENT_SOURCE_DIR}/../micropython/py/objsingleton.c ${CMAKE_CURRENT_SOURCE_DIR}/../micropython/py/objslice.c ${CMAKE_CURRENT_SOURCE_DIR}/../micropython/py/objstr.c ${CMAKE_CURRENT_SOURCE_DIR}/../micropython/py/objstrunicode.c ${CMAKE_CURRENT_SOURCE_DIR}/../micropython/py/objstringio.c ${CMAKE_CURRENT_SOURCE_DIR}/../micropython/py/objtuple.c ${CMAKE_CURRENT_SOURCE_DIR}/../micropython/py/objtype.c ${CMAKE_CURRENT_SOURCE_DIR}/../micropython/py/objzip.c ${CMAKE_CURRENT_SOURCE_DIR}/../micropython/py/opmethods.c ${CMAKE_CURRENT_SOURCE_DIR}/../micropython/py/sequence.c ${CMAKE_CURRENT_SOURCE_DIR}/../micropython/py/stream.c ${CMAKE_CURRENT_SOURCE_DIR}/../micropython/py/binary.c ${CMAKE_CURRENT_SOURCE_DIR}/../micropython/py/builtinimport.c ${CMAKE_CURRENT_SOURCE_DIR}/../micropython/py/builtinevex.c ${CMAKE_CURRENT_SOURCE_DIR}/../micropython/py/builtinhelp.c ${CMAKE_CURRENT_SOURCE_DIR}/../micropython/py/modarray.c ${CMAKE_CURRENT_SOURCE_DIR}/../micropython/py/modbuiltins.c ${CMAKE_CURRENT_SOURCE_DIR}/../micropython/py/modcollections.c ${CMAKE_CURRENT_SOURCE_DIR}/../micropython/py/modgc.c ${CMAKE_CURRENT_SOURCE_DIR}/../micropython/py/modio.c ${CMAKE_CURRENT_SOURCE_DIR}/../micropython/py/modmath.c ${CMAKE_CURRENT_SOURCE_DIR}/../micropython/py/modcmath.c ${CMAKE_CURRENT_SOURCE_DIR}/../micropython/py/modmicropython.c ${CMAKE_CURRENT_SOURCE_DIR}/../micropython/py/modstruct.c ${CMAKE_CURRENT_SOURCE_DIR}/../micropython/py/modsys.c ${CMAKE_CURRENT_SOURCE_DIR}/../micropython/py/moduerrno.c ${CMAKE_CURRENT_SOURCE_DIR}/../micropython/py/modthread.c ${CMAKE_CURRENT_SOURCE_DIR}/../micropython/py/vm.c ${CMAKE_CURRENT_SOURCE_DIR}/../micropython/py/bc.c ${CMAKE_CURRENT_SOURCE_DIR}/../micropython/py/showbc.c ${CMAKE_CURRENT_SOURCE_DIR}/../micropython/py/repl.c ${CMAKE_CURRENT_SOURCE_DIR}/../micropython/py/smallint.c ${CMAKE_CURRENT_SOURCE_DIR}/../micropython/py/frozenmod.c ${CMAKE_CURRENT_SOURCE_DIR}/../micropython/extmod/moductypes.c ${CMAKE_CURRENT_SOURCE_DIR}/../micropython/extmod/modujson.c ${CMAKE_CURRENT_SOURCE_DIR}/../micropython/extmod/modure.c ${CMAKE_CURRENT_SOURCE_DIR}/../micropython/extmod/moduzlib.c ${CMAKE_CURRENT_SOURCE_DIR}/../micropython/extmod/moduheapq.c ${CMAKE_CURRENT_SOURCE_DIR}/../micropython/extmod/modutimeq.c ${CMAKE_CURRENT_SOURCE_DIR}/../micropython/extmod/moduhashlib.c ${CMAKE_CURRENT_SOURCE_DIR}/../micropython/extmod/moducryptolib.c ${CMAKE_CURRENT_SOURCE_DIR}/../micropython/extmod/modubinascii.c ${CMAKE_CURRENT_SOURCE_DIR}/../micropython/extmod/virtpin.c ${CMAKE_CURRENT_SOURCE_DIR}/../micropython/extmod/machine_mem.c ${CMAKE_CURRENT_SOURCE_DIR}/../micropython/extmod/machine_pinbase.c ${CMAKE_CURRENT_SOURCE_DIR}/../micropython/extmod/machine_signal.c ${CMAKE_CURRENT_SOURCE_DIR}/../micropython/extmod/machine_pulse.c ${CMAKE_CURRENT_SOURCE_DIR}/../micropython/extmod/machine_i2c.c ${CMAKE_CURRENT_SOURCE_DIR}/../micropython/extmod/machine_spi.c ${CMAKE_CURRENT_SOURCE_DIR}/../micropython/extmod/modbluetooth.c ${CMAKE_CURRENT_SOURCE_DIR}/../micropython/extmod/modussl_axtls.c ${CMAKE_CURRENT_SOURCE_DIR}/../micropython/extmod/modussl_mbedtls.c ${CMAKE_CURRENT_SOURCE_DIR}/../micropython/extmod/modurandom.c ${CMAKE_CURRENT_SOURCE_DIR}/../micropython/extmod/moduselect.c ${CMAKE_CURRENT_SOURCE_DIR}/../micropython/extmod/moduwebsocket.c ${CMAKE_CURRENT_SOURCE_DIR}/../micropython/extmod/modwebrepl.c ${CMAKE_CURRENT_SOURCE_DIR}/../micropython/extmod/modframebuf.c ${CMAKE_CURRENT_SOURCE_DIR}/../micropython/extmod/vfs.c ${CMAKE_CURRENT_SOURCE_DIR}/../micropython/extmod/vfs_blockdev.c ${CMAKE_CURRENT_SOURCE_DIR}/../micropython/extmod/vfs_reader.c ${CMAKE_CURRENT_SOURCE_DIR}/../micropython/extmod/vfs_posix.c ${CMAKE_CURRENT_SOURCE_DIR}/../micropython/extmod/vfs_posix_file.c ${CMAKE_CURRENT_SOURCE_DIR}/../micropython/extmod/vfs_fat.c ${CMAKE_CURRENT_SOURCE_DIR}/../micropython/extmod/vfs_fat_diskio.c ${CMAKE_CURRENT_SOURCE_DIR}/../micropython/extmod/vfs_fat_file.c ${CMAKE_CURRENT_SOURCE_DIR}/../micropython/extmod/vfs_lfs.c ${CMAKE_CURRENT_SOURCE_DIR}/../micropython/extmod/utime_mphal.c ${CMAKE_CURRENT_SOURCE_DIR}/../micropython/extmod/uos_dupterm.c ${CMAKE_CURRENT_SOURCE_DIR}/../micropython/lib/embed/abort_.c ${CMAKE_CURRENT_SOURCE_DIR}/../micropython/lib/utils/printf.c ${PROJECT_BINARY_DIR}/genhdr/moduledefs.h ${CMAKE_CURRENT_SOURCE_DIR}/../micropython/py/mpconfig.h ${CMAKE_CURRENT_SOURCE_DIR}/mpconfigport.h > ${PROJECT_BINARY_DIR}/genhdr/qstr.i.last
	DEPENDS ${PROJECT_BINARY_DIR}/genhdr/moduledefs.h
	)
add_custom_target(
 	gen_qstr_i_last ALL
 	DEPENDS ${PROJECT_BINARY_DIR}/genhdr/qstr.i.last
)

#Split Qstrings
add_custom_command(
	OUTPUT ${PROJECT_BINARY_DIR}/genhdr/qstr
	COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/../micropython/py/makeqstrdefs.py split ${PROJECT_BINARY_DIR}/genhdr/qstr.i.last ${PROJECT_BINARY_DIR}/genhdr/qstr ${PROJECT_BINARY_DIR}/genhdr/qstrdefs.collected.h
	DEPENDS ${PROJECT_BINARY_DIR}/genhdr/qstr.i.last
	)
add_custom_target(
 	gen_qstr_split ALL
 	DEPENDS ${PROJECT_BINARY_DIR}/genhdr/qstr
)

#Touch qstr.split
#TODO: can I use the file(TOUCH filename) for this somehow? 
add_custom_command(
	OUTPUT ${PROJECT_BINARY_DIR}/genhdr/qstr.split
	COMMAND "${CMAKE_COMMAND}" -E touch ${PROJECT_BINARY_DIR}/genhdr/qstr.split
	DEPENDS ${PROJECT_BINARY_DIR}/genhdr/qstr
	)
add_custom_target(
 	touch_qstr_split ALL
 	DEPENDS ${PROJECT_BINARY_DIR}/genhdr/qstr.split
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
	gen_qstr_i_last		#TODO: make this a dependency of later qstr steps
	gen_qstr_split
	touch_qstr_split
	)

target_link_libraries(MicroPython 
	RetroConsole
	mp_lib_utils
	mp_lib_readline
	mp_py
	)

