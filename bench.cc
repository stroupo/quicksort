#include "quicksort.h"
#include <benchmark/benchmark.h>

static void BM_quicksort_naive(benchmark::State &state) {

  int a[] = {1,2,3,10, 3, 6, 5, 3, 1, 0, 9, 8, 7};
  for (auto _ : state) {
    quicksort_naive(a, 0, 12);
  }
}
BENCHMARK(BM_quicksort_naive)->Unit(benchmark::kMillisecond);


BENCHMARK_MAIN();

