add_library(${GLOBAL_PLATFORM}
	isd.c
)

target_include_directories(${GLOBAL_PLATFORM}
	PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
)