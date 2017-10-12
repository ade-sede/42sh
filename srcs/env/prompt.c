/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 22:40:48 by vcombey           #+#    #+#             */
/*   Updated: 2017/10/11 22:40:59 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "env.h"
#include "get_next_line.h"
#include "line_editing.h"

void	put_prompt(t_line *line)
{
	t_coor coord;

	ft_putstr_fd(line->prompt, 2);
	coord = get_prompt_visual_offset(line);
	if (coord.x == 0)
		ft_putchar_fd('\n', 2);
}

void	load_prompt(t_env *env, t_line *line, char *var, char *defaut)
{
	char	*prompt;
	size_t	len;

	len = 0;
	prompt = NULL;
	if (var && ft_strequ(var, "PS1"))
		prompt = get_ps1(env, &len);
	else if (var)
		prompt = env_getenv((const char**)env->environ, var, NULL);
	if (!prompt)
		prompt = defaut;
	if (var && ft_strequ(var, "PS1"))
		line->prompt_len = len;
	else
		line->prompt_len = ft_strlen(prompt);
	if (line->prompt)
		free(line->prompt);
	if (var && ft_strequ(var, "PS1"))
		line->prompt = prompt;
	else
		line->prompt = ft_strdup(prompt);
}
