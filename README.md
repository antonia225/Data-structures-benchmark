# Data Structures Benchmark

Benchmarking treap, skip list, and red-black tree across multiple operations and input distributions in C++. Each operation is timed in nanoseconds and results are written to CSV files for analysis.

## Data Structures

- Treap (with `shared_ptr`)
- Skip List
- Red-Black Tree

## Operations Benchmarked

| Code | Operation |
|---|---|
| 1–4 | Insert |
| 5 | Delete |
| 6 | Search |
| 7 | Range query |
| 8 | Successor |
| 9 | Predecessor |
| 10 | Union |

## Input Distributions

Each test uses 40000 elements drawn from one of:

- Sorted ascending
- Sorted descending
- Uniform random
- Gaussian
- Inverted Gaussian

The distribution is assigned per test based on its index — the first fifth of tests use sorted ascending, the next fifth sorted descending, and so on.

## Project Structure

```
.
├── main.cpp              # Benchmark runner
├── generator.hpp         # Templated input generators
└── ds        
    ├── treaps.hpp        # Treap implementation
    ├── skip_lists.hpp    # Skip list implementation
    └── redblack.h        # Red-black tree implementation
```

## Output

One CSV file per data structure:

```
output_treap.csv
output_skiplist.csv
output_redblack.csv
```

Each row has the format:

```
Test, Nr_numere, Operatie, Timp, Rezultat
```

`Timp` is in nanoseconds. `Rezultat` is only present for search (found/not found), successor, predecessor, and range query operations.

## Build & Run

**Requirements:** C++17 or later.

```bash
g++ -std=c++17 -O2 -o benchmark main.cpp
./benchmark
```

Enter the number of tests when prompted.
