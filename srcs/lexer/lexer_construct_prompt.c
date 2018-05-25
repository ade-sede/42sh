/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_construct_prompt.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:37 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 23:14:29 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"
#include <stdio.h>

struct s_state_to_prompt	g_state_to_promt[] =
{
	{CMD_SUBST, "cmdsubst"},
	{AR_EXP, "mathsubst"},
	{DQUOTES, "dquote"},
	{QUOTES, "quote"},
	{-1, NULL}
};

char	*lexer_construct_prompt(t_lexer *lex)
{
	int		state;
	int		i;

	i = 0;
	state = ((struct s_info*)lex->state->data)->state;
	while (g_state_to_promt[i].string)
	{
		if (state == g_state_to_promt[i].id)
			return (ft_strdup(g_state_to_promt[i].string));
		i++;
	}
	return (NULL);
}
