// SPDX-License-Identifier: BSD-3-Clause

#include "string.h"

char *strcpy(char *destination, const char *source)
{
	/* TODO: Implement strcpy(). */

	int i = 0;
	while((destination[i] = source[i]) != '\0')
		i++;

	return destination;
}

char *strncpy(char *destination, const char *source, size_t len)
{
	/* TODO: Implement strncpy(). */
	int i = 0; // cu i mergem pe lungimea sirurilor
	size_t l = 0; // cu l mergem pe lungimea dorita
	while((destination[i] = source[i] ) && ++l < len)
		i++;

	return destination;
}

char *strcat(char *destination, const char *source)
{
	/* TODO: Implement strcat(). */
	int ld = 0;					//pt lungimea lui destination
	while(destination[ld])
		ld++;
	int ls = 0;					//pt lungimea lui source
	while(source[ls])
		destination[ld++] = source[ls++];

	destination[ld] = '\0';

	return destination;
}

char *strncat(char *destination, const char *source, size_t len)
{
	/* TODO: Implement strncat(). */
	int ld = 0; //pt lungimea lui destination
	while(destination[ld])
		ld++;

	int ls = 0;	//pt lungimea lui source
	size_t l = 0; //pt a merge pana la len = lungimea dorita

	while(source[ls] && (l++ < len))
		destination[ld++] = source[ls++];

	destination[ld] = '\0';
	return destination;
}

int strcmp(const char *str1, const char *str2)
{
	/* TODO: Implement strcmp(). */
	int i = 0;
	while(str1[i] && str2[i])
	{
		if (str1[i] > str2[i])
			return 1;
		else if (str1[i] < str2[i])
				return -1;
		i++;
	}
	if (str1[i] == '\0' && str2[i] == '\0')
		return 0;
	else if (str1[i] == '\0')
			return -1;
		else
			return 1;
}

int strncmp(const char *str1, const char *str2, size_t len)
{
	/* TODO: Implement strncmp(). */
	size_t l = 0;
	while(str1[l] && str2[l] && (l < len))
	{
		if (str1[l] > str2[l])
			return 1;
		else if (str1[l] < str2[l])
				return -1;
		l++;
	}

	if (l == len) // s au comparat toate caracterele
		return 0;

	if (str1[l] == str2[l]) //ambele s-au terminat in acelasi timp
		return 0;
	else if (str1[l] == '\0') //primul s a terminat mai repede
			return -1;
		else
			return 1;
}

size_t strlen(const char *str)
{
	size_t i = 0;

	for (; *str != '\0'; str++, i++)
		;

	return i;
}

char *strchr(const char *str, int c)
{
	/* TODO: Implement strchr(). */
	int i = 0;
	while(str[i] != '\0')
	{
		if (str[i] == (char)c )
			return (char *)&str[i];
		i++;
	}

	if ((char )c == '\0') //caracterul cautat c este nul
		return (char *) &str[i];
	return NULL;
}

char *strrchr(const char *str, int c)
{
	/* TODO: Implement strrchr(). */
	size_t i = 0;
	char *last = NULL;

	while(str[i])
	{
		if (str[i] == (char )c )
			last = (char *) &str[i];
		i++;
	}

	if ((char )c == '\0')
		return (char* ) &str[i];

	return last;
}

char *strstr(const char *haystack, const char *needle)
{
	/* TODO: Implement strstr(). */
	size_t i, j;

	if (*needle == '\0'){
		return (char* )haystack;
	}

	for(i = 0; haystack[i] != 0; i++){
		if (haystack[i] == needle[0])
			{
				for(j = 0; needle[j] != '\0'; j++)
				{
					if (haystack[i+j] != needle[j]){
							break;
						}
				}

				if (needle[j] == '\0'){
					return (char *) &haystack[i];
				}
			}
	}
	return NULL;
}

char *strrstr(const char *haystack, const char *needle)
{
	/* TODO: Implement strrstr(). */
	size_t i, j;
	char * last = NULL;

	if (*needle == '\0'){
		return (char* )haystack;
	}

		for(i = 0; haystack[i] != 0; i++)
				if (haystack[i] == needle[0])
				{
					for(j = 0; needle[j] != '\0'; j++)
						if (haystack[i+j] != needle[j]){
							break;
						}

					if (needle[j] == '\0'){
						last =  (char *) &haystack[i];
					}
				}
	return last;
}

void *memcpy(void *destination, const void *source, size_t num)
{
	/* TODO: Implement memcpy(). */
	unsigned char *dest = destination;
	const unsigned char *src = source;

	for(size_t i = 0; i < num; i++)
		dest[i] = src[i];

	return destination;
}

void *memmove(void *destination, const void *source, size_t num)
{
	/* TODO: Implement memmove(). */
	unsigned char *dest = destination;
	const unsigned char *src = source;

	if (dest == src || num == 0)
		return destination;
	if (dest < src)
	{//sirurile nu se suprapun deci se copiaza normal
		for(size_t i = 0; i < num; i++)
			dest[i] = src[i];
	} else {//copiere inversa pentru sirurile care se suprapun
		for(size_t i = num; i > 0; i--)
			dest[i-1] = src[i-1];
	}
	return destination;
}

int memcmp(const void *ptr1, const void *ptr2, size_t num)
{
	/* TODO: Implement memcmp(). */

	const unsigned char *p1 = ptr1;
	const unsigned char *p2 = ptr2;

	for(size_t i = 0; i < num; i++)
		if (p1[i] != p2[i])
			return (int)p1[i] - (int)p2[i];

	return 0;
}

void *memset(void *source, int value, size_t num)
{
	/* TODO: Implement memset(). */

	unsigned char *src = source;
	unsigned char val = (unsigned char)value; //transf value intr-un singur byte

	for(size_t i = 0; i < num; i++) //scriem byte cu byte valoarea val in toata zona source de memorie
		src[i] = val;

	return source;
}




