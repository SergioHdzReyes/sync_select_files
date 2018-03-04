cmake_minimum_required(VERSION 3.9)
project(sync_select_files C)

set(CMAKE_C_STANDARD 99)

add_executable(sync_select_files main.c shr/window_utils.h shr/general_utils.h configure_sync_select.c configure/configure_host.h)