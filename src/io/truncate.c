// SPDX-License-Identifier: BSD-3-Clause

#include <unistd.h>
#include <internal/syscall.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>

int truncate(const char *path, off_t length)
{
	/* TODO: Implement truncate(). */

	//deschidem fisier cu permisiuni de scriere
	int fd = syscall(__NR_openat, AT_FDCWD, path, O_WRONLY, 0);

	if(fd < 0)
	{
		errno = -fd;
		return -1;
	}

	long result = syscall(__NR_ftruncate, fd, length); //apelam ftruncate pt a schimba dimensiunea
	syscall(__NR_close, fd); //inchidem fisierul

	if(result < 0)
	{
		errno = -result;
		return -1;
	}
	return 0;
}
