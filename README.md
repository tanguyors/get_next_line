# get_next_line

```
 âââââââ ââââ   ââââââ
ââââââââ âââââ  ââââââ
âââ  ââââââââââ ââââââ
âââ   ââââââââââââââââ
ââââââââââââ ââââââââââââââ
 âââââââ âââ  âââââââââââââ
```

> *Reading a line from a fd is way too tedious. So I wrote my own.*

[![42 School](https://img.shields.io/badge/42-School-000000?style=flat-square&logo=42&logoColor=white)](https://42.fr)
![C](https://img.shields.io/badge/C-99-blue?style=flat-square&logo=c&logoColor=white)
![Stars](https://img.shields.io/github/stars/tanguyors/get_next_line?style=flat-square)

---

## About

**get_next_line** is a function that reads a file descriptor line by line. Each call returns the next line from the fd, including the trailing `\n` (except possibly the last line). It handles multiple file descriptors simultaneously and manages memory efficiently through static variables.

This project is a deep dive into **static variables**, **buffer management**, and **dynamic memory allocation** in C.

## How It Works

```
ââââââââââââââââââââââââââââââââââââââââââââââââ
â  BUFFER_SIZE = 42                            â
â                                              â
â  read(fd, buf, 42) âââº "Hello, World!\n"     â
â                         â²              â     â
â                         â     found \n â¼     â
â                    ââââââ´âââââ  ââââââââââââ â
â                    â return  â  â   save    â â
â                    â  line   â  â leftover  â â
â                    âââââââââââ  â (static)  â â
â                                 ââââââââââââ â
ââââââââââââââââââââââââââââââââââââââââââââââââ
```

## Key Concepts

- **Static variables** â Persist data between function calls to remember leftover buffer content
- **Dynamic buffer** â Handles any `BUFFER_SIZE` at compile time
- **Multi-fd support** â Can read from multiple file descriptors in parallel
- **Memory safety** â Proper allocation, reallocation, and freeing at every step

## Files

```
get_next_line/
âââ get_next_line.c          # Core logic
âââ get_next_line_utils.c    # Helper functions
âââ get_next_line.h          # Header
```

## Usage

```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int   fd = open("file.txt", O_RDONLY);
    char  *line;

    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return (0);
}
```

Compile with custom buffer size:
```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 main.c get_next_line.c get_next_line_utils.c -o reader
```

---

*One line at a time. â 42 School*
