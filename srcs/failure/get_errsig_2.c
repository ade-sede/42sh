/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_errno_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:36 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 23:14:11 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*get_errsig_1(int sig)
{
	if (sig == 129)
		return ("hang up instruction: 1\n");
	if (sig == 130)
		return ("\n");
	if (sig == 131)
		return ("quit: 3\n");
	if (sig == 132)
		return ("illegal instruction: 4\n");
	if (sig == 133)
		return ("trace/breakpoint trap: 5\n");
	if (sig == 134)
		return ("abort: 6\n");
	if (sig == 135)
		return ("emulation trap: 7\n");
	if (sig == 136)
		return ("Arithmetic exception: 8\n");
	if (sig == 137)
		return ("kill instruction: 9\n");
	if (sig == 138)
		return ("bus error: 10\n");
	if (sig == 139)
		return ("segmentation fault: 11\n");
	if (sig == 140)
		return ("bad system call: 12\n");
	return (NULL);
}

char	*get_errsig_2(int sig)
{
	if (sig == 141)
		return ("broken pipe: 13\n");
	if (sig == 142)
		return ("alarm clock: 14\n");
	return ("terminated\n");
}
