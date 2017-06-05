/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match_operator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/05 12:51:27 by ade-sede          #+#    #+#             */
/*   Updated: 2017/06/05 16:09:49 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"
#include <stdio.h>

/*
**	Exhaustive list of all shell operators
*/

static const char	*g_operator_list[] = {
	"<",
	">",
	";",
	"|",
	"&",
	"&&",
	"||",
	";;",
	"<<",
	">>",
	"<&",
	">&",
	"<>",
	"<<-",
	">|",
	NULL
};

/*
**	This function has 2 purposes :
**
**				DELIMITING TOKENS
**	When delimiting tokens, if we are currently reading an operator, if the
**	char we are reading is an operator, it will either be appended to our
**	operator token or will delimit it depending on wether or not it can create
**	a valid operator if joined with the last one. This function will return 1
**	if the 'new operator' is valid, 0 otherwise.
**
**				ASSIGNING TOKEN ID
**	If used on a valid string, it will load the token_id variable (if pointer
**	exists) with the defined value for this exact token. See INCLUDES/LEXER.H
*/

int		match_operator(const char *value, size_t token_start, size_t token_end, t_token_id	*token_id)
{
	const char	*tmp_token;
	size_t		diff;
	int			i;

	i = 0;
	diff = token_end - token_start + 1;
	tmp_token = value + token_start;
	while (g_operator_list[i] != NULL && !ft_strnequ(g_operator_list[i], tmp_token, diff))
		i++;
	if (token_id && g_operator_list[i])
		*token_id = i + 5;
	if (g_operator_list[i] != NULL)
		return (1);
	return (0);
}
