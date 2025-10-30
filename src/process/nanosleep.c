#include <time.h>
#include <internal/syscall.h>
#include <internal/types.h>
#include <errno.h>

int nanosleep(const struct timespec *req, struct timespec *rem)
{
    if (req == NULL)
    {
        errno = EINVAL;
        return -1;
    }

    long result = syscall(__NR_nanosleep, req, rem);

    if (result < 0)
    {
        errno = -result;
        return -1;
    }

    return 0;
}



