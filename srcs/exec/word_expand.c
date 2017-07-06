/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_expand.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/05 17:37:49 by ade-sede          #+#    #+#             */
/*   Updated: 2017/07/06 16:00:38 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lexer.h"
#include "parser.h"
#include "env.h"
#include "exec.h"

int		word_expand(t_token *token)
{
	t_env	*env;
	int		ret;

	ret = 1;
	env = singleton_env();
	if (token->type == EXPAND)
	{
		if (*token->value == '$' && *token->value + 1 != '(' && *token->value + 1 != '{')
			exec_expand_args(*env, token);
		else
			ret = 0;
	}
	else if (token->type != QUOTED)
			exec_expand_args(*env, token);
	else
		ret = 0;
	if (token->type == DQUOTED || token->type == QUOTED)
	{
		*token->value = 0;
		if (token->size > 2)
		{
			token->value++;
			token->value[token->size - 2] = 0;
		}
		token->size -= 2;
	}
	return (ret);
}
