# Algorithmic Efficiency Comparison

## Environment
- All runs performed on the same machine and environment
- Compilation flags: gcc -Wall -Werror -Wextra -pedantic -std=gnu89 -Wno-long-long
- Array size: 50000 elements

## Raw Measurements

### Run 1
Naive algorithm result: 625025000
Naive algorithm time: 0.576275 seconds
Single-pass algorithm result: 25000
Single-pass algorithm time: 0.000025 seconds

### Run 2
Naive algorithm result: 625025000
Naive algorithm time: 0.557592 seconds
Single-pass algorithm result: 25000
Single-pass algorithm time: 0.000021 seconds

### Run 3
Naive algorithm result: 625025000
Naive algorithm time: 0.564344 seconds
Single-pass algorithm result: 25000
Single-pass algorithm time: 0.000031 seconds

## Average Execution Time

Naive algorithm:
(0.576275 + 0.557592 + 0.564344) / 3 = 0.566070 seconds

Single-pass algorithm:
(0.000025 + 0.000021 + 0.000031) / 3 = 0.000026 seconds

## Relative Difference

0.566070 / 0.000026 = ~21,772

The naive implementation is approximately 22,000 times slower than
the single-pass implementation.

## Analysis

### Why the naive version is slower

The naive version uses two nested loops. For every element in the outer
loop, the inner loop restarts and walks through the array again from the
beginning. This means the work grows with the square of the array size.

With 50000 elements, the naive version performs roughly 1.25 billion
comparisons, while the single-pass version performs only 50000. Both
solve the same problem, but one repeats work that has already been done.

### Time complexity

- Naive version: O(n^2) — quadratic growth
- Single-pass version: O(n) — linear growth

The measured difference of ~22,000x is consistent with this theory.

### Scaling

If the array size grew from 50000 to 1000000 (20 times larger), the
single-pass version would take roughly 20 times longer, while the naive
version would take roughly 400 times longer, since its cost grows with
the square of the input.

### Energy and sustainability

Runtime is a proxy for CPU activity. A program that keeps the CPU busy
for 0.57 seconds instead of 0.000026 seconds consumes far more energy for
the same result. At scale — thousands of servers running the same code —
this difference becomes significant in real power consumption and cost.

Choosing an efficient algorithm is therefore not only a performance
decision, but also a sustainability decision.

### Measurement notes

The three runs produced similar but not identical times. This variability
is expected, since the CPU is shared with other system processes.
Averaging multiple runs reduces the impact of this noise.
