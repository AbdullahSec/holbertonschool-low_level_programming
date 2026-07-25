# C - More malloc, free

## Description
This project covers advanced dynamic memory allocation in C programming, including custom implementations of memory allocation functions such as `malloc_checked`, `string_nconcat`, `_calloc`, and `array_range`.

## Requirements
* Allowed editors: `vi`, `vim`, `emacs`
* All files compiled on Ubuntu 20.04 LTS using `gcc` with options `-Wall -Werror -Wextra -pedantic -std=gnu89`
* Code must adhere to the **Betty** style guide
* No global variables allowed
* No more than 5 functions per file
* The standard library functions `malloc` and `free` are permitted; `exit` is allowed where specified.

## Function Prototypes

| File | Prototype | Description |
| --- | --- | --- |
| `0-malloc_checked.c` | `void *malloc_checked(unsigned int b);` | Allocates memory using `malloc`. Terminates process with status `98` on failure. |
| `1-string_nconcat.c` | `char *string_nconcat(char *s1, char *s2, unsigned int n);` | Concatenates `s1` with the first `n` bytes of `s2`. |
| `2-calloc.c` | `void *_calloc(unsigned int nmemb, unsigned int size);` | Allocates memory for an array of `nmemb` elements initialized to zero. |
| `3-array_range.c` | `int *array_range(int min, int max);` | Creates an array of integers containing values from `min` to `max`. |

