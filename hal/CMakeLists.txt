
if(FUNOS_SIMULATOR)
	add_executable(${ENTRY_POINT}
		udp/main.c
		udp/udp_handler.c
	)

	target_include_directories(${ENTRY_POINT}
		PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/udp
		PRIVATE ${PROJECT_SOURCE_DIR}/iso7816
	)

	target_link_libraries(${ENTRY_POINT}
		${ISO7816}
	)
endif()