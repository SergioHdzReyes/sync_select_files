cmake_minimum_required(VERSION 3.20)
project(sync_select_files C)

set(CMAKE_C_STANDARD 11)

# Find dependencies
find_package(PkgConfig REQUIRED)
find_package(uriparser CONFIG REQUIRED)
find_package(libconfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
pkg_check_modules(GTK3 REQUIRED gtksourceview-4)
link_directories(${GTK3_LIBRARY_DIRS})
link_directories(${GTKSOURCEVIEW_LIBRARY_DIRS})
add_compile_options(${GTK3_CFLAGS_OTHER})
add_compile_options(${GTKSOURCEVIEW_FLAGS_OTHER})
set(LIBRARIES ${LIBRARIES} ${GTK3_LIBRARIES})

set(FLAGS "-I${GTK3_INCLUDE_DIRS} -lconfig")
message(STATUS "Flags: ${FLAGS}")
string(REPLACE ";" " -I" FLAGS "${FLAGS}")
set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} ${GTK3_FLAGS} ${FLAGS})

# Compile
add_executable(ssf src/ssf.c src/ssf_app.c src/ssf_window.c src/ssf_select_server_dialog.c src/ssf_invalid_project_dialog.c
        src/ssf_diff_core.c src/ssf.gresources.c src/libssfservers.c)
add_executable(ssf-server src/servers.c src/libssfservers.c src/general_utils.c)
add_executable(ssf-diff src/ssf_diff.c src/ssf_diff_core.c)

add_custom_command(TARGET ssf POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_CURRENT_SOURCE_DIR}/src/ssf.AppWindow.glade
        $<TARGET_FILE_DIR:ssf>
        )

target_link_libraries(ssf ${LIBRARIES})