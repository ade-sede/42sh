/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_errno_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 22:40:48 by vcombey           #+#    #+#             */
/*   Updated: 2017/10/11 22:40:59 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include "libft.h"

char	*get_errno_1(void)
{
	if (errno == 1)
		return ("Operation not permitted");
	if (errno == 2)
		return ("No such file or directory");
	if (errno == 3)
		return ("No such process");
	if (errno == 4)
		return ("Interrupted system call");
	if (errno == 5)
		return ("I/O error");
	if (errno == 6)
		return ("No such device or address");
	if (errno == 7)
		return ("Argument list too long");
	if (errno == 8)
		return ("Exec format error");
	if (errno == 9)
		return ("Bad file number");
	if (errno == 10)
		return ("No child processes");
	if (errno == 11)
		return ("Try again");
	if (errno == 12)
		return ("Out of memory");
	return (NULL);
}

char	*get_errno_2(void)
{
	if (errno == 13)
		return ("Permission denied");
	if (errno == 14)
		return ("Bad address");
	if (errno == 15)
		return ("Block device required");
	if (errno == 16)
		return ("Device or resource busy");
	if (errno == 17)
		return ("File exists");
	if (errno == 18)
		return ("Cross-device link");
	if (errno == 19)
		return ("No such device");
	if (errno == 20)
		return ("Not a directory");
	if (errno == 21)
		return ("Is a directory");
	if (errno == 22)
		return ("Invalid argument");
	if (errno == 23)
		return ("File table overflow");
	if (errno == 24)
		return ("Too many open files");
	return (NULL);
}

char	*get_errno_3(void)
{
	if (errno == 25)
		return ("Not a typewriter");
	if (errno == 26)
		return ("Text file busy");
	if (errno == 27)
		return ("File too large");
	if (errno == 28)
		return ("No space left on device");
	if (errno == 29)
		return ("Illegal seek");
	if (errno == 30)
		return ("Read-only file system");
	if (errno == 31)
		return ("Too many links");
	if (errno == 32)
		return ("Broken pipe");
	if (errno == 33)
		return ("Math argument out of domain of func");
	if (errno == 34)
		return ("Math result not representable");
	if (errno == 35)
		return ("Resource deadlock would occur");
	if (errno == 36)
		return ("File name too long");
	return (NULL);
}

char	*get_errno_4(void)
{
	if (errno == 37)
		return ("No record locks available");
	if (errno == 38)
		return ("Function not implemented");
	if (errno == 39)
		return ("Directory not empty");
	if (errno == 40)
		return ("Too many symbolic links encountered");
	if (errno == 41)
		return ("Operation would block");
	if (errno == 42)
		return ("No message of desired type");
	if (errno == 43)
		return ("Identifier removed");
	if (errno == 44)
		return ("Channel number out of range");
	if (errno == 45)
		return ("Level 2 not synchronized");
	if (errno == 46)
		return ("Level 3 halted");
	if (errno == 47)
		return ("Level 3 reset");
	if (errno == 48)
		return ("Link number out of range");
	return (NULL);
}

char	*get_errno_5(void)
{
	if (errno == 49)
		return ("Protocol driver not attached");
	if (errno == 50)
		return ("No CSI structure available");
	if (errno == 51)
		return ("Level 2 halted");
	if (errno == 52)
		return ("Invalid exchange");
	if (errno == 53)
		return ("Invalid request descriptor");
	if (errno == 54)
		return ("Exchange full");
	if (errno == 55)
		return ("No anode");
	if (errno == 56)
		return ("Invalid request code");
	if (errno == 57)
		return ("Invalid slot");
	if (errno == 58)
		return ("Bad font file format");
	if (errno == 59)
		return ("Device not a stream");
	if (errno == 60)
		return ("No data available");
	return (NULL);
}
