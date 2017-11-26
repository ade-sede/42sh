/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match_open_dir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:36 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 23:14:14 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/dir.h>
#include <sys/types.h>
#include <dirent.h>
#include "libft.h"
#include "glob.h"

int				bad_dir(char *dir_name)
{
	free(dir_name);
	return (0);
}

int				end_match_open_dir(t_matches *m, char *cpy_to_match[2], \
		char *m_dir_cpy, int bool_match)
{
	free(m->dir);
	m->dir = m_dir_cpy;
	m->to_match = cpy_to_match[0];
	return (bool_match);
}

static void		cut(char *m_to_match, char **cpy_to_match, int *bool_match,
		int thin)
{
	cpy_to_match[1] = m_to_match;
	*bool_match |= thin;
}

static int		init(char **cpy_to_match, char **m_dir_cpy, char *dir_name,
		t_matches *m)
{
	cpy_to_match[0] = m->to_match;
	*m_dir_cpy = m->dir;
	m->dir = dir_name;
	return (0);
}

int				match_open_dir(t_matches *m, int m_i, int r_i, char *dir_name)
{
	int				bool_match;
	DIR				*dir;
	char			*m_dir_cpy;
	char			*cpy_to_match[2];
	struct dirent	*dirent;

	if ((dir = opendir(dir_name)) == NULL)
		return (bad_dir(dir_name));
	bool_match = init(cpy_to_match, &m_dir_cpy, dir_name, m);
	while ((dirent = readdir(dir)) != NULL)
	{
		if (ft_strequ(m->dir, "."))
			cut((m->to_match = ft_strdup(dirent->d_name)), cpy_to_match,
										&bool_match, (match(m, m_i, r_i)));
		else if (ft_strequ(m->dir, "/"))
			cut((m->to_match = (ft_strjoin(m->dir, dirent->d_name))),
					cpy_to_match, &bool_match, (match(m, m_i + 1, r_i)));
		else
			cut((m->to_match = (ft_strjoin3_free(m->dir, "/", dirent->d_name,
0))), cpy_to_match, &bool_match, (*dirent->d_name != '.' || (*dirent->d_name ==
		'.' && m->regex[r_i] == '.')) ? (match(m, m_i + 1, r_i)) : 0);
		free(cpy_to_match[1]);
	}
	closedir(dir);
	return (end_match_open_dir(m, cpy_to_match, m_dir_cpy, bool_match));
}
