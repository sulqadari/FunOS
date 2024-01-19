file(GLOB sources ${CMAKE_CURRENT_SOURCE_DIR}/*.c)

add_library(${XINU_NAME}_QUEUE STATIC ${sources})

target_include_directories(${XINU_NAME}_QUEUE PUBLIC
	${PROJECT_SOURCE_DIR}/src
	${PROJECT_SOURCE_DIR}/src/queue
	${PROJECT_SOURCE_DIR}/src/scheduler
)