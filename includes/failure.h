/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   failure.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 22:42:10 by vcombey           #+#    #+#             */
/*   Updated: 2017/10/11 22:42:13 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FAILURE_H
# define FAILURE_H
# define E_BUFSIZE 4096
# include <errno.h>
# include <stdio.h>
# include <time.h>
# include <fcntl.h>
# include <stdlib.h>

# ifdef LOG_FILE

#  define STRINGIZE(x) #x
#  define STRINGIZE_VALUE_OF(x) STRINGIZE(x)
#  define LOG_STREAM	get_logfd(STRINGIZE_VALUE_OF(LOG_FILE))
# else
#  define LOG_STREAM	get_logfd("log/def")
# endif

int				get_logfd(const char *file);

/*
**int				logwrite(const char *filename, const char *func_name,
**		const char *format, ...);
*/

char			*get_errno_1(void);
char			*get_errno_2(void);
char			*get_errno_3(void);
char			*get_errno_4(void);
char			*get_errno_5(void);
char			*get_errno_6(void);
char			*get_errno_7(void);
char			*get_errno_8(void);
char			*get_errno_9(void);
char			*get_errno_10(void);
char			*get_errno_11(void);

char			*get_errno(void);

int				investigate_error(int logfile, const char *prefix, \
		const char *custom_error, int return_value);

/*
**	In file return_failure.c
*/

int				return_failure(const char *str, const char *error_msg);
#endif
