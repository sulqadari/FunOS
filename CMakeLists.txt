cmake_minimum_required(VERSION 3.25)
project(FunOS)


option(FUNOS_SIMULATOR "compile the simulator" YES)

set(ISO7816         "iso7816")
set(GLOBAL_PLATFORM "GlobalPlatform")
set(MEMNGER         "MemoryMngr")
set(ENTRY_POINT     "FunOSexe")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -m32 -Wall -O0 -g3")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=address -static-libasan -fno-omit-frame-pointer")

add_subdirectory(hal)
add_subdirectory(iso7816)
add_subdirectory(memngr)