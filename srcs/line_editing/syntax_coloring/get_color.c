/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:37 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 23:14:36 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syntax_coloring.h"
#include "libft.h"

static struct s_color_match g_color_match[] =
{
	{DEFAULT, RESET},
	{WORD, RESET},
	{WHITESPACE, RESET},
	{COMMENT, GREY},
	{OPERATOR, PNK},
	{PARAM_EXP, BLU},
	{CMD_SUBST, RESET},
	{AR_EXP, RESET},
	{DQUOTES, YEL},
	{QUOTES, MAG},
	{BS, CYN},
	{NEWLINE, RESET},
	{-1, RESET},
};

const char	*get_color(int state)
{
	size_t	i;

	i = 0;
	while (g_color_match[i].state != -1 && g_color_match[i].state != state)
		++i;
	return (g_color_match[i].color);
}
