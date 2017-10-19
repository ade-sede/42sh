/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 22:40:47 by vcombey           #+#    #+#             */
/*   Updated: 2017/10/19 15:51:04 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"
#include "exec.h"
#include "line_editing.h"
#include "history.h"
#include "color.h"

/*
**	Determines if the char we are reading should or not be included in the
**	token.
**	If not, it closes the last token by returning the index of its last char,
**	and putting lex->index on the first char of the next potential token.
*/

#include <stdio.h>

static int	match_part_2(t_lexer *lex, size_t token_start, int *reopen)
{
	int		ret;

	(void)token_start;
	(void)reopen;
	ret = -1;
	if (IS_INPUT_END(lex->line[lex->index]) && !(IS_QUOTED(lex->state)))
		ret = lex->index - 1;
	else if (lex->state == NEWLINE)
	{
		if (lex->line[lex->index] != '\n')
			ret = (lex->index - 1);
	}
	/* else if (lex->state == EXPAND) */
	/* { */
	/* 	if (match_expand(lex, token_start)) */
	/* 		ret = (lex->index - 1); */
	/* } */
	return (ret);
}

static int	match_part_1(t_lexer *lex, size_t token_start, int *reopen)
{
	int		ret;

	if ((ret = match_part_2(lex, token_start, reopen)) != -1)
		return (ret);
	if (lex->state == WORD)
	{
		if (match_word(lex))
			ret = (lex->index - 1);
	}
	else if (IS_QUOTED(lex->state))
	{
		if (lex->line[lex->index] == '\0')
		{
			*reopen = lex->state;
			return (1);
		}
		if (charcmp(lex->line, lex->index, lex->state))
			ret = lex->index++;
	}
	return (ret);
}

int			token_match(t_lexer *lex, size_t token_start, int *reopen)
{
	int	ret;

	ret = -1;
	ret = match_part_1(lex, token_start, reopen);
	if (ret != -1)
		return (ret);
	else if (lex->state == OPERATOR)
	{
		if (IS_OPERATOR(lex->line[lex->index]) ||
				(charcmp(lex->line, lex->index, '-') &&
				charcmp(lex->line, lex->index - 1, '<')))
		{
			if (!match_operator(lex->line, token_start, lex->index))
				ret = lex->index - 1;
		}
		else
			ret = lex->index - 1;
	}
	if (lex->state == '\\')
		lex->state = WORD;
	return (ret);
}
