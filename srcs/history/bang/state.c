/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 18:10:19 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 18:17:02 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "bang.h"

static void	change_state(int state[2], int s)
{
	state[_B_STATE] = s;
	state[_B_COUNT] = 0;
}

static int	update_state_part_1(int state[2], const char source)
{
	if (state[_B_STATE] == DEF)
	{
		if (source == '\'')
			change_state(state, QUOTES_BANG);
		else if (source == '"')
			change_state(state, DQUOTES_BANG);
		else if (source == '\\')
			change_state(state, BS_BANG);
		return (1);
	}
	if (state[_B_STATE] == QUOTES_BANG)
	{
		if (source == '\'')
			change_state(state, DEF);
		return (1);
	}
	return (0);
}

void		update_state(int state[2], const char source)
{
	int	ret;

	ret = update_state_part_1(state, source);
	if (!ret)
	{
		if (state[_B_STATE] == DQUOTES_BANG)
		{
			if (source == '"')
				change_state(state, DEF);
			if (source == '\\')
				change_state(state, DQUOTES_BANG_BS_BANG);
		}
		else if (state[_B_STATE] == BS_BANG)
		{
			if (state[_B_COUNT] == 2)
				change_state(state, DEF);
		}
		else if (state[_B_STATE] == DQUOTES_BANG_BS_BANG)
			change_state(state, DQUOTES_BANG);
	}
	state[_B_COUNT]++;
}
