/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   curly_brackets_is_range.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/15 22:41:03 by vcombey           #+#    #+#             */
/*   Updated: 2017/09/15 22:41:13 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glob.h"
#include "list.h"
#include "libft.h"

int	ft_is_start_of_digit(char c)
{
	return (ft_isdigit(c) || c == '-');
}

int	curly_brackets_is_range(char *str)
{
	int		start_range;
	int		end_range;
	int		i;
	char	*point;
	int		is_number;

	if (!(point = ft_strchr(str, '.')))
		return (0);
	*point = '\0';
	is_number = ft_atoi_safe(str, &start_range);
	*point = '.';
	if (!is_number)
		return ((!(str[0] && str[1] && str[2] && str[3] && \
					str[1] == '.' && str[2] == '.' && !str[4])) ? 0 : 1);
	i = 0;
	while (str[i] && (ft_is_start_of_digit(str[i])))
		i++;
	if (str[i] != '.' || str[i + 1] != '.')
		return (0);
	i += 2;
	if (!(ft_atoi_safe(str + i, &end_range)) && (str[i + 1] || \
				((start_range >= 10 || start_range <= 10) && !str[i + 1])))
		return (0);
	return (1);
}
