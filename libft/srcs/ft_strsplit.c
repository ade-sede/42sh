/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit_str.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/16 19:18:36 by vcombey           #+#    #+#             */
/*   Updated: 2017/05/19 19:33:30 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	ft_count_words(char const *s, const char *str)
{
	unsigned int	i;
	unsigned int	nb_words;

	i = 0;
	nb_words = 0;
	while (s[i])
	{
		while (s[i] && ft_is_one_of(s[i], str))
			i++;
		if (s[i] && !(ft_is_one_of(s[i], str)))
			nb_words++;
		while (s[i] && !(ft_is_one_of(s[i], str)))
			i++;
	}
	return (nb_words);
}

static char			**ft_malloc_t(char const *s, char **t, const  char *str)
{
	unsigned int	i;
	unsigned int	no_words;
	unsigned int	nb_letters;

	i = 0;
	no_words = -1;
	while (s[i])
	{
		while (s[i] && ft_is_one_of(s[i], str))
			i++;
		if (s[i] && !(ft_is_one_of(s[i], str)))
			no_words++;
		nb_letters = 0;
		while (s[i] && !(ft_is_one_of(s[i], str)))
		{
			i++;
			nb_letters++;
		}
		if (nb_letters != 0)
		{
			if (!(t[no_words] = ft_strnew(nb_letters)))
				return (NULL);
		}
	}
	return (t);
}

static void			ft_fill_t(char const *s, char **t, const char *str)
{
	unsigned int	i;
	unsigned int	no_words;
	unsigned int	no_letters;

	i = 0;
	no_words = -1;
	while (s[i])
	{
		while (s[i] && ft_is_one_of(s[i], str))
			i++;
		if (s[i] && !(ft_is_one_of(s[i], str)))
			no_words++;
		no_letters = 0;
		while (s[i] && !(ft_is_one_of(s[i], str)))
		{
			t[no_words][no_letters] = s[i];
			i++;
			no_letters++;
		}
	}
}

char				**ft_strsplit(char const *s, const char *str)
{
	unsigned int	nb_words;
	char			**word_tab;

	if (!s)
		return (NULL);
	nb_words = ft_count_words(s, str);
	word_tab = NULL;
	if (!(word_tab = (char **)malloc(sizeof(char *) * (nb_words + 1))))
		return (NULL);
	word_tab[nb_words] = NULL;
	if (ft_malloc_t(s, word_tab, str) == NULL)
		return (NULL);
	ft_fill_t(s, word_tab, str);
	return (word_tab);
}
