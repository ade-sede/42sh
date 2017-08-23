/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comple_exit_matched.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/08 23:19:54 by vcombey           #+#    #+#             */
/*   Updated: 2017/07/25 17:36:25 by vcombey          ###   ########.fr       */
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

int	comple_exit_matched(t_line *line, t_comple c, unsigned long long keycode)
{
	(void)line;
	//printf("\nto_replace %s, match %s\n", c.to_replace, c.matches[c.pos]);
	delete_word(c.to_replace);
	//printf("\nto_replace %s, match %s\n", c.to_replace, c.matches[c.pos]);
	(void)keycode;
	if (keycode == KEY_ENTER || c.nb_matches == 1)
		edit_insert_str(line, c.to_replace, c.matches[c.pos]);
	//ft_strncpy(c.to_replace, c.matches[c.pos], ft_strlen(c.matches[c.pos]));
	comple_clear(c);
	put_termcap("up");
	comple_free(c);
	return (keycode);
}
