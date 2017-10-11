/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion_ctor.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmickael <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/10 05:13:58 by bmickael          #+#    #+#             */
/*   Updated: 2017/09/10 05:14:00 by bmickael         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_completion.h"
#include "common/properties.h"
#include "common/messages.h"

int		init_completion(struct s_completion **ctx)
{
	if (!ENABLE_COMPLETION)
		return (0);
	if (!(*ctx = (struct s_completion *)ft_memalloc(sizeof(**ctx))))
		exit(EXIT_FAILURE);
	return (0);
}

int		close_completion(struct s_completion **ctx)
{
	if (!ENABLE_COMPLETION)
		return (0);
	if (*ctx == NULL)
	{
		return (error("close_completion",
		"ctx main context were never initialized", -1));
	}
	free_ternary_tree(&(*ctx)->tree);
	if ((*ctx)->path)
		free((*ctx)->path);
	free(*ctx);
	*ctx = NULL;
	return (0);
}
