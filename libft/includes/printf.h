/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:41 by ade-sede          #+#    #+#             */
/*   Updated: 2017/12/05 11:48:03 by seddaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTF_H
# define PRINTF_H
# include <string.h>
# include <stdarg.h>

/*
**	In file ft_printf.c
*/

void				ft_printf(const char *format, ...);

/*
**	In file ft_printf.c
*/

void				ft_dprintf(int fd, const char *format, ...);

/*
**	In file ft_printfd.c
*/

void				ft_putcfd(int fd, char c);
void				ft_putsfd(int fd, const char *str);
void				ft_putnfd(int fd, int nb);
void				ft_putunfd(int fd, unsigned int nb);

#endif
