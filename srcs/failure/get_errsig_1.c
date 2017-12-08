/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_errsig_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:36 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 23:14:11 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "failure.h"

static char		*(*g_err_func[2])(int sig) =
{
	&get_errsig_1,
	&get_errsig_2
};

char	*get_errsig(int sig)
{
	char	*error;
	size_t	i;

	i = 0;
	while (i <= 1 && (error = (*g_err_func[i])(sig)) == NULL)
		i++;
	return (error);
}
