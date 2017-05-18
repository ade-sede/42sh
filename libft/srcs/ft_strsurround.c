/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsurround.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/20 23:27:31 by ade-sede          #+#    #+#             */
/*   Updated: 2017/05/17 19:04:10 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsurround(const char *s1, const char *s2, const char *s3)
{
	char	*tmp;
	char	*str;

	if (!s2)
		return (NULL);
	if (!s1)
		return (ft_strjoin(s2, s3));
	if (!s3)
		return (ft_strjoin(s1, s2));
	tmp = ft_strjoin(s1, s2);
	str = ft_strjoin(tmp, s3);
	free(tmp);
	return (str);
}
