// SPDX-License-Identifier: BSD-3-Clause

#include <sys/stat.h>
#include <internal/syscall.h>
#include <errno.h>

int fstat(int fd, struct stat *st)
{//apel de sistem pentru informatii despre fisierul fd
	/* TODO: Implement fstat(). */

	long result = syscall(__NR_newfstatat, fd, "", st, AT_EMPTY_PATH); //apelez syscall-ul fstat
	if (result < 0)
	{
		errno = -result; //syscall-ul a esuat
		return -1;
	}


	return 0;
}




