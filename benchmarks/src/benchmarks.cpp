//
// Бенчмарк на скорость обновления стакана
// и получения из него результирующих значений

#include <benchmark/benchmark.h>
#include "calculator/calculator.h"
#include "config.h"

int Count = 0;

// Создадим класс fixture в котором сразу
// проинициализируем вектор с апдейтами и класс calc
template <class Record>
class UpdateObjVectorFixture : public ::benchmark::Fixture {
public:
    void SetUp(const ::benchmark::State& st) {
        Calculator tmp({INPUT_FILE, OUTPUT_FILE});
        calc = std::move(tmp);
        calc.calcSnapshotBench(records);
    }

    void TearDown(const ::benchmark::State&) {
        records.clear();
    }

    std::vector<Record> records;
    Calculator calc;
};

using UpdateFix = UpdateObjVectorFixture<InputData>;
BENCHMARK_DEFINE_F(UpdateFix, Obj)(benchmark::State& state) {
    while (state.KeepRunning()) {
        calc._doUpdate(records[Count++ % records.size()]);
    }
}
BENCHMARK_REGISTER_F(UpdateFix, Obj);

BENCHMARK_MAIN();