cmake_minimum_required(VERSION 3.25)
project(Xinu VERSION 0.1)

set(XINU_NAME XinuOS)

add_subdirectory(src/queue)

add_executable(${XINU_NAME} main.c)

target_link_libraries(${XINU_NAME} "${XINU_NAME}_QUEUE")