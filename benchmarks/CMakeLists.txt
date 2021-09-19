add_executable(huobi_benchmark
        src/benchmarks.cpp
        ../src/file_handler/file_handler.cpp
        ../src/file_handler/file_handler.h
        ../src/types.h
        ../src/calculator/calculator.cpp
        ../src/calculator/calculator.h)

include_directories(${PROJECT_SOURCE_DIR}/src ${PROJECT_BINARY_DIR}/src
        ${PROJECT_BINARY_DIR}/third_party/benchmark/include ${PROJECT_SOURCE_DIR}/third_party/benchmark/include
        ${PROJECT_BINARY_DIR}/third_party ${PROJECT_SOURCE_DIR}/third_party)

set (BENCHMARK_LIBRARY_DIR "${PROJECT_SOURCE_DIR}/third_party/benchmark/build/src")
target_link_libraries (huobi_benchmark ${BENCHMARK_LIBRARY_DIR}/libbenchmark.a
        ${BENCHMARK_LIBRARY_DIR}/libbenchmark_main.a
        -lpthread)
