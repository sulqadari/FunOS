cmake_minimum_required(VERSION 3.25)
project(FunOS)

set(ENTRY_POINT "FunOSemu")
set(UDP_CONNECTION	"WebSocket")
set(ISO7816		"iso7816")
set(GLOBAL_PLATFORM "GlobalPlatform")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -O0 -g3")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=address -static-libasan -fno-omit-frame-pointer")
# set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-unused-variable")

add_compile_definitions(
	FUNOS_SIMULATOR
)

add_subdirectory(hal/udp)
add_subdirectory(iso7816)
add_subdirectory(globalPlatform)

add_executable(${ENTRY_POINT}
	main.c
)

target_include_directories(${ENTRY_POINT}
	PRIVATE ${PROJECT_SOURCE_DIR}/globalPlatform
	PRIVATE ${PROJECT_SOURCE_DIR}/hal
	PRIVATE ${PROJECT_SOURCE_DIR}/iso7816
)

target_link_libraries(${ENTRY_POINT}
	PRIVATE ${UDP_CONNECTION}
	PRIVATE ${ISO7816}
	PRIVATE ${GLOBAL_PLATFORM}
)