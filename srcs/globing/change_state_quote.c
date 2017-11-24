/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_state_quote.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:36 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 23:14:12 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glob.h"

static void		quotement(int *quoted, int what)
{
	if (*quoted == 0)
		*quoted = what;
	else if (*quoted == what)
		*quoted = 0;
}

int				change_state_quote(char c, int quoted)
{
	if (c == '\'' && quoted != 3)
		quotement(&quoted, 1);
	else if (c == '"' && quoted != 3)
		quotement(&quoted, 2);
	else if (c == '\\')
		quotement(&quoted, 3);
	else
	{
		if (quoted == 3)
			quoted = 0;
	}
	return (quoted);
}
