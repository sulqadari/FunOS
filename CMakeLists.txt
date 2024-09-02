cmake_minimum_required(VERSION 3.25)
project(FunOS)

set(ENTRY_POINT "FunOSemu")
set(WEBSOCKET	"WebSocket")
set(ISO7816		"iso7816")
add_subdirectory(HAL/WS)
add_subdirectory(ISO7816)

add_executable(${ENTRY_POINT}
	main.c
)

target_include_directories(${ENTRY_POINT}
	PRIVATE ${PROJECT_SOURCE_DIR}/ISO7816
	PRIVATE ${PROJECT_SOURCE_DIR}/HAL/WS
)

target_link_libraries(${ENTRY_POINT}
	PRIVATE ${WEBSOCKET}
	PRIVATE ${ISO7816}
)