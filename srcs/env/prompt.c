/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/27 05:07:29 by vcombey           #+#    #+#             */
/*   Updated: 2017/08/27 05:07:58 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "env.h"
#include "get_next_line.h"
#include "line_editing.h"

void	put_prompt(t_line *line)
{
	ft_putstr(line->prompt);
}

void	load_prompt(t_env *env, t_line *line, char *var, char *defaut)
{
	char	*prompt;
	size_t	len;

	len = 0;
	prompt = NULL;
	if (ft_strequ(var, "PS1"))
		prompt = get_ps1(env, &len);
	else
		prompt = ft_strdup(env_getenv((const char**)env->environ, var, NULL));
	if (!prompt)
		prompt = defaut;
	if (ft_strequ(var, "PS1"))
		line->prompt_len = len;
	else
		line->prompt_len = ft_strlen(prompt);
	if (line->prompt)
		free(line->prompt);
	line->prompt = prompt;
}
