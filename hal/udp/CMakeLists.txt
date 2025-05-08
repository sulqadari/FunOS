add_library(${UDP_CONNECTION}
	cmdParser.c
	udp.c
)

target_include_directories(${UDP_CONNECTION}
	PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
	PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include
	PRIVATE ${PROJECT_SOURCE_DIR}/iso7816
)