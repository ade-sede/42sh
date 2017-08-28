/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comple_exit_matched.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/27 05:07:29 by vcombey           #+#    #+#             */
/*   Updated: 2017/08/28 18:55:22 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "completion.h"
#include "line_editing.h"

void	comple_clear(t_comple c)
{
	ft_putchar('\n');
	put_termcap("cd");
	(void)c;
}

void	comple_free(t_comple c)
{
	ft_arraydel(&c.matches);
}

char	*extract_color(char *str)
{
	char	*res;
	char	*res_dup;

	res = ft_strnew(ft_strlen_color(str));
	res_dup = res;
	while (*str)
	{
		if (*str == '\e')
		{
			while (*str && *str != 'm')
				str++;
			str++;
			if (!*str)
				return (res);
		}
		*res_dup = *str;
		res_dup++;
		str++;
	}
	return (res);
}

int		comple_exit_matched(t_line *line, t_comple c,
		unsigned long long keycode)
{
	char	*matched;

	if ((keycode == KEY_ENTER && c.pos != -1) || c.nb_matches == 1)
	{
		delete_word(c.to_replace);
		matched = extract_color(c.matches[c.pos]);
		edit_insert_str(line, c.to_replace, matched);
		free(matched);
	}
	edit_refresh(line);
	comple_free(c);
	return (keycode);
}
