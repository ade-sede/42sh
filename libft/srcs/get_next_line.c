/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/21 16:23:26 by ade-sede          #+#    #+#             */
/*   Updated: 2017/06/21 16:24:25 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"
#include <stdio.h>

static	t_l		*find_fd(t_l **list, int fd)
{
	t_l	*tmp;

	tmp = *list;
	while (tmp)
	{
		if (fd == tmp->fd)
			return (tmp);
		tmp = tmp->next;
	}
	return (tmp);
}

static	t_l		*new_elem(char *buff, size_t buff_size, int fd, t_l **list)
{
	t_l		*new_elem;
	char	*new_stock;

	if (buff == NULL)
	{
		new_stock = NULL;
		buff_size = 0;
	}
	new_stock = ft_strdup(buff);
	if ((new_elem = (t_l*)malloc(sizeof(t_l))) == NULL || !new_stock)
		return (NULL);
	new_elem->stock_size = buff_size;
	new_elem->fd = fd;
	new_elem->stock = new_stock;
	*list = new_elem;
	return (new_elem);
}

static	int		fill_line(t_l **list, int fd, char **ret)
{
	t_l		*new_elem;
	char	*tmp;
	int		eol_index;

	if (!(new_elem = find_fd(list, fd)))
		return (-1);
	if ((eol_index = ft_strichr(new_elem->stock, '\n')) != -1)
	{
		*ret = ft_strsub(new_elem->stock, 0, eol_index);
		if (!(tmp = ft_strdup(new_elem->stock + eol_index + 1)))
			return (-1);
		free(new_elem->stock);
		new_elem->stock = tmp;
	}
	else
	{
		if (!new_elem->stock || !(*ret = ft_strdup(new_elem->stock)))
		{
			*ret = NULL;
			return (-1);
		}
		free(new_elem->stock);
		new_elem->stock = NULL;
	}
	return ((ft_strlen(*ret) == 0 && eol_index != 0) ? 0 : 1);
}

static	int		check_list(t_l **list, int fd, char *buff)
{
	char	*new_stock;
	t_l		*tmp;
	t_l		*swap;

	swap = *list;
	tmp = find_fd(list, fd);
	if (!tmp)
	{
		tmp = new_elem(buff, ft_strlen(buff), fd, list);
		if (!tmp)
			return (-1);
		tmp->next = swap;
		*list = tmp;
	}
	else
	{
		if ((new_stock = ft_strjoin(tmp->stock, buff)) == NULL)
			return (-1);
		free(tmp->stock);
		tmp->stock = new_stock;
		tmp->stock_size = ft_strlen(new_stock);
	}
	return ((ft_strichr(tmp->stock, '\n') != -1) ? 0 : 1);
}

int				get_next_line(const int fd, char **line)
{
	static t_l		*elem;
	char			*buff;
	int				ret;

	if (!(buff = malloc(sizeof(char) * BUFF_SIZE + 1)))
		return (-1);
	if (fd < 0)
		return (-1);
	while ((ret = read(fd, buff, BUFF_SIZE)))
	{
		if (ret < 0)
			return (-1);
		buff[ret] = '\0';
		if ((check_list(&elem, fd, buff)) == 0)
		{
			if (fill_line(&elem, fd, &*line) == -1)
				return (-1);
			return (1);
		}
	}
	free(buff);
	if (fill_line(&elem, fd, &*line) == 1)
		return (1);
	return (0);
}
