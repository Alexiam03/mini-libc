// SPDX-License-Identifier: BSD-3-Clause

#include <fcntl.h>
#include <internal/syscall.h>
#include <stdarg.h>
#include <errno.h>
#include <sys/stat.h>

int open(const char *filename, int flags, ...)
{
	/* TODO: Implement open system call. */
	mode_t mode = 0; //pentru a stoca permisiuni
	
	if(flags & O_CREAT) //verificam daca in flags apare optiunea O_CREAT
	{//cream fisierul atunci
	//citim argumentele optionale
	
		va_list args;
		va_start(args, flags);
		mode = va_arg(args, mode_t); //punem argumentul optional in mode
		va_end(args);
	}

	long result = syscall(__NR_openat, AT_FDCWD, filename, flags, mode);

	if( result < 0 )
	{
		errno = -result;
		return -1;
	}
	return (int)result;
}
