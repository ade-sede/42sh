/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_history.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/27 05:07:29 by vcombey           #+#    #+#             */
/*   Updated: 2017/08/27 07:27:19 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history.h"
#include "get_next_line.h"
#include <sys/types.h>
#include <sys/stat.h>
#include "env.h"

static void	init_hist_struct(t_hist *h, t_env *env)
{
	char		*hist_file;

	ft_bzero(h, sizeof(t_hist));
	hist_file = env_getenv((const char **)env->environ, "HISTFILE", NULL);
	if (!hist_file)
		hist_file = ".minishell_history";
	h->file = hist_file;
	h->list = NULL;
	h->writen_buff = ft_strnew(4096);
	h->btsearch_buff = ft_strnew(4096);
}

int			history_load(t_hist *h, t_env *env)
{
	int			fd;
	char		*line;
	t_list_d	*list;

	init_hist_struct(h, env);
	if ((fd = open(h->file, O_RDWR | O_CREAT)) == -1)
		return (0);
	chmod(h->file, S_IRUSR | S_IWUSR | S_IRGRP);
	while (get_next_line(fd, &line))
	{
		list = ft_double_lst_create(line);
		if (h->list == NULL)
			h->list = ft_create_head(list);
		else
			ft_double_lst_add(&h->list, list);
	}
	close(fd);
	return (1);
}
