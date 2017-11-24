/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_get_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:34 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 23:13:47 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environ.h"
#include "read.h"
#include "local.h"
#include "line_editing.h"

static void	ft_strrem(char *str)
{
	while (*str)
	{
		*str = str[1];
		++str;
	}
}

static void	read_get_input_2(t_read options, unsigned long keycode, char **line)
{
	if (**line && (keycode == KEY_DELETE || keycode == KEY_BACKSPACE))
	{
		ft_strrem(line[ft_strlen(*line) - 1]);
		put_termcap("le");
		write(1, " ", 1);
		put_termcap("le");
	}
	if (ft_isprint((char)keycode) || keycode == KEY_ENTER ||
			keycode == KEY_TAB)
		ft_strpush(line, keycode);
	if ((options.flags & S))
		write(2, "*", 1);
	else if (ft_isprint((char)keycode) || keycode == KEY_ENTER ||
			keycode == KEY_TAB)
		write(2, &keycode, 1);
	else if (keycode == 27)
	{
		ft_strspush(line, "^[");
		write(2, "^[", 2);
	}
}

char		*read_get_input(t_read options)
{
	unsigned long	keycode;
	char			*line;
	int				index;

	index = 0;
	line = ft_strnew(0);
	while (42 || index < 10)
	{
		keycode = 0;
		read(0, &keycode, 1);
		if (g_abort_opening || keycode == KEY_CTRL_D ||
				(options.delim == (char)keycode))
			return (line);
		if (keycode == 27 || keycode > 127)
			read(STDIN_FILENO, (char *)&keycode + 1, 7);
		read_get_input_2(options, keycode, &line);
		if (options.nchars && options.nchars == ++index)
			return (line);
	}
}

char		*read_get_rcinput(t_read options)
{
	unsigned long	keycode;
	char			*line;
	int				index;

	index = 0;
	line = ft_strnew(0);
	while (!(keycode = 0) && read(STDIN_FILENO, &keycode, 1) == 1)
	{
		if (g_abort_opening || keycode == KEY_CTRL_D
			|| (options.delim == (char)keycode))
			return (line);
		if (keycode == 27 || keycode > 127)
			read(STDIN_FILENO, (char *)&keycode + 1, 7);
		if (*line && (keycode == KEY_DELETE || keycode == KEY_BACKSPACE))
			ft_strrem(&line[ft_strlen(line) - 1]);
		if (ft_isprint((char)keycode) || keycode == KEY_ENTER
			|| keycode == KEY_TAB)
			ft_strpush(&line, keycode);
		if (options.nchars && options.nchars == ++index)
			return (line);
	}
	return (line);
}
