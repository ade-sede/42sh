/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comple_file_matches.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:34 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 23:13:50 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_editing.h"
#include <string.h>

char	*get_file_color(char *dir, char *file, struct dirent *dirent)
{
	if (dirent->d_type == DT_DIR)
		return (ft_strjoin3_free("\e[1;31m", comple_escape(0, 0,
						dirent->d_name), "/", 0b10));
	else if (ft_is_executable(dir, file))
		return (ft_strjoin_free("\e[1;32m", comple_escape(0, 0,
						dirent->d_name), 0b1));
	else
		return (comple_escape(0, 0, dirent->d_name));
}

char	**array_matches(size_t i, size_t size, char *dir_match, char *to_match)
{
	struct dirent	*dirent;
	DIR				*dir;
	char			**matches;

	matches = NULL;
	dir = (dir_match) ? opendir(dir_match) : opendir(".");
	if (!dir)
		return (matches);
	while ((dirent = readdir(dir)) != NULL)
	{
		if ((!to_match[0] && dirent->d_name[0] != '.') || \
				(to_match[0] && ft_strstr(dirent->d_name, to_match)))
		{
			if (i >= size)
			{
				matches = ft_array_string_realloc(matches, size, size +
						MALLOC_UNIT);
				size += MALLOC_UNIT;
			}
			matches[i] = get_file_color(dir_match, dirent->d_name, dirent);
			i++;
		}
	}
	closedir(dir);
	return (matches);
}

void	split_word(char *str, char *separator, char **head, char **queu)
{
	char tmp;

	tmp = *separator;
	*separator = '\0';
	if (*str == '\0')
		*head = ft_strdup("/");
	else
		*head = ft_strdup(str);
	*queu = ft_strdup(separator + 1);
	*separator = tmp;
}

char	**comple_file_matches(t_line *line, t_comple *c)
{
	char	*to_match;
	char	*dir_match;
	char	**matches;

	to_match = NULL;
	dir_match = NULL;
	c->to_replace = get_start_word_cursor(line);
	if (c->current_word && ft_strichr(c->current_word, '/') != -1)
	{
		c->to_replace = get_word_slash(line) + 1;
		split_word(c->current_word, ft_strrchr(c->current_word, '/'), \
				&dir_match, &to_match);
		matches = array_matches(0, 0, dir_match, to_match);
		free(dir_match);
		free(to_match);
		return (matches);
	}
	matches = array_matches(0, 0, NULL, c->current_word);
	return (matches);
}
