cmake_minimum_required(VERSION 3.20)

file(GLOB_RECURSE LIB_SOURCES "*.c" "*.S" "*.asm")

foreach(src ${LIB_SOURCES})
  if(src MATCHES "\\.[Ss]$")
    set_source_files_properties("${src}" PROPERTIES LANGUAGE ASM_NASM)
  endif()
endforeach()

set(CMAKE_ASM_NASM_FLAGS "-f win64")

add_library(ToolLib ${LIB_SOURCES})

target_include_directories(ToolLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
