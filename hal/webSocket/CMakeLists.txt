add_library(${WEBSOCKET}
	ws_wraper.c
	src/http_parser.c
	src/wic_server_hash.c
	src/wic_transport.c
	src/wic_utils.c
	src/wic.c
)

target_include_directories(${WEBSOCKET}
	PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
	PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include
	PRIVATE ${PROJECT_SOURCE_DIR}/iso7816
)