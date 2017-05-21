/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conf_term.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/08 22:16:28 by vcombey           #+#    #+#             */
/*   Updated: 2017/05/09 20:41:23 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "termios.h"
#include "term.h"

void	fatal(char *msg)
{
	ft_putendl_fd(msg, 2);
	exit(1);
}

void	conf_term_out(void)
{
	if (tcsetattr(0, TCSADRAIN, line()->old_term))
		fatal("tcsetattr error");
}

void	conf_term_in(void)
{
	char			*termtype;
	char			term_buffer[4096];
	struct termios	term;

	if ((termtype = getenv("TERM")) == NULL)
		termtype = "xterm";
	if (tgetent(term_buffer, termtype) <= 0)
		fatal("cant access data base");
	if (tcgetattr(0, &term) == -1)
		fatal("getattr error");
	line()->old_term = &term;
	term.c_lflag &= ~(ICANON);
	term.c_lflag &= ~(ECHO);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSADRAIN, &term) < 0)
		fatal("tcsetattr error");
}
