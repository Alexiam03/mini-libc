// SPDX-License-Identifier: BSD-3-Clause

#include <internal/mm/mem_list.h>
#include <internal/types.h>
#include <internal/essentials.h>
#include <sys/mman.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

void *malloc(size_t size)
{
	/* TODO: Implement malloc(). */

	if(size == 0)
		return NULL;

	//MAP_ANONYMOUS si MAP_PRIVATE => nu e legat la niciun fisier
	void *result = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

	if(result == MAP_FAILED) //daca esueaza
	{
		errno = ENOMEM;
		return NULL;
	}
	return result;
}

void *calloc(size_t nmemb, size_t size)
{
	/* TODO: Implement calloc(). */

	size_t total = nmemb * size;
	void *result = malloc(total);

	if(!result )
		return NULL;

	memset(result, 0, total); //umple memoria incepand de la adresa result
	return result;
}

void free(void *ptr)
{
	/* TODO: Implement free(). */

	if(ptr == NULL)
		return;

	munmap(ptr, 0);
}

void *realloc(void *ptr, size_t size)
{
	/* TODO: Implement realloc(). */

	if(ptr == NULL)
		return malloc(size);

	if(size == 0)
	{
		free(ptr);
		return NULL;
	}

	void *result = malloc(size);
	if( !result )
		return NULL;
	memcpy(result, ptr, size);
	free(ptr);

	return result;
}

void *reallocarray(void *ptr, size_t nmemb, size_t size)
{
	/* TODO: Implement reallocarray(). */
	return NULL;
}
