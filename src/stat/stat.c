// SPDX-License-Identifier: BSD-3-Clause

#include <sys/stat.h>
#include <internal/syscall.h>
#include <fcntl.h>
#include <errno.h>

int stat(const char *restrict path, struct stat *restrict buf)
{//obtine informatii fisier specificat prin cale
	/* TODO: Implement stat(). */

	//apeleaza syscall-ul fstat pentru a obtine informatii despre fisier
	long result = syscall(__NR_newfstatat, AT_FDCWD, path, buf, 0);
	if (result < 0)
	{
		errno = -result; //syscall-ul a esuat
		return -1;
	}


	return 0;
}




