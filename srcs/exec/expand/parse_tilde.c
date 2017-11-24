/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tilde.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:35 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 23:14:03 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parser.h"
#include "t_env.h"
#include "exec.h"
#include "glob.h"
#include "expand.h"

int		parse_tilde(t_expand *exp)
{
	char	*home;

	home = getenv("HOME");
	if (home != NULL)
	{
		w_addstr(&exp->word, home);
		w_addstr(&exp->g_word, home);
	}
	else
	{
		w_addchar(&exp->word, '~');
		w_addchar(&exp->g_word, '~');
	}
	return (1);
}
