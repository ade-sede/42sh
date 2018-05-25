/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   return_failure.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:36 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 23:14:12 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "failure.h"
#include <stdio.h>
#include <stdarg.h>
#include "color.h"
#include "libft.h"

int		return_failure(const char *str, const char *error_msg)
{
	if (str)
		ft_putstr_fd(str, 2);
	if (error_msg)
		ft_putstr_fd(error_msg, 2);
	ft_putchar_fd('\n', 2);
	return (EXIT_FAILURE);
}

int		get_logfd(const char *file)
{
	int			fd;

	fd = open(file, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (fd < 0)
		return (-1);
	return (fd);
}

int		investigate_error(int log, const char *prefix,
		const char *custom_error, int return_value)
{
	size_t		i;
	t_word		buff;
	char		*error_name;

	w_newword(&buff);
	if (prefix != NULL && (i = -1))
	{
		while (prefix[++i])
			w_addchar(&buff, prefix[i]);
		w_addchar(&buff, ':');
		error_name = custom_error ? (char*)custom_error : get_errno();
		if (error_name)
			w_addstr(&buff, error_name);
	}
	else if (custom_error != NULL && prefix == NULL)
		w_addstr(&buff, custom_error);
	if (log && buff.str)
		ft_putendl_fd(buff.str, 2);
	w_free(&buff);
	return (return_value == -1 ? errno : return_value);
}
