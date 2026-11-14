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
| `--medium` | Sliding-window chunk sort: push elements to b a window of ranks at a time (small ones sent to the bottom of b), then pull the maximum back each time | O(n√n) (nominal) |
| `--complex` | Radix sort (LSD, binary) on ranked values | O(n log n) |
| `--adaptive` (default) | Computes the input's disorder, then picks one of the three strategies above (inputs of 5 or fewer numbers use a dedicated small sort) | depends on input |

The complexity of `--medium` is the nominal class that `--bench` reports. The window size is a constant fraction of `n` that was tuned empirically (see [Medium sort](#medium-sort-sliding-window-chunks)).

## How the sorts work

### Common building blocks

**Stack representation.** Each stack is a plain `int` array whose top is index `0`, plus a size variable. Every operation function does three things: it updates the arrays, increments its counter in `ft_ops()` (used by `--bench`), and writes its name to stdout. The sorting algorithms never print anything themselves.

**Ranking.** `rank_values` replaces every value with its rank, i.e. the number of values smaller than it, so the input becomes a permutation of `0 .. n-1`. This removes the problem of negative numbers and keeps the values small enough for bitwise operations. The medium and complex strategies rank first. The simple strategy works directly on the values.

**Shortest rotation.** To bring the element at index `idx` of a stack of size `s` to the top, the code picks the cheaper direction:

```
idx <= s / 2   →  idx   rotations          (ra / rb)
idx >  s / 2   →  s-idx reverse rotations  (rra / rrb)
```

For example, index 4 in a stack of 5 costs a single `rra`. The simple sort, the small sort and the second phase of the medium sort all use this rule.

---

### Simple sort (selection sort)

**Idea.** Repeatedly take the smallest remaining number out of `a` and park it in `b`. Because the smallest number is pushed first, it ends up at the bottom of `b`, and the largest ends up on top. Pushing everything back with `pa` reverses that order, so `a` ends up ascending.

**Algorithm.**

1. If `a` is already sorted, stop.
2. While `a` is not empty:
   1. find the index of the smallest value in `a`;
   2. bring it to the top with the shortest rotation (`ra` or `rra`);
   3. `pb`.
3. While `b` is not empty: `pa`.

**Worked example: `./push_swap --simple 5 4 3 2 1`**

| Step | Minimum (index) | Rotation | `pb` | `a` after | `b` after |
|---|---|---|---|---|---|
| 1 | 1 (index 4 of 5) | `rra` | `pb` | `[5,4,3,2]` | `[1]` |
| 2 | 2 (index 3 of 4) | `rra` | `pb` | `[5,4,3]` | `[2,1]` |
| 3 | 3 (index 2 of 3) | `rra` | `pb` | `[5,4]` | `[3,2,1]` |
| 4 | 4 (index 1 of 2) | `ra` | `pb` | `[5]` | `[4,3,2,1]` |
| 5 | 5 (index 0 of 1) | none | `pb` | `[]` | `[5,4,3,2,1]` |
| 6 | | | `pa` ×5 | `[1,2,3,4,5]` | `[]` |

Output (14 operations): `rra pb rra pb rra pb ra pb pb pa pa pa pa pa`

**Cost.** Every element costs one `pb` and one `pa`, so `2n` push operations are always spent. On top of that come the rotations: finding the minimum is a scan of `a`, and bringing it to the top costs up to `size/2` rotations. On random input this adds up to roughly `n²/8` rotations, hence O(n²). When the input is already almost in order, the minimum is usually at or near the top, so the rotation part stays small. That is why the adaptive mode only uses this strategy when disorder is below 20 %.

---

### Medium sort (sliding-window chunks)

**Idea.** Instead of searching for each value, push the numbers from `a` to `b` in rough rank order using a window of ranks that slides upward. This leaves `b` roughly organised, so that pulling the numbers back in descending order is cheap. The rotations are where most of the work is, so the algorithm tries to merge them and to always choose the shorter direction.

**Setup.** `a` is ranked (`0 .. n-1`). The window width is:

```
chunk = n / 7 + 1     if n <= 100
chunk = n / 14 + 1    if n >  100        (n = 100 → 15, n = 500 → 36)
```

#### Phase 1: push `a` → `b` through the window

Let `pushed` be the number of elements already moved to `b`. The window contains the ranks `< pushed + chunk`:

```
ranks:  0 ........ pushed-1 | pushed ......... pushed+chunk-1 | ......... n-1
        [ already in b      ][ window: push these with pb      ][ not yet: rotate past ]
```

Every `pb` raises the upper bound by one, so the window slides up and the numbers enter `b` gradually, smallest ranks first.

**The rotate logic.** The goal is to send the lowest numbers of the window to the *bottom* of `b` while the higher ones stay on top, but without paying for every `rb` separately. The algorithm uses a flag, "pending `rb`":

```
while a is not empty:
    if a[0] < pushed + chunk:                  # a[0] is inside the window
        if rb_pending: rb                      # flush the previous pending rotation
        pb
        rb_pending = (rank just pushed < pushed_before + chunk/8) and b has >= 2 elements
        pushed++
    else if rb_pending and a has >= 2 elements:
        rr                                     # one operation instead of ra + rb
        rb_pending = false
    else:
        ra                                     # rotate a to reach the next candidate
if rb_pending: rb
```

In words:

- After a `pb`, if the pushed number is among the lowest `chunk/8` ranks of the window, it should sit at the bottom of `b`. The `rb` is **not** executed yet, it is only marked as pending.
- If the next number of `a` is outside the window, `a` needs an `ra` anyway. The pending `rb` is combined with it into a single `rr`, saving one operation.
- If the next number is inside the window, the pending `rb` is executed right before the next `pb`, so the small number really moves to the bottom first.
- A last pending `rb` is flushed after the loop.

#### Phase 2: pull `b` → `a` in descending order

At this point `b` holds every rank. Since the largest values must end up at the bottom of `a`, they are pulled first (each `pa` puts the number on top of `a`, so pulling in descending order builds `a` in ascending order).

```
while b is not empty:
    max    = rank (size_b - 1)
    second = rank (size_b - 2)
    if dist(second) + 1 < dist(max):
        bring second to the top (rb or rrb) ; pa
        bring max    to the top (rb or rrb) ; pa
        sa                                     # a = [second, max, ...] → back in order
    else:
        bring max to the top (rb or rrb) ; pa
```

`dist` is the shortest-rotation distance from the section above. The extra `+ 1` accounts for the `sa`: taking the second largest first is only worth it when it is at least two rotations closer than the largest.

**Example of what the operations look like.** One random run of 100 numbers with `--medium` produced `ra` 119, `rb` 101, `rr` 15, `rrb` 110, `pb` 100, `pa` 100, `sa` 28 (573 operations in total). The 15 `rr` operations are the merged `ra` + `rb` pairs, and the 28 `sa` operations come from the "second largest first" shortcut.

**Cost.** Phase 1 does `n` pushes plus the rotations of `a` needed to reach numbers inside the window, so a wider window means fewer rotations but a less ordered `b`. Phase 2 does `n` pushes plus the rotations of `b`, which are short because `b` is already roughly ordered. The window widths above (`n/7`, `n/14`) were tuned by testing 100 and 500 numbers.

---

### Complex sort (LSD binary radix sort)

**Idea.** Sort the ranked numbers one bit at a time, from the least significant bit to the most significant. After handling bit `k`, the numbers are ordered by their lowest `k + 1` bits. After the last bit they are fully sorted. Ranking guarantees the numbers are `0 .. n-1`, so only `ceil(log2 n)` bits are needed (n = 100 → 7 bits, n = 500 → 9 bits).

**One pass for a given `bit`.** Look at each of the `n` numbers of `a` exactly once, from the top:

- the bit is `1` → `ra` (the number stays in `a` and goes to the back);
- the bit is `0` → `pb` (the number moves to `b`).

Then push everything from `b` back with `pa`.

**Why it works (stability).** Radix sort needs each pass to keep the relative order of numbers that have the same bit value:

- the `1` numbers are only rotated, so their order does not change;
- the `0` numbers are pushed to `b` and pushed back, which reverses their order twice, so it is also preserved;
- the pushed-back `0` numbers land on top of the `1` numbers, so all the `0` numbers end up before all the `1` numbers.

**Worked example: `./push_swap --complex 3 0 2 1`** (2 bits, ranks are the values themselves)

| Pass | Operations | `a` after the pass |
|---|---|---|
| bit 0 | `ra` (3), `pb` (0), `pb` (2), `ra` (1), `pa`, `pa` | `[0,2,3,1]` (even numbers first, then odd numbers, each group in original order) |
| bit 1 | `pb` (0), `ra` (2), `ra` (3), `pb` (1), `pa`, `pa` | `[0,1,2,3]` |

Output (12 operations): `ra pb pb ra pa pa pb ra ra pb pa pa`

**Cost.** Each pass spends `n` operations (`ra` or `pb`) plus one `pa` for every number that went to `b`. The total is therefore about `n · log₂(n)` plus the number of zero bits. Because the ranks are always the same set `0 .. n-1`, the operation count depends **only on `n`, not on the order of the input**: it is always 1084 operations for 100 numbers and 6784 for 500 numbers (checked on random inputs). This makes the strategy very stable on highly disordered input, but wasteful on input that is already nearly sorted, which is why the adaptive mode avoids it for low disorder.

---

### Adaptive mode and disorder

**Disorder.** Disorder is the ratio of inversions (pairs `i < j` with `a[i] > a[j]`) to the total number of pairs `n(n-1)/2`. It ranges from `0.0` (sorted) to `1.0` (reversed). In adaptive mode:

| Disorder | Strategy selected |
|---|---|
| `0 %` | Nothing to do, nothing is printed |
| `< 20 %` | Simple |
| `20 % – 50 %` | Medium |
| `≥ 50 %` | Complex |

The strategy is chosen once, before sorting, rather than re-evaluated during the sort. Note that a uniformly random input has a disorder close to 50 % (typically within a few percent), which is exactly the boundary between medium and complex.

**Small inputs (adaptive only).** With `n ≤ 5` the adaptive mode skips the three strategies and uses a dedicated small sort: for 2 numbers it does `sa`; otherwise it pushes the minimum to `b` (shortest rotation) until 3 numbers remain, sorts those 3 with a hard-coded case analysis (`sa`, `ra`, `rra` combinations), and pushes everything back. Forcing a strategy with `--simple`, `--medium` or `--complex` bypasses this shortcut.

### Typical operation counts

Measured with this implementation on random sets of distinct integers (3 runs per size, strategy forced with its flag):

| Numbers | `--simple` | `--medium` | `--complex` |
|---|---|---|---|
| 100 | about 1350 – 1620 | about 500 – 550 | 1084 (always) |
| 500 | about 31600 – 31900 | about 4450 – 4600 | 6784 (always) |

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
