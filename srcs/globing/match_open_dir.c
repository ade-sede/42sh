#include "glob.h"
#include <sys/dir.h>
#include <sys/types.h>
#include <dirent.h>

/*
**	char *match_open_file(char *m_dir, char *file_name)
**	{
**		if (ft_strequ(m_dir, "."))
**			return (ft_strdup(file_name));
**		else if (ft_strequ(m_dir, "/"))
**			return (ft_strjoin(m_dir, file_name));
**		else
**			return (ft_strjoin3_free(m_dir, "/", file_name, 0));
**	}
*/

int	bad_dir(char *dir_name)
{
	free(dir_name);
	return (0);
}

int	end_match_open_dir(t_matches *m, char *cpy_to_match[2], char *m_dir_cpy, \
		int bool_match)
{
	free(m->dir);
	m->dir = m_dir_cpy;
	m->to_match = cpy_to_match[0];
	return (bool_match);
}

int	match_open_dir(t_matches *m, int m_i, int r_i, char *dir_name)
{
	int				bool_match;
	DIR				*dir;
	char			*m_dir_cpy;
	char			*cpy_to_match[2];
	struct dirent	*dirent;

	dirent = NULL;
	bool_match = 0;
	cpy_to_match[0] = m->to_match;
	if ((dir = opendir(dir_name)) == NULL)
		return (bad_dir(dir_name));
	m_dir_cpy = m->dir;
	m->dir = dir_name;
	while ((dirent = readdir(dir)) != NULL)
	{
		if (ft_strequ(m->dir, "."))
		{
			m->to_match = ft_strdup(dirent->d_name);
			cpy_to_match[1] = m->to_match;
			bool_match |= (match(m, m_i, r_i));
		}
		else if (ft_strequ(m->dir, "/"))
		{
			m->to_match = (ft_strjoin(m->dir, dirent->d_name));
			cpy_to_match[1] = m->to_match;
			bool_match |= (match(m, m_i + 1, r_i));
		}
		else
		{
			m->to_match = (ft_strjoin3_free(m->dir, "/", dirent->d_name, 0));
			cpy_to_match[1] = m->to_match;
			if (dirent->d_name[0] != '.' || (dirent->d_name[0] == '.' && m->regex[r_i] == '.'))
				bool_match |= (match(m, m_i + 1, r_i));
		}
		free(cpy_to_match[1]);
	}
	closedir(dir);
	return (end_match_open_dir(m, cpy_to_match, m_dir_cpy, bool_match));
}
