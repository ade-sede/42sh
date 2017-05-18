/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   palloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 00:27:47 by ade-sede          #+#    #+#             */
/*   Updated: 2017/05/02 17:47:39 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "printf.h"

void	*palloc(size_t size, const char *func_name)
{
	void	*mem;

	mem = malloc(size);
	if (mem == NULL)
	{
		ft_dprintf(2, "Malloc returned NULL. Error occured in %s\n", func_name);
		exit(1);
	}
	return (mem);
}
