#include <stdio.h>
#include <unistd.h>
#include <internal/syscall.h>
#include <string.h>
#include <errno.h>

int puts(const char *s)
{
    if (s == NULL)
    {
        errno = EINVAL; //invalid argument
        return -1;
    }

    size_t len = strlen(s);
    //scriem sirul
    long result = syscall(__NR_write, 1, s, len);

    if (result < 0)
    {
        errno = -result;
        return -1;
    }

    char newline = '\n';
    result = syscall(__NR_write, 1, &newline, 1);
    if (result < 0) {
        errno = -result;
        return -1;
    }

    return 0;
}

