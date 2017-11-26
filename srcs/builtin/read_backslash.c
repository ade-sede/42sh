/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_backslash.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:34 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 23:13:47 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	backslash(char **line, char **word, char quote)
{
	(*line)++;
	if (quote && **line == 'n')
		ft_strpush(word, '\n');
	if (quote && **line == 't')
		ft_strpush(word, '\t');
	if (quote && **line == 'v')
		ft_strpush(word, '\v');
	if (quote && **line == 'a')
		ft_strpush(word, '\a');
	if (quote && **line == 'b')
		ft_strpush(word, '\b');
	if (quote && **line == 'f')
		ft_strpush(word, '\f');
	if (quote && **line == 'r')
		ft_strpush(word, '\r');
	else
		ft_strpush(word, **line);
	(*line)++;
}
