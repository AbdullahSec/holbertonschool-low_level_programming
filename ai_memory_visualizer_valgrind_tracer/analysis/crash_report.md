# Crash Report — crash_example.c

Analysis of a deterministic segmentation fault. All figures are from an actual
run on Ubuntu (WSL2), Valgrind 3.26.0. The crash is fully explained without
re-running the program.

## Description of the crash

Running ./crash_example prints two lines and then terminates with a
segmentation fault (SIGSEGV, signal 11). Under Valgrind:

  Invalid write of size 4
    at main (crash_example.c:32)
  Address 0x0 is not stack'd, malloc'd or (recently) free'd
  Process terminating with default action of signal 11 (SIGSEGV)
  Access not within mapped region at address 0x0

The faulting line 32 is: nums[0] = 42;

## Root cause analysis

The crash is a NULL pointer dereference. The causal chain is:

1. main declares int n = 0 and calls nums = allocate_numbers(n).
2. allocate_numbers begins with:
     if (n <= 0)
         return NULL;
   Since n == 0, the guard is true and the function returns NULL immediately.
   malloc is never reached.
3. Back in main, nums now holds NULL (0x0).
4. Line 32, nums[0] = 42, is *(nums + 0) = 42, i.e. a 4-byte write to address
   0x0.
5. Address 0x0 is not mapped, so the CPU raises SIGSEGV.

The segmentation fault is the final observable effect, not the bug. The bug is
dereferencing a pointer that the code never checked for NULL after an early
return.

## Why the memory access is invalid

nums is a stack variable in main, but it holds the value NULL (0x0). The write
targets the address stored in nums, which is 0x0. Valgrind confirms this
address "is not stack'd, malloc'd or (recently) free'd" — it belongs to no
valid region. On Linux the first page (address 0) is deliberately left unmapped
so that NULL dereferences fault immediately and deterministically.

Stack, heap, or both? Neither valid region is touched:
- No heap is involved in the fault. malloc was never called on this path,
  because allocate_numbers returned before reaching it. The 1,024 bytes Valgrind
  lists as "still reachable" come from stdio buffering (printf), not from this
  program's logic, and are unrelated to the crash.
- The stack holds the pointer variable nums itself, but the invalid access is a
  write to address 0x0, which is neither the stack nor any allocated heap block.

## Category of undefined behavior

Null pointer dereference: writing through a null pointer. This is undefined
behavior in C. Here it is deterministic — n is hardcoded to 0, so the early
return and the resulting NULL write happen on every run, at the same line.

## Suggested fix (labeled as such)

This is a suggestion; the task does not require fixing the code. The robust fix
is to check the return value before using it:

  nums = allocate_numbers(n);
  if (nums == NULL)
      return 1;
  nums[0] = 42;

This handles the early-return case (and a real malloc failure) instead of
assuming allocate_numbers always returns a valid pointer.

## Documented AI Mistake and Correction

When asked for possible causes, an AI assistant claimed:

"The crash happens because malloc failed to allocate memory, so nums is NULL.
The system is out of memory."

Why this is incorrect: malloc never ran. allocate_numbers returns NULL from its
early guard (if (n <= 0) return NULL) because n is 0, so control never reaches
the malloc call. The Valgrind heap summary supports this: total heap usage is
"1 allocs" only (the stdio buffer), and there is no failed-allocation report.
NULL here comes from the function's own control flow, not from memory
exhaustion.

Correction: the NULL originates from the n <= 0 guard, not from a malloc
failure. The real defect is that main uses the returned pointer without
checking it. Blaming "out of memory" would send a developer to investigate
system resources instead of the missing NULL check, which is the actual cause.
