# mini-libc

A minimalistic, **freestanding** implementation of the C standard library for Linux on `x86_64`. It is built directly on top of the Linux system call interface and does not depend on glibc or any other external library.

The goal of the project is to understand how a libc works under the hood: string and memory primitives, POSIX file I/O, memory allocation, and the raw syscall layer.

## Features

| Area | Header(s) | Functions |
|------|-----------|-----------|
| Strings | `<string.h>` | `strlen`, `strcpy`, `strncpy`, `strcat`, `strncat`, `strcmp`, `strncmp`, `strchr`, `strrchr`, `strstr`, `strrstr` |
| Memory operations | `<string.h>` | `memcpy`, `memmove`, `memset`, `memcmp` |
| Output | `<stdio.h>` | `puts` |
| File I/O | `<unistd.h>`, `<fcntl.h>`, `<sys/stat.h>` | `open`, `close`, `lseek`, `stat`, `fstat`, `truncate`, `ftruncate` |
| Time | `<time.h>`, `<unistd.h>` | `nanosleep`, `sleep` |
| Memory management | `<stdlib.h>`, `<sys/mman.h>` | `malloc`, `free`, `calloc`, `realloc`, `reallocarray`, `mmap`, `mremap`, `munmap` |
| Error handling | `<errno.h>` | `errno`, set by the syscall wrappers and library functions on failure |

## How it works

- **Syscalls.** Every system call goes through a single `syscall()` function (`src/syscall.c`), which calls the architecture-specific code in `src/internal/arch/x86_64/syscall_arch.h`.
- **Error handling.** Wrappers convert negative kernel return values into `-1` (or `MAP_FAILED`) and store the error code in `errno`, following POSIX conventions.
- **Allocator.** `malloc` is built on `mmap`: each allocation gets its own anonymous private mapping, and its size is recorded in a list (`include/internal/mm/mem_list.h`, `src/mm/mem_list.c`). `free` looks the pointer up in that list and calls `munmap`. `calloc`, `realloc` and `reallocarray` are built on top of `malloc`, with overflow checks on the size multiplication.
- **Reuse.** Library functions build on each other; for example `sleep` calls `nanosleep`, and `puts` uses `strlen` and the `write` syscall.
- **Startup code.** `src/crt/` contains the program entry point (`start.asm`, `__libc_start_main.c`), so programs can be linked against mini-libc without glibc.

> **Note:** Because every `malloc` is a separate `mmap`, allocations are page-granular. This keeps the implementation simple but is not meant to be efficient.

## Project structure

```
.
├── src/            # mini-libc implementation (builds libc.a)
│   ├── crt/        # program startup code
│   ├── io/         # open, close, lseek, truncate, ftruncate, puts, ...
│   ├── mm/         # malloc family, mmap family, allocation list
│   ├── process/    # exit, sleep, nanosleep
│   ├── stat/       # stat, fstat
│   └── string/     # string and memory functions
├── include/        # public and internal headers
├── samples/        # small programs that use mini-libc
├── tests/          # automated tests
├── checker/        # test runner scripts
├── Dockerfile      # environment with the linters installed
└── README.checker.md
```

## Requirements

- Linux on `x86_64` (on ARM64 / Apple Silicon, use an `x86_64` virtual machine)
- `gcc`, `make`, `nasm` and `ar`

## Building

Build the library (produces `src/libc.a`):

```console
$ cd src/
$ make
```

Build the sample programs:

```console
$ cd samples/
$ make
```

## Testing

Run the whole test suite:

```console
$ cd tests/
$ make check
```

Or build everything and run tests individually:

```console
$ make -i
$ ./test_lseek.sh
$ ./test_memory
$ ./run_all_tests.sh
```

Each test prints its name and whether it passed:

```
test_strcpy                      ........................ passed ...   9
```

### Coding style

Style checks use `checkpatch.pl`, `cpplint` and `shellcheck`. The easiest way to run them is through the provided `Dockerfile`, which has everything installed:

```console
$ cd tests/
$ make lint
```

## Resources

- [GNU C Library manual](https://www.gnu.org/software/libc/manual/html_mono/libc.html)
- [musl libc source](https://elixir.bootlin.com/musl/latest/source)
- [glibc source](https://elixir.bootlin.com/glibc/latest/source)
- [Linux man pages](https://man7.org/linux/man-pages/index.html)

## Acknowledgements

The project skeleton and tests come from the *Mini-libc* assignment of the Operating Systems course at University POLITEHNICA of Bucharest. The functions listed above were implemented by me.
