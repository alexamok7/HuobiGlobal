cmake_minimum_required(VERSION 3.14)
project(HuobiGlobal)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

set(INPUT_FILE "\"huobi_global_depth.log\"")
set(OUTPUT_FILE "\"12345.txt\"")

# sub-projects
add_subdirectory(src)
add_subdirectory(benchmarks)

configure_file (
        "${PROJECT_SOURCE_DIR}/config.h.in"
        "${PROJECT_BINARY_DIR}/src/config.h"
)
