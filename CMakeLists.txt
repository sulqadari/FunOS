cmake_minimum_required(VERSION 3.25)
project(FunOS)

set(ENTRY_POINT "FunOSemu")
set(WEBSOCKET	"WebSocket")
set(ISO7816		"iso7816")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0 -g3 -fsanitize=address -static-libasan -fno-omit-frame-pointer")

add_compile_definitions(
	FUNOS_SIMULATOR
)

add_subdirectory(hal/webSocket)
add_subdirectory(iso7816)

add_executable(${ENTRY_POINT}
	main.c
)

target_include_directories(${ENTRY_POINT}
	PRIVATE ${PROJECT_SOURCE_DIR}/iso7816
	PRIVATE ${PROJECT_SOURCE_DIR}/hal/webSocket
)

target_link_libraries(${ENTRY_POINT}
	PRIVATE ${WEBSOCKET}
	PRIVATE ${ISO7816}
)