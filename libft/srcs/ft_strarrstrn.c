/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strarrstrn.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seddaoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/23 11:50:46 by seddaoud          #+#    #+#             */
/*   Updated: 2017/10/23 11:52:28 by seddaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strarrstrn(char **array, char *str, unsigned int n)
{
	int index;

	index = 0;
	while (array[index] && ft_strncmp(str, array[index], n))
		++index;
	return (array[index]) ? index : -1;
}
