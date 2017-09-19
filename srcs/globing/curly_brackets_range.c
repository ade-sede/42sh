/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   curly_brackets_range.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 14:05:47 by ade-sede          #+#    #+#             */
/*   Updated: 2017/09/18 14:06:14 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glob.h"
#include "list.h"
#include "libft.h"

void	curly_brackets_range_alpha(t_list **res, char *expr, char *str, int end)
{
	char	b[2];
	char	b_end;

	b[0] = str[0];
	b[1] = '\0';
	b_end = str[ft_strlen(str) - 1];
	while (b[0] <= b_end)
	{
		curly_brackets(res, \
				ft_strjoin3_free(expr, (char *)b, expr + end + 1, 0));
		(*b)++;
	}
	free(str);
	free(expr);
}

void	curly_brackets_range_num(t_list **res, char *expr, char *str, int end)
{
	int	i;
	int	start_range;
	int	end_range;

	ft_atoi_safe(str, &start_range);
	i = 0;
	while (ft_is_start_of_digit(str[i]))
		i++;
	i += 2;
	ft_atoi_safe(str + i, &end_range);
	while (start_range != end_range)
	{
		curly_brackets(res, ft_strjoin3_free(expr, \
					ft_itoa(start_range), expr + end + 1, 2));
		if (start_range < end_range)
			start_range++;
		else
			start_range--;
	}
	curly_brackets(res, ft_strjoin3_free(expr, \
				ft_itoa(start_range), expr + end + 1, 2));
	free(str);
	free(expr);
}

void	curly_brackets_range(t_list **res, char *expr, char *str, int end)
{
	if (!ft_is_start_of_digit(str[0]) || !ft_isdigit(str[ft_strlen(str) - 1]))
		return (curly_brackets_range_alpha(res, expr, str, end));
	return (curly_brackets_range_num(res, expr, str, end));
}
