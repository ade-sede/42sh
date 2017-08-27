/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_executable.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/27 06:58:33 by vcombey           #+#    #+#             */
/*   Updated: 2017/08/27 06:59:22 by vcombey          ###   ########.fr       */
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
