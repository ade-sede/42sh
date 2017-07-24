/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/26 15:20:19 by ade-sede          #+#    #+#             */
/*   Updated: 2017/07/24 18:42:44 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "unistd.h"
#include "env.h"
#include "sys/wait.h"
#include "get_next_line.h"
#include "line_editing.h"

void	put_prompt(t_line *line)
{
	ft_putstr(line->prompt);
}

void	load_prompt(t_env *env, t_line *line, char *var, char *defaut)
{
	char	*prompt;

	prompt = NULL;
	prompt = env_getenv((const char**)env->environ, var, NULL);
	if (!prompt)
		prompt = defaut;
	line->prompt_len = ft_strlen(prompt);
	line->prompt = prompt;
}
