/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_fieldsplitting.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:35 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 23:14:01 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	nop_slit(char *value, t_expand *exp)
{
	size_t	i;

	i = 0;
	while (value[i])
	{
		if (value[i] == '\\')
			parse_qtd_backslash(&exp->g_word, &exp->word, value, &i);
		else if (ft_strchr("*[?", value[i]))
		{
			w_addchar(&exp->g_word, '\\');
			w_addchar(&exp->g_word, value[i]);
			w_addchar(&exp->word, value[i]);
		}
		else
		{
			w_addchar(&exp->g_word, value[i]);
			w_addchar(&exp->word, value[i]);
		}
		i++;
	}
}

static void	yep_slit(char *value, t_expand *exp)
{
	char	**split;
	size_t	i;

	split = ft_strsplit(value, exp->ifs);
	w_addstr(&exp->word, split[0]);
	w_addstr(&exp->g_word, split[0]);
	i = 1;
	while (split[i])
	{
		w_addword(exp, &exp->g_word, &exp->word);
		w_addstr(&exp->word, split[i]);
		w_addstr(&exp->g_word, split[i]);
		i++;
	}
	ft_arraydel(&split);
}

int			handle_fieldsplitting(char *value, t_expand *exp, int quoted)
{
	if (!value || (value && *value == 0))
		return (0);
	if (quoted || !exp || exp->flag & NO_FIELDSPLITING)
		nop_slit(value, exp);
	else
		yep_slit(value, exp);
	return (0);
}
