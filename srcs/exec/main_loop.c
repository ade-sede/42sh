/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/26 15:39:34 by ade-sede          #+#    #+#             */
/*   Updated: 2017/06/26 15:43:57 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>
#include "env.h"
#include "exec.h"
#include "builtin.h"
#include "line_editing.h"
#define LOCAL_BUFF_SIZE 4096

void	exec(t_env *env, const char **argv)
{
	if (!(exec_builtin(env, argv)))
		fork_exec_bin(env, argv);
}

void	main_loop(t_env *env)
{
	char		**argv;
	char		no_term_buff[LOCAL_BUFF_SIZE];

	while (42)
	{
		put_prompt(env);
		ft_bzero(no_term_buff, LOCAL_BUFF_SIZE);
		read(0, no_term_buff, LOCAL_BUFF_SIZE);
		*ft_strchr(no_term_buff, '\n') = '\0';
		argv = ft_strsplit_quotes(no_term_buff, " \t");
		exec_expand_args(*env, argv);
		exec(env, (const char **)argv);
		ft_arraydel(&argv);
	}
}
