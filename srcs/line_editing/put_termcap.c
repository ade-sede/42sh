/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_termcap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/15 22:41:02 by vcombey           #+#    #+#             */
/*   Updated: 2017/09/16 02:27:01 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_editing.h"

int		int_putchar(int c)
{
	ft_putchar_fd((char)c, 2);
	return (0);
}

void	put_termcap(char *capacity)
{
	tputs(tgetstr(capacity, NULL), 1, int_putchar);
}

void	put_ntermcap(char *capacity, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		put_termcap(capacity);
		i++;
	}
}

void	goto_termcap(char *capacity, int co, int li)
{
	tputs(tgoto(tgetstr(capacity, NULL), co, li), 1, int_putchar);
}
