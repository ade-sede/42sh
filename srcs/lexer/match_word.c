/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/26 15:59:59 by ade-sede          #+#    #+#             */
/*   Updated: 2017/06/26 16:00:51 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"
#include <stdio.h>

/*
**	Exhaustive list of reserved words
*/

static char	*g_reserved_word_list[] = {
	"if",
	"then",
	"else",
	"elif",
	"fi",
	"do",
	"done",
	"case",
	"esac",
	"while",
	"until",
	"for",
	"{",
	"}",
	"!",
	"in",
	NULL
};

/*
**	As the default state is word, we need to check if char we are reading is
**	starting a new token, thus closing the current one.
*/

int			match_word(t_lexer *lex)
{
	int	ret;

	(void)g_reserved_word_list;
	ret = 0;
	if (IS_WHITESPACE(lex->line[lex->index]))
		return (1);
	ret = update_state(lex);
	if (ret != WORD && ret != BACKSLASH)
		return (1);
	return (0);
}

/*
**	When trying to get the token id, if the token is a WORD, it might be an
**	IO_NUMBER.  Checking here.
*/

int			id_io_number(t_token *token, char delimiter, t_token_id *id)
{
	size_t	i;

	i = 0;
	if (delimiter != '<' && delimiter != '>')
		return (0);
	while (token->value[i] && ft_isdigit(token->value[i]))
		i++;
	if ((token->value[i]))
		return (0);
	*id = TK_IO_NUMBER;
	return (1);
}
