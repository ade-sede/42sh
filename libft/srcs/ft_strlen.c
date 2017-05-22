#include "libft.h"
#include <stdio.h>

/* static int	get_index(const char *cp) */
/* { */
/* 	if (cp[0] == 0) */
/* 		return (0); */
/* 	if (cp[1] == 0) */
/* 		return (1); */
/* 	if (cp[2] == 0) */
/* 		return (2); */
/* 	if (cp[3] == 0) */
/* 		return (3); */
/* 	/1* if (cp[4] == 0) *1/ */
/* 	/1* 	return (4); *1/ */
/* 	/1* if (cp[5] == 0) *1/ */
/* 	/1* 	return (5); *1/ */
/* 	/1* if (cp[6] == 0) *1/ */
/* 	/1* 	return (6); *1/ */
/* 	/1* if (cp[7] == 0) *1/ */
/* 	/1* 	return (7); *1/ */
/* 	return (-1); */
/* } */

/* static size_t	align_memory(const char **str) */
/* { */
/* 	const char	*origin; */

/* 	origin = *str; */
/* 	while ((unsigned long int)*str & (sizeof(unsigned long int) - 1)) */
/* 	{ */
/* 		if (**str == 0) */
/* 			return ((size_t)(*str - origin)); */
/* 		*str = *str + 1; */
/* 	} */
/* 	return (0); */
/* } */

/* size_t	ft_strlen(const char *str) */
/* { */
/* 	unsigned long int	longword; */
/* 	unsigned long int	himagic; */
/* 	unsigned long int	lomagic; */
/* 	unsigned long int	*longword_ptr; */
/* 	const char		*origin; */
/* 	int			ret; */

/* 	origin = str; */
/* 	if ((ret = (int)align_memory(&str)) != 0) */
/* 		return ((size_t)ret); */
/* 	longword_ptr = (unsigned long int *)str; */
/* 	himagic = 0x80808080UL; */
/* 	lomagic = 0x01010101UL; */
/* 	while (1) */
/* 	{ */
/* 		longword = *longword_ptr; */
/* 		longword_ptr++; */
/* 		if ((longword - lomagic) & ~(longword) & himagic) */
/* 		{ */
/* 			ret = get_index((const char *)longword_ptr - 1); */
/* 			if (ret != -1) */
/* 			{ */
/* 				return ((size_t)(((char *)longword_ptr + ret - origin))); */
/* 			} */
/* 		} */
/* 	} */
/* 	return (0); */
/* } */

size_t	ft_strlen(const char *s)
{
	int i;

	if (s == NULL)
		return (-1);
	i = 0;
	while (*s != '\0')
	{
		i++;
		s++;
	}
	return (i);
}

size_t	ft_arraylen(const char **s)
{
	int	i;

	if (s == NULL)
		return (-1);
	i = 0;
	while (*s != '\0')
	{
		i++;
		s++;
	}
	return (i);
}
