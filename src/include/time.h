#ifndef __TIME_H__
#define __TIME_H__

#include <internal/types.h>
#include <errno.h>

struct timespec {
    long tv_sec;   // secunde
    long tv_nsec;  // nanosecunde
};
unsigned int sleep(unsigned int seconds);
int nanosleep(const struct timespec *req, struct timespec *rem);
#endif



