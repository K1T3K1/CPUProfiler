cmake_minimum_required(VERSION 3.22)

add_compile_options(-Wall -Wextra)



project(CPUProfiler C)
add_executable(cpuprofiler main.c)
set_property(TARGET cpuprofiler PROPERTY C_STANDARD 11)

add_library(default-lib
            SHARED
            ${CMAKE_SOURCE_DIR}/CPUProfiler/Reader/reader.c
            ${CMAKE_SOURCE_DIR}/CPUProfiler/Analyzer/analyzer.c
            ${CMAKE_SOURCE_DIR}/CPUProfiler/Analyzer/analyzerTests.c
            ${CMAKE_SOURCE_DIR}/CPUProfiler/Printer/printer.c)

target_include_directories(cpuprofiler
                           PUBLIC
                           ${CMAKE_SOURCE_DIR}/CPUProfiler/Reader
                           ${CMAKE_SOURCE_DIR}/CPUProfiler/Analyzer
                           ${CMAKE_SOURCE_DIR}/CPUProfiler/Printer)

include_directories( ${CMAKE_SOURCE_DIR}/CPUProfiler/Reader
                     ${CMAKE_SOURCE_DIR}/CPUProfiler/Analyzer
                     ${CMAKE_SOURCE_DIR}/CPUProfiler/Printer)

target_link_libraries(cpuprofiler default-lib)


target_compile_options(cpuprofiler PRIVATE -Wall -Wextra)

