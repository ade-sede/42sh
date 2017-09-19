/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_executable.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 14:05:51 by ade-sede          #+#    #+#             */
/*   Updated: 2017/09/18 14:06:40 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_is_executable(char *dir, char *file)
{
	char	*filename;

	filename = ft_strjoin3_free(dir ? dir : ".", "/", file, 0);
	if (access(filename, F_OK | X_OK) == 0)
	{
		free(filename);
		return (1);
	}
	free(filename);
	return (0);
}
