/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conf_term.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/08 23:19:54 by vcombey           #+#    #+#             */
/*   Updated: 2017/08/27 02:50:19 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_editing.h"
#include <stdio.h>

void	conf_term_canonical(t_line *line)
{
	if (tcsetattr(0, TCSADRAIN, &line->canonical_mode))
		fatal("tcsetattr error");
}

void	conf_term_normal(t_line *line)
{
	if (tcsetattr(0, TCSADRAIN, &line->normal_mode))
		fatal("tcsetattr error");
}

void	conf_term_in(void)
{
	char			*termtype;
	char			term_buffer[4096];
	struct termios	term;
	t_line			*line;

	line = singleton_line();
	if ((termtype = getenv("TERM")) == NULL)
		termtype = "xterm";
	if (tgetent(term_buffer, termtype) <= 0)
		fatal("cant access data base");
	if (tcgetattr(0, &term) == -1)
		fatal("getattr error");
	ft_memcpy(&line->normal_mode, &term, sizeof(struct termios));
	ft_memcpy(&line->canonical_mode, &line->normal_mode, sizeof(struct termios));
	term.c_lflag &= ~(ICANON);
	term.c_lflag &= ~(ECHO);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	line->canonical_mode.c_lflag &= ~(ICANON);
	line->canonical_mode.c_lflag &= ~(ECHO);
	line->canonical_mode.c_cc[VMIN] = 1;
	line->canonical_mode.c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSADRAIN, &term) < 0)
		fatal("tcsetattr error");
}
