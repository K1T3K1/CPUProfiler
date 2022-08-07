cmake_minimum_required(VERSION 3.22)
project(CPUProfiler C)
add_executable(cpuprofiler main.c)
set_property(TARGET cpuprofiler PROPERTY C_STANDARD 11)

add_library(default-lib
            SHARED
            ${CMAKE_SOURCE_DIR}/CPUProfiler/Reader/reader.c
            ${CMAKE_SOURCE_DIR}/CPUProfiler/Analyzer/analyzer.c
            ${CMAKE_SOURCE_DIR}/CPUProfiler/Printer/printer.c
            ${CMAKE_SOURCE_DIR}/CPUProfiler/Watchdog/watchdog.c
            ${CMAKE_SOURCE_DIR}/CPUProfiler/Logger/logger.c)

target_include_directories(cpuprofiler
                           PUBLIC
                           ${CMAKE_SOURCE_DIR}/CPUProfiler/Reader
                           ${CMAKE_SOURCE_DIR}/CPUProfiler/Analyzer
                           ${CMAKE_SOURCE_DIR}/CPUProfiler/Printer
                           ${CMAKE_SOURCE_DIR}/CPUProfiler/Watchdog
                           ${CMAKE_SOURCE_DIR}/CPUProfiler/Logger)

include_directories( ${CMAKE_SOURCE_DIR}/CPUProfiler/Reader
                     ${CMAKE_SOURCE_DIR}/CPUProfiler/Analyzer
                     ${CMAKE_SOURCE_DIR}/CPUProfiler/Printer
                     ${CMAKE_SOURCE_DIR}/CPUProfiler/Watchdog
                     ${CMAKE_SOURCE_DIR}/CPUProfiler/Logger)

        
target_link_libraries(cpuprofiler default-lib)