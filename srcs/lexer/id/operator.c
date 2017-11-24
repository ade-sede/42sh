/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 20:28:46 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/23 20:28:57 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"

static char	*g_operator_list[] =
{
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

int		id_operator(const char *value)
{
	int		id;
	size_t	i;

	i = 0;
	id = -1;
	while (g_operator_list[i] && !ft_strequ(g_operator_list[i], value))
		++i;
	if (g_operator_list[i])
		id = i + OPERATOR_OFFSET;
	return (id);
}
