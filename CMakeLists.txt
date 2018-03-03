cmake_minimum_required(VERSION 2.8.9)
project (des)

set (DES_ROOT_DIR "${CMAKE_CURRENT_LIST_DIR}")

set(SOURCE_FILES
    des.c
)

add_executable(des ${SOURCE_FILES})