#include <benchmark/benchmark.h>
#include "quicksort.h"

// static void BM_quicksort_naive(benchmark::State &state) {

//   int a[] = {1,2,3,10, 3, 6, 5, 3, 1, 0, 9, 8, 7};
//   for (auto _ : state) {
//     quicksort_naive(a, 0, 12);
//   }
// }
// BENCHMARK(BM_quicksort_naive)->Unit(benchmark::kMillisecond);


// BENCHMARK_MAIN();



// template <class Q> void BM_Sequential(benchmark::State& state) {
//   Q q;
//   typename Q::value_type v;
//   for (auto _ : state) {
//     for (int i = state.range(0); i--; )
//       q.push(v);
//     for (int e = state.range(0); e--; )
//       q.Wait(&v);
//   }
//   // actually messages, not bytes:
//   state.SetBytesProcessed(
//       static_cast<int64_t>(state.iterations())*state.range(0));
// }

// template <class T, class function> void BM_sort(benchmark::State& state) {
//   Q q;
//   typename Q::value_type v;
//   for (auto _ : state) {
//     for (int i = state.range(0); i--; )
//       q.push(v);
//     for (int e = state.range(0); e--; )
//       q.Wait(&v);
//   }
//   // actually messages, not bytes:
//   state.SetBytesProcessed(
//       static_cast<int64_t>(state.iterations())*state.range(0));
// }

/*
Template:
- Dtype
- Array Size
- Uni | O | RO | LO | PU
- function
*/

auto BM_test = [](benchmark::State& st, auto Inputs) { /* ... */ };

int main(int argc, char** argv) {
  // for (auto& test_input : { /* ... */ })
  //     benchmark::RegisterBenchmark(test_input.name(), BM_test, test_input);
  // benchmark::Initialize(&argc, argv);
  // benchmark::RunSpecifiedBenchmarks();
}