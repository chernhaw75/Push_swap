*This project has been created as part of the 42 curriculum by tchern-h and jianlai.*

# push_swap

## Description

**push_swap** is a sorting project from the 42 curriculum. Given a stack `a` filled with distinct integers (positive and negative) and an empty stack `b`, the program must print, on standard output, the shortest possible list of operations that sorts `a` in ascending order, with the smallest number on top.

The goal is to learn how algorithm choice affects performance: the same input can be sorted with very different numbers of operations depending on the strategy used. This implementation provides four selectable strategies and a benchmark mode to compare them.

### Allowed operations

| Operation | Effect |
|---|---|
| `sa` / `sb` / `ss` | Swap the first two elements of a / b / both |
| `pa` / `pb` | Push the top element of b onto a / of a onto b |
| `ra` / `rb` / `rr` | Rotate a / b / both up (first element becomes last) |
| `rra` / `rrb` / `rrr` | Reverse rotate a / b / both (last element becomes first) |

### Strategies

| Flag | Strategy | Complexity |
|---|---|---|
| `--simple` | Selection sort: bring the minimum to the top by the shortest rotation, push it to b, then push everything back | O(n²) |
| `--medium` | Chunk sort: push elements to b in rank chunks of about √n, then pull the maximum back each time | O(n√n) |
| `--complex` | Radix sort (LSD, binary) on ranked values | O(n log n) |
| `--adaptive` (default) | Computes the input's disorder, then picks one of the three strategies above | depends on input |

**Ranking.** Medium and complex strategies first replace every value with its rank (0 = smallest). This removes the problem of negative numbers and keeps the values small enough for bitwise operations.

**Disorder.** Disorder is the ratio of inversions (pairs `i < j` with `a[i] > a[j]`) to the total number of pairs `n(n-1)/2`. It ranges from `0.0` (sorted) to `1.0` (reversed). In adaptive mode:

| Disorder | Strategy selected |
|---|---|
| `< 20 %` | Simple |
| `20 % – 50 %` | Medium |
| `≥ 50 %` | Complex |

### Benchmark mode

With `--bench`, metrics are printed to **stderr** (the operation list on stdout is unaffected):

```
[bench] disorder: 42.31%
[bench] strategy: Adaptive / O(n sqrt(n))
[bench] total_ops: 1234
[bench] sa: .. sb: .. ss: .. pa: .. pb: ..
[bench] ra: .. rb: .. rr: .. rra: .. rrb: .. rrr: ..
```

## Instructions

### Compilation

```bash
make        # builds ./push_swap
make clean  # removes object files
make fclean # removes object files and the binary
make re     # full rebuild
```

The project is compiled with `cc -Wall -Wextra -Werror`.

### Execution

```bash
./push_swap [strategy flag] [--bench] <integers...>
```

Flags must come before the numbers. Examples:

```bash
# Default (adaptive) strategy
./push_swap 2 1 3 6 5 8

# Count the operations
ARG="4 67 3 87 23"; ./push_swap --adaptive $ARG | wc -l

# Force a strategy
./push_swap --simple 5 4 3 2
./push_swap --medium $ARG
./push_swap --complex $ARG

# Benchmark only: hide the operations, keep the metrics
./push_swap --bench --simple $ARG > /dev/null

# Pipe operations to the checker and save the benchmark to a file
./push_swap --bench $ARG 2> bench.txt | ./checker $ARG
```

### Behavior and error handling

- No arguments, or an already sorted input: nothing is printed.
- Invalid input prints `Error` followed by a newline on **stderr** and exits with status 1. This covers non-numeric tokens, values outside the `int` range, and duplicates.

```bash
$ ./push_swap --adaptive 0 one 2 3
Error
$ ./push_swap --simple 3 2 3
Error
```

### Testing

Generate random inputs and verify the result with the provided checker:

```bash
ARG=$(shuf -i 0-1000 -n 100 | tr '\n' ' ')
./push_swap $ARG | ./checker $ARG
./push_swap $ARG | wc -l
```

## Resources

### References

- Cormen, Leiserson, Rivest, Stein: *Introduction to Algorithms* (CLRS), chapters on sorting and linear-time sorting (radix sort).
- Wikipedia: [Radix sort](https://en.wikipedia.org/wiki/Radix_sort), [Selection sort](https://en.wikipedia.org/wiki/Selection_sort), [Inversion (discrete mathematics)](https://en.wikipedia.org/wiki/Inversion_(discrete_mathematics)).
- The 42 push_swap subject (PDF) and the 42 Norm.
- GNU Make manual: <https://www.gnu.org/software/make/manual/>
- Linux manual pages for `write`, `malloc` and `free`.

### Use of AI

AI (Claude, by Anthropic) was used as a learning and pair-programming aid. It was used for:

- **Program structure:** drafting `main.c` (flag parsing, strict integer parsing and validation, duplicate check, strategy selection, benchmark output and stdout/stderr separation).
- **Algorithms:** explaining and drafting the radix sort with value ranking, the chunk-based medium sort, and a selection-sort variant for the simple strategy; reviewing the existing simple sort for correctness.
- **Concepts:** explaining the disorder metric and the reasoning behind choosing one strategy once rather than re-evaluating during the sort.
- **Documentation:** generating the first draft of this README.

All AI-generated code and explanations were read, tested and adapted by the authors to fit the project's own stack functions and the 42 Norm. The authors are responsible for the final code and understand how each part works.

## Authors

- tchern-h
- jianlai
