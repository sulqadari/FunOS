add_library(${ISO7816}
	apdu.c
)

target_include_directories(${ISO7816}
	PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
	PRIVATE ${PROJECT_SOURCE_DIR}/globalPlatform
	PRIVATE ${PROJECT_SOURCE_DIR}/hal/webSocket
	PRIVATE ${PROJECT_SOURCE_DIR}/hal/webSocket/include
)

target_link_libraries(${ISO7816}
	PRIVATE ${WEBSOCKET}
)