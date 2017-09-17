/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conf_term.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/15 22:41:02 by vcombey           #+#    #+#             */
/*   Updated: 2017/09/17 17:18:45 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_editing.h"
#include "env.h"

void	conf_term_canonical(void)
{
	if (tcsetattr(0, TCSADRAIN, &singleton_line()->canonical_mode) < 0)
		fatal("tcsetattr error");
}

void	conf_term_normal(void)
{
	if (tcsetattr(0, TCSADRAIN, &singleton_line()->normal_mode) < 0)
		fatal("tcsetattr error");
}

void	conf_term_in(void)
{
	char			*termtype;
	struct termios	term;
	t_line			*line;

	line = singleton_line();
	if ((termtype = env_getenv((const char**)singleton_env()->environ, \
					"TERM", NULL)) == NULL)
		termtype = "xterm";
	if (tgetent(NULL, termtype) <= 0)
		fatal("cant access data base");
	if (tcgetattr(0, &term) == -1)
		fatal("getattr error");
	ft_memcpy(&line->normal_mode, &term, sizeof(struct termios));
	ft_memcpy(&line->canonical_mode, &line->normal_mode,
			sizeof(struct termios));
	line->canonical_mode.c_lflag &= ~(ICANON);
	line->canonical_mode.c_lflag &= ~(ECHO);
	line->canonical_mode.c_cc[VMIN] = 1;
	line->canonical_mode.c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSANOW, &line->canonical_mode) < 0)
		fatal("tcsetattr error");
}
