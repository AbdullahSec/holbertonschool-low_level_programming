# Memory Maps Analysis

This document analyzes the runtime memory behavior of three programs from the
`programs/` directory: `stack_example.c`, `aliasing_example.c`, and
`heap_example.c`. All addresses and Valgrind figures below are from actual runs
on Ubuntu (WSL2), Valgrind 3.26.0.

## 1. stack_example.c — Stack Frames and Lifetimes

`main` calls `walk_stack(0, 3)`, which recurses
then unwinds. Each call creates its own stack frame with its own locals.
Everything lives on the stack; there is no heap use here.

Observed marker addresses during unwind:

| Frame     | address         | marker |
|-----------|-----------------|--------|
| depth = 0 | 0x7ffef1687a84  | 0      |
| depth = 1 | 0x7ffef1687a54  | 10     |
| depth = 2 | 0x7ffef1687a24  | 20     |

Conclusions:
- Each recursive call has its own independent frame: same name, different
  address, different value. No shared marker.
- Addresses decrease by 0x30 (48 bytes) per deeper call, confirming the stack
  grows toward lower addresses on x86-64.
- Lifetime: each local is valid only between function entry and exit. Returning
  the address of a local would produce a dangling pointer.

## 2. aliasing_example.c — Aliasing and Use-After-Free

make_numbers(5) allocates a heap array of 5 ints (20 bytes) and returns it to
a. Then b = a copies the pointer. After free(a), the program keeps reading and
writing through b. The array lives on the heap (allocated in make_numbers, line
12); a and b live on the stack in main.

Critical point: b = a does NOT copy the array. It copies only the address, so a
and b point to the same block. They are aliases. free(a) at line 38 releases
that block, leaving b dangling.

Valgrind reported 3 errors:

| Line | Access      | Category                |
|------|-------------|-------------------------|
| 42   | b[2] read   | Invalid read of size 4  |
| 44   | b[3] = 1234 | Invalid write of size 4 |
| 45   | b[3] read   | Invalid read of size 4  |

Each carried: "Address 0x4a9148c is 12 bytes inside a block of size 20 free'd",
freed via a at line 38, allocated in make_numbers line 12. This proves the
aliasing: b touches the same block freed through a. Offset 12 (3*4) inside a
20-byte block (5 ints) matches exactly.

Conclusions:
- Use-after-free is not a leak. Valgrind reports "All heap blocks were freed --
  no leaks are possible". The block was freed once; the bug is accessing it
  afterward.
- Ownership was ambiguous: both a and b acted as owners of one block. Setting
  b = NULL after the free, or a single clear owner, prevents this.

## 3. heap_example.c — Heap Ownership and a Deliberate Leak

person_new does two allocations per Person: the struct and p->name. bob is
freed correctly (free(bob->name) then free(bob)). alice is freed via
person_free_partial, which frees only the struct and forgets alice->name. Both
structs and names live on the heap.

Valgrind output:
- "6 bytes in 1 blocks are definitely lost ... person_new (heap_example.c:21)"
- "total heap usage: 5 allocs, 4 frees"

Conclusions:
- The leaked 6 bytes are "Alice" (5) plus the null terminator (1). Line 21 is
  p->name = malloc(len + 1), so the leaked block is alice's name.
- 5 allocs vs 4 frees: one allocation (alice->name) is never freed.
- For nested allocations, free the inner block before the outer. bob did;
  person_free_partial did not.

## 4. Documented AI Mistake and Correction

AI claim: "After b = a, b holds its own copy of the array, so even after
free(a), reading b[2] is safe because b is a separate variable."

Why it is wrong: this confuses the pointer variable with the memory it points
to. a and b are separate stack variables, but b = a copies only the address,
not the 20-byte heap block. Both point to the same block, so free(a) leaves b
dangling. Valgrind proves it: the access through b is "12 bytes inside a block
of size 20 free'd", freed via a at line 38.

Correction: b = a creates an alias, not a copy. There is one heap block and one
valid owner. After free(a), any access through b is use-after-free. A real copy
would need a second malloc plus an element-by-element copy, which this program
never does.
