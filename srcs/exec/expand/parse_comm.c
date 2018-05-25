/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_comm.c                                       :+:      :+:    :+:   */
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
#include <stdio.h>

void	cotement(int *quoted, int what)
{
	if (*quoted == 0)
		*quoted = what;
	else if (*quoted == what)
		*quoted = 0;
}

int		make_err(t_word *comm, t_expand *exp, int parent_quoted)
{
	int		error;

	error = exec_comm(comm->str, exp, parent_quoted);
	w_free(comm);
	return (error);
}

int		parse_comm(t_expand *exp, int parent_quoted)
{
	int		paren_depth;
	int		quoted;
	t_word	comm;

	paren_depth = 1;
	quoted = 0;
	w_newword(&comm);
	while (exp->words[exp->offset])
	{
		if (exp->words[exp->offset] == '\'')
			cotement(&quoted, 1);
		if (exp->words[exp->offset] == '"')
			cotement(&quoted, 2);
		if (exp->words[exp->offset] == ')')
			if (!quoted && --paren_depth == 0)
				if (comm.str)
					return (make_err(&comm, exp, parent_quoted));
		if (exp->words[exp->offset] == '(' && !quoted)
			++paren_depth;
		w_addchar(&comm, exp->words[exp->offset]);
		++exp->offset;
	}
	w_free(&comm);
	return (WRDE_SYNTAX);
}
