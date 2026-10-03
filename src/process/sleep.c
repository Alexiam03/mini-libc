#include <time.h>
#include <unistd.h>
#include <internal/syscall.h>
#include <internal/types.h>
#include <errno.h>

unsigned int sleep(unsigned int seconds)
{
    struct timespec req;
    req.tv_sec = seconds;
    req.tv_nsec = 0;

    int result = nanosleep(&req, NULL); //null ptc daca timpul e intrerupt, timpul ramas nu e raportat inapoi

    if (result < 0) //syscall-ul esueaza si returneaza timpul ramas
        return seconds;

    return 0;
}





