#include "../src/list/list.h"
#include <benchmark/benchmark.h>

// Benchmark for adding elements to the end of the SinglyLinkedList
static void BM_AddElementsToEnd(benchmark::State& state) {
    for (auto _ : state) {
        Lists::SinglyLinkedList<int> list;
        for (int i = 0; i < state.range(0); ++i) {
            list.add(i);
        }
    }
}
BENCHMARK(BM_AddElementsToEnd)->Range(8, 8 << 10);
/*
// Benchmark for adding elements at a specific index in the SinglyLinkedList
static void BM_AddElementsAtIndex(benchmark::State& state) {
    for (auto _ : state) {
        Lists::SinglyLinkedList<int> list;
        for (int i = 0; i < state.range(0); ++i) {
            list.add(i / 2, i);  // Add in the middle of the list
        }
    }
}
BENCHMARK(BM_AddElementsAtIndex)->Range(8, 8 << 10);

// Benchmark for removing elements by index from the SinglyLinkedList
static void BM_RemoveElementsByIndex(benchmark::State& state) {
    for (auto _ : state) {
        Lists::SinglyLinkedList<int> list;
        for (int i = 0; i < state.range(0); ++i) {
            list.add(i);
        }
        for (int i = state.range(0) - 1; i >= 0; --i) {
            list.remove(i);  // Remove elements from the end
        }
    }
}
BENCHMARK(BM_RemoveElementsByIndex)->Range(8, 8 << 10);

// Benchmark for removing elements by value from the SinglyLinkedList
static void BM_RemoveElementsByValue(benchmark::State& state) {
    for (auto _ : state) {
        Lists::SinglyLinkedList<int> list;
        for (int i = 0; i < state.range(0); ++i) {
            list.add(i);
        }
        for (int i = 0; i < state.range(0); ++i) {
            list.remove(i);  // Remove by value
        }
    }
}
BENCHMARK(BM_RemoveElementsByValue)->Range(8, 8 << 10);

// Benchmark for accessing elements by index from the SinglyLinkedList
static void BM_GetElementsByIndex(benchmark::State& state) {
    Lists::SinglyLinkedList<int> list;
    for (int i = 0; i < state.range(0); ++i) {
        list.add(i);
    }
    for (auto _ : state) {
        list.get(state.range(0) / 2);  // Access the middle element
    }
}
BENCHMARK(BM_GetElementsByIndex)->Range(8, 8 << 10);

// Benchmark for setting elements by index in the SinglyLinkedList
static void BM_SetElementsByIndex(benchmark::State& state) {
    Lists::SinglyLinkedList<int> list;
    for (int i = 0; i < state.range(0); ++i) {
        list.add(i);
    }
    for (auto _ : state) {
        list.set(state.range(0) / 2, -1);  // Set the middle element to -1
    }
}
BENCHMARK(BM_SetElementsByIndex)->Range(8, 8 << 10);

// Benchmark for checking if a SinglyLinkedList contains an element
static void BM_ContainsElement(benchmark::State& state) {
    Lists::SinglyLinkedList<int> list;
    for (int i = 0; i < state.range(0); ++i) {
        list.add(i);
    }
    for (auto _ : state) {
        list.contains(state.range(0) / 2);  // Check for the middle element
    }
}
BENCHMARK(BM_ContainsElement)->Range(8, 8 << 10);

// Benchmark for finding the index of an element in the SinglyLinkedList
static void BM_IndexOfElement(benchmark::State& state) {
    Lists::SinglyLinkedList<int> list;
    for (int i = 0; i < state.range(0); ++i) {
        list.add(i);
    }
    for (auto _ : state) {
        list.indexOf(state.range(0) / 2);  // Find the index of the middle element
    }
}
BENCHMARK(BM_IndexOfElement)->Range(8, 8 << 10);

// Benchmark for clearing the SinglyLinkedList
static void BM_ClearList(benchmark::State& state) {
    for (auto _ : state) {
        Lists::SinglyLinkedList<int> list;
        for (int i = 0; i < state.range(0); ++i) {
            list.add(i);
        }
        list.clear();
    }
}
BENCHMARK(BM_ClearList)->Range(8, 8 << 10);
*/
// Main function to run the benchmarks
BENCHMARK_MAIN();

