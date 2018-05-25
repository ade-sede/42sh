/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:40 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 23:15:19 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "str.h"

static	int		ft_char_is_space(char c)
{
	if (c == '\t' || c == '\n' || c == ' ')
		return (1);
	return (0);
}

char			*ft_strtrim(char const *s)
{
	char	*new_str;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (s == NULL || (new_str = ft_strnew(ft_strlen(s))) == NULL)
		return (NULL);
	while (i != ft_strlen(s))
	{
		if (ft_char_is_space(s[i]) && !j)
			i++;
		else
			new_str[j++] = s[i++];
	}
	while (ft_char_is_space(new_str[--j]))
		new_str[j] = '\0';
	return (new_str);
}

/*
** Returns a duped copy of string s where all occurence of the string sequence
** has been removed from s.
*/

static size_t	get_trimed_size(const char *s, const char *sequence, \
		size_t seq_len)
{
	size_t	trimed_len;
	size_t	i;

	i = 0;
	trimed_len = 0;
	while (s[i])
	{
		if (!ft_strnequ(s + i, sequence, seq_len))
		{
			++trimed_len;
			++i;
		}
		else
			i += seq_len;
	}
	return (trimed_len);
}

char			*ft_strtrim_sequence(const char *s, const char *sequence)
{
	size_t	trimed_len;
	char	*ret;
	size_t	i;
	size_t	j;
	size_t	seq_len;

	i = 0;
	j = 0;
	seq_len = ft_strlen(sequence);
	if (!seq_len || !s || !*s)
		return (NULL);
	trimed_len = get_trimed_size(s, sequence, seq_len);
	ret = ft_strnew(trimed_len);
	while (s[i])
	{
		if (!ft_strnequ(s + i, sequence, seq_len))
		{
			ret[j] = s[i];
			++j;
			++i;
		}
		else
			i += seq_len;
	}
	return (ret);
}
