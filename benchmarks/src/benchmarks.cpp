//
// Бенчмарк на скорость обновления стакана
// и получения из него результирующих значений

#include <benchmark/benchmark.h>
#include "calculator/calculator.h"
#include "config.h"

static void BM_Updating(benchmark::State& state) {
    Calculator calc({INPUT_FILE, OUTPUT_FILE});
    for (auto _ : state)
        calc.calculateForBenchmark();
}
BENCHMARK(BM_Updating);

BENCHMARK_MAIN();