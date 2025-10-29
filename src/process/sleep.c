#include <unistd.h>
#include <internal/syscall.h>
#include <internal/types.h>

struct timespec{
    long tv_sec; //secunde
    long tv_nsec; //nanosecunde
};

unsigned int sleep (unsigned int seconds)
{
    struct timespec req;
    req.tv_sec = seconds;
    req.tv_nsec = 0;

    long result = syscall(__NR_nanosleep, &req, 0);

    if(result < 0) //syscall-ul esueaza si returneaza timpul ramas
        return seconds;

    return 0;
}