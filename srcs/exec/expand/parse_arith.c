/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arith.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:35 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 23:14:02 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

int			bad_arith(t_expand *exp, t_word cpy_word, t_word cpy_g_word)
{
	w_free(&exp->word);
	w_free(&exp->g_word);
	exp->word = cpy_word;
	exp->g_word = cpy_g_word;
	return (WRDE_SYNTAX);
}

int			get_arith(t_expand *exp, t_word cpy_word, t_word cpy_g_word)
{
	char			result[21];
	long int		numresult;
	long long int	convertme;
	int				error;

	numresult = 0;
	ft_bzero(result, 21);
	if (exp->words[1 + exp->offset] != ')')
		return (bad_arith(exp, cpy_word, cpy_g_word));
	++(exp->offset);
	if (exp->word.str && (error = eval_expr(exp->word.str, &numresult)) != 0)
		return (bad_arith(exp, cpy_word, cpy_g_word));
	bad_arith(exp, cpy_word, cpy_g_word);
	if (numresult < 0)
	{
		convertme = -numresult;
		w_addchar(&exp->word, '-');
	}
	else
		convertme = numresult;
	w_addstr(&exp->word, ft_itoa_word(convertme, result));
	w_addstr(&exp->g_word, ft_itoa_word(convertme, result));
	return (0);
}

int			parse_arith_special_chars(t_expand *exp, t_word cpy_word,
		t_word cpy_g_word)
{
	if (exp->words[exp->offset] == '$')
		parse_dollars(exp, 1);
	else if (exp->words[exp->offset] == '`')
	{
		(exp->offset)++;
		parse_backtick(exp, 1);
	}
	else if (exp->words[exp->offset] == '\\')
		parse_qtd_backslash(&exp->g_word, &exp->word, exp->words, &exp->offset);
	else if (ft_strchr(";{}", exp->words[exp->offset]))
		return (bad_arith(exp, cpy_word, cpy_g_word));
	else
		w_addchar(&exp->word, exp->words[exp->offset]);
	return (0);
}

void		cpy_word_g_word(t_expand *exp, t_word *cpy_word, t_word *cpy_g_word)
{
	*cpy_word = exp->word;
	*cpy_g_word = exp->g_word;
	w_newword(&exp->word);
	w_newword(&exp->g_word);
}

int			parse_arith(t_expand *exp)
{
	int				paren_depth;
	t_word			cpy_word;
	t_word			cpy_g_word;

	paren_depth = 1;
	cpy_word_g_word(exp, &cpy_word, &cpy_g_word);
	while (exp->words[exp->offset])
	{
		if (exp->words[exp->offset] == ')')
		{
			if (--paren_depth == 0)
				return (get_arith(exp, cpy_word, cpy_g_word));
			w_addchar(&exp->word, exp->words[exp->offset]);
		}
		else if (exp->words[exp->offset] == '(')
		{
			w_addchar(&exp->word, exp->words[exp->offset]);
			++paren_depth;
		}
		else if (parse_arith_special_chars(exp, cpy_word, cpy_g_word) != 0)
			return (WRDE_SYNTAX);
		++(exp->offset);
	}
	return (bad_arith(exp, cpy_word, cpy_g_word));
}
