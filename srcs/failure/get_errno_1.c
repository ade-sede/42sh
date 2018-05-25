/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_errno_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:36 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 23:14:11 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "failure.h"

static char		*(*g_err_func[11])(void) =
{
	&get_errno_1,
	&get_errno_2,
	&get_errno_3,
	&get_errno_4,
	&get_errno_5,
	&get_errno_6,
	&get_errno_7,
	&get_errno_8,
	&get_errno_9,
	&get_errno_10,
	&get_errno_11
};

char	*get_errno_11(void)
{
	if (errno == 121)
		return ("Quota exceeded");
	if (errno == 122)
		return ("No medium found");
	if (errno == 123)
		return ("Wrong medium type");
	if (errno == 124)
		return ("Operation Canceled");
	if (errno == 125)
		return ("Required key not available");
	if (errno == 126)
		return ("Key has expired");
	if (errno == 127)
		return ("Key has been revoked");
	if (errno == 128)
		return ("Key was rejected by service");
	if (errno == 129)
		return ("Owner died");
	if (errno == 130)
		return ("State not recoverable");
	return (NULL);
}

char	*get_errno(void)
{
	char	*error;
	size_t	i;

	i = 0;
	while (i <= 11 && (error = (*g_err_func[i])()) == NULL)
		i++;
	return (error);
}
