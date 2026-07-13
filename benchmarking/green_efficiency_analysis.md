# Green Efficiency Analysis

## Measurement Methodology

All programs were compiled with the same flags:
`gcc -Wall -Werror -Wextra -pedantic -std=gnu89 -Wno-long-long`

Timing used `clock()` from `<time.h>`. The clock value was read immediately
before and immediately after the region being measured, and the difference
divided by `CLOCKS_PER_SEC` to get seconds. `clock()` reports processor time
rather than wall-clock time, which is the right choice here because the question
is how long the CPU stays busy.

Every run was done on the same machine, in the same WSL environment, so hardware
is not a variable between measurements. Each program was run three times and the
results averaged, since a single run is affected by scheduling noise from other
processes.

In the instrumentation exercise, four timestamps were taken: one before the first
phase and one after each of the three phases. Each boundary sits directly around
its function call, so a phase interval contains only that phase's work. Total is
the difference between the last timestamp and the first, so it is always at least
as large as any individual phase.

## Observed Performance Differences

Naive implementation (nested loops), three runs:
0.576275, 0.557592, 0.564344 seconds. Average: 0.566070 s.

Single-pass implementation, three runs:
0.000025, 0.000021, 0.000031 seconds. Average: 0.000026 s.

Dividing the averages gives roughly 21,772. The naive version is about 22,000
times slower on the same 50,000-element array, on the same machine.

The reason is in the code. The naive version restarts an inner loop for every
element of the outer loop, so it re-scans data it has already scanned. Its cost
grows with the square of the input, O(n^2). The single-pass version reads each
element once, O(n). At 50,000 elements the naive version performs on the order of
1.25 billion comparisons against 50,000 for the single pass.

The three runs of each version were close but not identical. That variation is
why the average was used rather than one measurement.

## Relation Between Runtime and Energy Consumption

This project does not measure watts. Runtime is used as a stand-in: a process
that occupies the CPU for longer draws power for longer.

On that basis, the 22,000x gap is not only a speed result. The naive version
holds the processor for over half a second to produce a value the single-pass
version produces in 26 microseconds. Run once, the difference is invisible. Run
in a loop, or across a fleet of machines, the total CPU-seconds consumed scale
with the same ratio.

## Limitations of the Experiment

Runtime is a proxy, not a measurement of energy. The conclusion about power is an
inference. Real consumption also depends on CPU frequency scaling, cooling, and
background load, none of which were controlled or recorded.

Three runs are enough to show the difference is large and repeatable. They are
not enough to state the ratio precisely.

The measurements were taken inside WSL rather than on bare hardware, which adds a
layer between the program and the CPU that may affect timing.

## Practical Engineering Takeaway

Both implementations were written in the same language, compiled with the same
flags, and run on the same machine. The only difference between them was the
algorithm, and that difference alone accounted for four orders of magnitude in
runtime.

Efficiency work should therefore start at the level of complexity, before
micro-optimization. Removing one unnecessary nested loop produced a gain that no
amount of low-level tuning would match.
