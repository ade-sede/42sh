/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_param.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:35 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 23:14:03 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lexer.h"
#include "parser.h"
#include "t_env.h"
#include "local.h"
#include "exec.h"
#include "glob.h"
#include "expand.h"

static int		get_param_cut(t_word *env, t_expand *exp)
{
	if (ft_isalpha(exp->words[exp->offset]) || exp->words[exp->offset] == '_')
	{
		while (ft_isalnum(exp->words[exp->offset]) ||
				exp->words[exp->offset] == '_')
		{
			w_addchar(env, exp->words[exp->offset]);
			++exp->offset;
		}
	}
	else if (ft_isdigit(exp->words[exp->offset]))
	{
		while (ft_isdigit(exp->words[exp->offset]))
		{
			w_addchar(env, exp->words[exp->offset]);
			++exp->offset;
		}
	}
	else if (CHAR_IN_SET(exp->words[exp->offset], "*@$?!"))
	{
		w_addchar(env, exp->words[exp->offset]);
		++exp->offset;
	}
	else
		return (0);
	return (1);
}

char			*get_param(t_expand *exp, int *seen_hash)
{
	t_word		env;
	int			brace;

	brace = exp->words[exp->offset] == '{';
	w_newword(&env);
	if (brace)
		++exp->offset;
	if (exp->words[exp->offset] == '#')
	{
		*seen_hash = 1;
		if (!brace)
			return (NULL);
		++exp->offset;
	}
	if (get_param_cut(&env, exp))
		if (!((brace && exp->words[exp->offset] == '}')))
			--exp->offset;
	return (env.str);
}

/*
**	poised after $
*/

static char		*parse_param_cut(int *seen_hash, t_expand *exp)
{
	char		*value;

	if (seen_hash)
	{
		value = ft_strdup(var_get_value(singleton_env(), "#"));
		seen_hash = 0;
	}
	else
	{
		value = NULL;
		exp->offset--;
		w_addchar(&exp->word, '$');
		w_addchar(&exp->g_word, '$');
	}
	return (value);
}

int				parse_param(t_expand *exp, int quoted)
{
	char		*value;
	int			seen_hash;
	char		*env_var;
	char		param_length[20];

	seen_hash = 0;
	env_var = get_param(exp, &seen_hash);
	if (env_var == NULL)
	{
		if (!(value = parse_param_cut(&seen_hash, exp)))
			return (0);
	}
	else
		value = var_get_value(singleton_env(), env_var);
	free(env_var);
	if (seen_hash)
	{
		w_addstr(&exp->word, ft_itoa_word((value ? ft_strlen(value) : 0),
				param_length));
		return (0);
	}
	handle_fieldsplitting(value, exp, quoted);
	return (0);
}
