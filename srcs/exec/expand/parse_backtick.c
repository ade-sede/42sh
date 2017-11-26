/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_backtick.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:35 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 23:14:02 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parser.h"
#include "t_env.h"
#include "exec.h"
#include "glob.h"
#include "expand.h"

int		parse_backtick(t_expand *exp, int quoted)
{
	t_word		comm;

	w_newword(&comm);
	while (exp->words[exp->offset])
	{
		if (exp->words[exp->offset] == '`')
		{
			exec_comm(comm.str, exp, quoted);
			return (0);
		}
		else
			w_addchar(&comm, exp->words[exp->offset]);
		++(exp->offset);
	}
	w_free(&comm);
	return (WRDE_SYNTAX);
}
