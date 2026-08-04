# Valgrind Analysis

This document interprets Valgrind output as a direct consequence of concrete
memory behavior. Each reported issue is mapped to a specific memory object and
the lifetime violation that caused it. Figures are from actual runs on Ubuntu
(WSL2), Valgrind 3.26.0, using --leak-check=full.

## 1. aliasing_example — Use-After-Free (3 errors)

Command: valgrind --leak-check=full ./aliasing_example

Valgrind reported 3 errors from 3 contexts and, importantly, no leaks:
"All heap blocks were freed -- no leaks are possible".

| Line | Access      | Valgrind category       |
|------|-------------|-------------------------|
| 42   | b[2] read   | Invalid read of size 4  |
| 44   | b[3] = 1234 | Invalid write of size 4 |
| 45   | b[3] read   | Invalid read of size 4  |

Memory object involved: the 20-byte heap block (5 ints) allocated in
make_numbers at line 12 and returned to a.

Lifetime violation: b = a aliases that block (copies the address, not the
data). free(a) at line 38 ends the block's lifetime. Every later access through
b is a use-after-free, because b is now a dangling pointer to freed memory.

Valgrind's own words confirm this: "Address 0x4a9148c is 12 bytes inside a
block of size 20 free'd", with the free at line 38 and the allocation in
make_numbers line 12. The offset 12 equals b[3] (3 * 4 bytes), inside the
20-byte block. Read vs write matches the source: b[2] and the b[3] print are
reads, b[3] = 1234 is a write.

Classification: use-after-free, not a leak and not an overflow. The block was
freed exactly once; the defect is accessing it after its lifetime ended.

## 2. heap_example — Memory Leak Due to Lost Ownership

Command: valgrind --leak-check=full ./heap_example

Valgrind reported 1 error:
"6 bytes in 1 blocks are definitely lost in loss record 1 of 1"
  at malloc ... person_new (heap_example.c:21)
LEAK SUMMARY: definitely lost: 6 bytes in 1 blocks
total heap usage: 5 allocs, 4 frees, 1,066 bytes allocated

Memory object involved: alice->name, the heap block allocated at line 21
(p->name = malloc(len + 1)). The 6 bytes are "Alice" (5 chars) plus the null
terminator (1 byte).

Lifetime violation: this is a leak due to lost ownership. person_new makes two
allocations per Person (the struct and its name). person_free_partial frees
only the struct:

  free(p);   /* frees the Person, forgets p->name */

When alice is freed this way, the only pointer to alice->name (stored inside
the struct) is destroyed along with the struct. Ownership of the name block is
lost while the block is still allocated, so it can never be freed. bob avoids
this by freeing the inner block first (free(bob->name)) then the struct.

The counts confirm it: 5 allocs vs 4 frees means exactly one allocation is
never freed, which is alice->name.

Classification: definitely lost leak (lost ownership of a nested allocation).
Distinct from the aliasing case: here memory is never freed; there memory was
freed and then used.

## 3. Documented AI Mistake and Correction

When asked to interpret the heap_example Valgrind output, an AI assistant
claimed:

"The '6 bytes definitely lost' means the program forgot to call free at the end
of main, so adding one more free(alice) would fix the leak."

Why this is partially incorrect: alice IS already freed, through
person_free_partial(alice). The struct itself is not leaked. Adding another
free(alice) would not fix anything and would risk a double-free. The AI
misread which object leaked. Valgrind points to heap_example.c:21, which is the
allocation of p->name, not the struct. The leaked object is alice->name, not
alice.

Correction: the leak is the inner allocation (the name string), lost because
person_free_partial frees the struct without first freeing p->name. The correct
fix is to free the inner block before the outer one inside the cleanup
function (free(p->name); then free(p);), exactly as bob is handled. This is
verified against the source (line 21 is the name malloc) and against the Task 0
memory map, which shows each Person owns a separate name allocation on the heap.
