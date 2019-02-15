cmake_minimum_required(VERSION 3.11)
project(quicksort LANGUAGES CXX)


add_library(ranarray ranarray.cc ranarray.h)
target_compile_features(ranarray PRIVATE cxx_std_17)

add_executable(main testranarray.cc)
target_link_libraries(main PRIVATE ranarray)


find_package(benchmark)
find_package(Threads)

add_executable(bench bench.cc quicksort.h)
target_link_libraries(
	bench
	PRIVATE
	Threads::Threads
	benchmark)
target_compile_options(
	bench
	PRIVATE
	-O2)

add_executable(test test.cc quicksort.h)