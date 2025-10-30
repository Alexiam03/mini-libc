// SPDX-License-Identifier: BSD-3-Clause

#include <internal/mm/mem_list.h>
#include <internal/types.h>
#include <internal/essentials.h>
#include <sys/mman.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#ifndef SIZE_MAX
#define SIZE_MAX ((size_t)-1)
#endif

static size_t get_alloc_size(void *ptr)
{
	struct mem_list *item = mem_list_find(ptr);
	if (item == NULL)
		return 0;
	return item->len;
}

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

	mem_list_add(result, size);

	return result;
}

void *calloc(size_t nmemb, size_t size)
{
	/* TODO: Implement calloc(). */

	if (size != 0 && nmemb > SIZE_MAX / size) {
		errno = ENOMEM;
		return NULL;
	}

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

	size_t size = get_alloc_size(ptr);

	if(size == 0)
	{
		errno = EINVAL;
		return;
	}

	mem_list_del(ptr);

	int res = munmap(ptr, size);
	if(res < 0)
		errno = EINVAL;
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

	size_t old_size = get_alloc_size(ptr);
	memcpy(result, ptr, (size < old_size) ? size : old_size);
	free(ptr);

	return result;
}

void *reallocarray(void *ptr, size_t nmemb, size_t size)
{
	/* TODO: Implement reallocarray(). */

	if( size != 0 && nmemb > SIZE_MAX / size)
	{
		errno = ENOMEM;
		return NULL;
	}

	size_t totalSize = nmemb * size;

	void *new = realloc(ptr, totalSize);

	if(new == NULL && totalSize != 0)
	{
		errno = ENOMEM;
		return NULL;
	}

	return new;
}
