/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_info.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:37 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 23:14:29 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"

void			free_info(void *ptr)
{
	struct s_info *info;

	info = ptr;
	if (info)
	{
		if (info->value.str)
			w_free(&info->value);
		free(info);
	}
}

struct s_info	*create_state_info(void)
{
	struct s_info *info;

	info = palloc(sizeof(*info));
	ft_memset(info, 0, sizeof(*info));
	w_newword(&info->value);
	return (info);
}

void			copy_state_info(struct s_info *old_info, struct s_info *new_i)
{
	ft_memcpy(new_i, old_info, sizeof(struct s_info));
}
