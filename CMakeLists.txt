cmake_minimum_required(VERSION 3.11)
project(quicksort LANGUAGES CXX)


# add_executable(main main.cc quicksort.h)


# find_package(benchmark REQUIRED)
# find_package(Threads REQUIRED)

# add_executable(bench bench.cc quicksort.h)
# target_link_libraries(bench PRIVATE Threads::Threads benchmark)


add_library(ranarray ranarray.cc ranarray.h)
target_compile_features(ranarray PRIVATE cxx_std_17)

add_executable(main testranarray.cc)
target_link_libraries(main PRIVATE ranarray)