# MicroPython System 7 Port
This is based, initially, on the minimal port of MircoPython. This can be found under ../micropython/ports/minimal/

Initially, only change is to strip out the STM32 related ifdef's.

After that, building a basic CMakeLists.txt file to import a bunch of code and tweak the files here until it successfully compiles.

Had to compile the minimal to get a few of the generated headers made for me until I can get around to bringing that into the CMake files.
