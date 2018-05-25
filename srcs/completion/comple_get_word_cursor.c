/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comple_get_word_cursor.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:34 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 23:13:51 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_editing.h"
#include <string.h>

char	*get_word_slash(t_line *line)
{
	char	*word;

	word = line->buff + line->pos;
	if (word > line->buff && *word == ' ')
		word--;
	while (word > line->buff && (*word != ' ') && (*word != '/'))
		word--;
	return ((*word == '/') ? word : NULL);
}

char	*get_start_word_cursor(t_line *line)
{
	char	*word;

	word = line->buff + line->pos;
	if (word > line->buff && *word == ' ')
		word--;
	while (word > line->buff && (*word != ' '))
		word--;
	word = (*word == ' ') ? word + 1 : word;
	return (word);
}

void	delete_word(char *to_replace)
{
	char	*end;

	end = ft_strchr(to_replace, ' ');
	if (end)
	{
		ft_memmove(to_replace, end, ft_strlen(end));
		ft_strclr(to_replace + ft_strlen(end));
	}
	else
		ft_strclr(to_replace);
}

char	*get_current_word_cursor(t_line *line)
{
	char	*word;
	char	*end;
	char	tmp;

	end = NULL;
	word = get_start_word_cursor(line);
	end = ft_strchr(word, ' ');
	if (end)
	{
		tmp = *end;
		*end = '\0';
	}
	word = ft_strdup(word);
	if (end)
		*end = tmp;
	return (word);
}
