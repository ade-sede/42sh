/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:40 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 23:15:21 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string.h"

void	w_newword(t_word *word)
{
	word->str = NULL;
	word->actlen = 0;
	word->maxlen = 0;
}

void	w_free(t_word *word)
{
	ft_strdel(&word->str);
	word->actlen = 0;
	word->maxlen = 0;
}

char	*w_addchar(t_word *word, char ch)
{
	if (word->actlen == word->maxlen)
	{
		word->maxlen += W_BUFF_SIZE;
		word->str = (char *)cl_realloc(word->actlen, word->str, \
				1 + word->maxlen);
	}
	word->str[word->actlen] = ch;
	word->actlen++;
	return (word->str);
}

char	*w_addmem(t_word *word, const char *str, size_t len)
{
	if (word->actlen + len > word->maxlen)
	{
		word->maxlen += 2 * len > W_BUFF_SIZE ? 2 * len : W_BUFF_SIZE;
		word->str = (char *)cl_realloc(word->actlen, word->str, \
				1 + word->maxlen);
	}
	ft_memcpy(&word->str[word->actlen], str, len);
	word->actlen += len;
	return (word->str);
}

char	*w_addstr(t_word *word, const char *str)
{
	size_t len;

	len = ft_strlen(str);
	return (w_addmem(word, str, len));
}
