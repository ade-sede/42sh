/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comple_exit_matched.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/08 23:19:54 by vcombey           #+#    #+#             */
/*   Updated: 2017/08/24 22:47:45 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "completion.h"
#include "line_editing.h"

void	comple_clear(t_comple c)
{
	//put_termcap("do");	
	//put_termcap("cr");	
	ft_putchar('\n');
	//goto_termcap("DL", 0, c.nb_lines);
	put_termcap("cd");	
	(void)c;
	//put_ntermcap("dl", c.nb_lines);	
}

void	comple_free(t_comple c)
{
	ft_arraydel(&c.matches);
}

char	*extract_color(char	*str)
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

int	comple_exit_matched(t_line *line, t_comple c, unsigned long long keycode)
{
	//printf("\nto_replace %s, match %s\n", c.to_replace, c.matches[c.pos]);
	//printf("\nto_replace %s, match %s\n", c.to_replace, c.matches[c.pos]);
	char	*matched;

	if ((keycode == KEY_ENTER && c.pos != -1)|| c.nb_matches == 1)
	{
		delete_word(c.to_replace);
		matched = extract_color(c.matches[c.pos]);
		edit_insert_str(line, c.to_replace, matched);
		free(matched);
	}
	//ft_strncpy(c.to_replace, c.matches[c.pos], ft_strlen(c.matches[c.pos]));
	comple_clear(c);
	put_termcap("up");
	comple_free(c);
	return (keycode);
}
