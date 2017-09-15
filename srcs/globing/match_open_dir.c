/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match_open_dir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/15 22:41:03 by vcombey           #+#    #+#             */
/*   Updated: 2017/09/15 22:41:13 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glob.h"
#include <sys/dir.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>

int	match_open_file(t_matches *m, int to_match_i, int regex_i, char *file_name)
{
	if (ft_strequ(m->dir, "."))
		m->to_match = ft_strdup(file_name);
	else if (ft_strequ(m->dir, "/"))
		m->to_match = ft_strjoin(m->dir, file_name);
	else
		m->to_match = ft_strjoin3_free(m->dir, "/", file_name, 0);
	(void)to_match_i;
	(void)regex_i;
	return (0);
}

int	bad_dir(char *dir_name)
{
	free(dir_name);
	return (0);
}

int	match_open_dir(t_matches *m, int to_match_i, int regex_i, char *dir_name)
{
	int				bool_match;
	DIR				*dir;
	char			*m_dir_cpy;
	char			*cpy_to_match;
	struct dirent	*dirent;

	dirent = NULL;
	bool_match = 0;
	if ((dir = opendir(dir_name)) == NULL)
		return (bad_dir(dir_name));
	m_dir_cpy = m->dir;
	m->dir = dir_name;
	while ((dirent = readdir(dir)) != NULL)
	{
		match_open_file(m, to_match_i, regex_i, dirent->d_name);
		cpy_to_match = m->to_match;
		if (dirent->d_name[0] != '.' || \
				(dirent->d_name[0] == '.' && m->regex[regex_i] == '.'))
			bool_match |= (match(m, to_match_i + 1, regex_i));
		free(cpy_to_match);
	}
	closedir(dir);
	free(m->dir);
	m->dir = m_dir_cpy;
	return (bool_match);
}
