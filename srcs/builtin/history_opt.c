/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_opt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:34 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 23:13:46 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "history.h"
#include "bang.h"
#include "printf.h"
#include "failure.h"

int	builtin_history_c(t_hist *hist)
{
	if (!hist->list || !hist->list->first)
		return (EXIT_FAILURE);
	ft_double_lst_remove(&hist->list, ft_free);
	return (EXIT_SUCCESS);
}

int	builtin_history_p(t_hist *hist, const char *argv)
{
	char	*tmp;

	if (!argv)
		return (EXIT_FAILURE);
	if ((tmp = bang_expand(argv, hist)))
	{
		ft_dprintf(2, "%s\n", tmp);
		free(tmp);
	}
	else
		ft_dprintf(2, "Expand would fail\n");
	return (EXIT_SUCCESS);
}

int	builtin_history_w(t_hist *hist, const char *argv)
{
	int			fd;
	const char	*path;

	path = argv;
	if (!argv)
		path = hist->file;
	if ((fd = open(path, O_RDWR | O_TRUNC | O_CREAT, 0644)) == -1)
		return (investigate_error(1, "open", NULL, EXIT_FAILURE));
	history_write_to_file(fd, hist);
	close(fd);
	return (EXIT_SUCCESS);
}

int	builtin_history_r(t_hist *hist, const char *argv)
{
	int			fd;
	const char	*path;

	path = argv;
	if (!argv)
		path = hist->file;
	if ((fd = open(path, O_RDONLY)) == -1)
		return (investigate_error(1, "open", NULL, EXIT_FAILURE));
	history_read_file(fd, hist);
	close(fd);
	return (EXIT_SUCCESS);
}
