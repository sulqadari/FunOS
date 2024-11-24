add_library(${MEMNGER}
	flash.c
)

target_include_directories(${MEMNGER}
	PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
)