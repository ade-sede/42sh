/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/25 19:39:56 by ade-sede          #+#    #+#             */
/*   Updated: 2017/05/29 16:48:31 by ade-sede         ###   ########.fr       */
/*                                                                            */ /* ************************************************************************** */ #include "str.h"
#include "mem.h"
#include "libft.h"
#include <stdio.h>

static void	align_memory(const char **s, char c)
{
	while (**s && **s != c && (((t_ulong)*s & (ULONG_SIZE - 1)) != 0))
		(*s)++;
}

static char *get_diff_end(const char *cp, char c)
{
	if (*++cp == c)
		return (char *) cp;
	else if (*cp == '\0')
		return NULL;
	if (*++cp == c)
		return (char *) cp;
	else if (*cp == '\0')
		return NULL;
	if (*++cp == c)
		return (char *) cp;
	else if (*cp == '\0')
		return NULL;
	if (*++cp == c)
		return (char *) cp;
	else if (*cp == '\0')
		return NULL;
	return (NULL);
}

static char *get_diff_start(const char *cp, char c)
{
	if (*cp == c)
		return (char *) cp;
	else if (*cp == '\0')
		return NULL;
	if (*++cp == c)
		return (char *) cp;
	else if (*cp == '\0')
		return NULL;
	if (*++cp == c)
		return (char *) cp;
	else if (*cp == '\0')
		return NULL;
	if (*++cp == c)
		return (char *) cp;
	else if (*cp == '\0')
		return NULL;
	return (get_diff_end(cp, c));
}

char * ft_strchr (const char *s, int c_in)
{
	const unsigned long int *longword_ptr;
	unsigned long int longword;

	align_memory(&s, (char)c_in);
	if (*s == (char)c_in)
		return (char*)s;
	else if (*s == '\0')
		return NULL;
	longword_ptr = (unsigned long int*) s;
	while (42)
	{
		longword = *longword_ptr++;
		if ((HAS_ZERO(longword)) || (HAS_VALUE(longword, CHAR_TO_LONG(c_in))))
			return (get_diff_start((const char*)(longword_ptr - 1), (char)c_in));
	}
	return NULL;
}
