/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/12 10:51:48 by ade-sede          #+#    #+#             */
/*   Updated: 2017/05/14 17:36:58 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int char_is_separator(char c, const char *split_base)
{
	if (ft_strichr((char*)split_base, c) != -1)
		return (1);
	return (0);
}

static char		*cpy_words(char *dst, char *src, int start, int lenght)
{
	int		i;
	int		j;

	if ((dst = (char*)malloc(sizeof(char) * (lenght + 1))) == NULL)
		return (NULL);
	i = 0;
	j = start;
	while (i != lenght)
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	dst[i] = '\0';
	return (dst);
}

static void		split_words(char **word_tab, char *s, char *split_base)
{
	int		word_size;
	int		i;

	word_size = 0;
	i = 0;
	while (s[i])
	{
		while (char_is_separator(s[i], split_base))
			i++;
		if (s[i] == '\0')
			break ;
		word_size = 0;
		while (!char_is_separator(s[i], split_base) && s[i])
		{
			i++;
			word_size++;
		}
		*word_tab = cpy_words(*word_tab, s, i - word_size, word_size);
		word_tab++;
	}
	*word_tab = NULL;
}

static int	get_nb_words(const char *str, const char *split_base)
{
	int	nb_words;
	int	i;

	nb_words = 0;
	i = 0;
	while(str[i])
	{
		while (char_is_separator(str[i], split_base))
			i++;
		if (str[i] == 0)
			return (nb_words);
		while (!char_is_separator(str[i], split_base))
			i++;
		nb_words++;
	}
	return (nb_words);
}

char	**ft_strsplit(const char *str, const char *split_base)
{
	char	**word_tab;
	int	nb_words;

	if (!str)
		return (NULL);
	nb_words = get_nb_words(str, split_base);
	word_tab = palloc(sizeof(char*) * (nb_words + 1), __func__);
	split_words(word_tab, (char*)str, (char*)split_base);
	return (word_tab);
}
