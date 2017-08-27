/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/27 12:13:14 by vcombey           #+#    #+#             */
/*   Updated: 2017/08/27 12:14:27 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "str.h"
#include "alloc.h"
#include "mem.h"

char	*ft_strdup(const char *s1)
{
	char	*new_str;
	size_t	len;

	len = ft_strlen(s1) + 1;
	new_str = palloc(sizeof(*new_str) * len);
	memcpy(new_str, s1, len);
	return (new_str);
}

char	*cl_strdup(const char *s1)
{
	char	*new_str;
	size_t	len;

	len = ft_strlen(s1) + 1;
	new_str = ft_memalloc(sizeof(*new_str) * len);
	memcpy(new_str, s1, len);
	return (new_str);
}

char	*ft_strndup(const char *s1, size_t n)
{
	char	*new_str;
	size_t	s1_len;

	s1_len = ft_strlen(s1);
	new_str = palloc(sizeof(*new_str) * n + 1);
	memcpy(new_str, s1, n);
	new_str[n] = 0;
	if (n > s1_len)
		ft_bzero(new_str + s1_len, n - s1_len);
	return (new_str);
}

char	*cl_strndup(const char *s1, size_t n)
{
	char	*new_str;
	size_t	s1_len;

	s1_len = ft_strlen(s1);
	new_str = ft_memalloc(sizeof(*new_str) * n + 1);
	memcpy(new_str, s1, n);
	new_str[n] = 0;
	if (n > s1_len)
		ft_bzero(new_str + s1_len, n - s1_len);
	return (new_str);
}
