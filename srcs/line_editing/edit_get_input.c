/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_get_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/27 04:54:27 by vcombey           #+#    #+#             */
/*   Updated: 2017/08/27 04:54:45 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_editing.h"
#include "completion.h"

static t_edit_func	g_edit_func[] =
{
	{KEY_LEFT, &edit_left},
	{KEY_RIGHT, &edit_right},
	{KEY_HOME, &edit_home},
	{KEY_END, &edit_end},
	{KEY_BACKSPACE, &edit_backspace},
	{KEY_TAB, comple_get_input},
	{0, NULL}
};

int		edit_loop(unsigned long long keycode, t_line *line)
{
	int	i;

	i = 0;
	while (g_edit_func[i].keycode)
	{
		if (g_edit_func[i].keycode == keycode)
		{
			g_edit_func[i].f(line);
			return (1);
		}
		i++;
	}
	if (ft_isprint((char)keycode))
		edit_add(keycode, line);
	return (1);
}

char		*edit_get_input(t_env *env)
{
	unsigned long long	keycode;
	t_line		*l;

	l = line();
	while (42)
	{
		keycode = 0;
		read(0, &keycode, 8);
		if (keycode == KEY_ENTER)
		{
			ft_putchar('\n');
			return (l->buff);
		}
		else if (edit_loop(keycode, l))
			edit_refresh(0, env);
	}
}

void		edit_line_init(void)
{
	ft_bzero(line()->buff, line()->len);
	line()->pos = 0;
	line()->len = 0;
}
