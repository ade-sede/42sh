/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:35 by ade-sede          #+#    #+#             */
/*   Updated: 2017/12/09 17:29:07 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "t_env.h"
#include "exec.h"
#include "builtin.h"
#include "history.h"
#include "line_editing.h"
#include "lexer.h"
#include "parser.h"
#include "job_control.h"
#include "parser.h"
#include "local.h"

void	exec_main_loop(t_ast *ast)
{
	int			exit_status;
	char		nbr[20];

	singleton_jc()->background = 0;
	if (singleton_jc()->shell_is_interactive)
	{
		parse_heredoc(ast);
		conf_term_canonical();
	}
	exit_status = exec(ast);
	local_add_change_from_key_value(singleton_env(), "?",
			ft_itoa_word(exit_status, nbr));
	if (singleton_jc()->shell_is_interactive)
	{
		conf_term_non_canonical();
		//edit_cursor_pos();
	}
}
