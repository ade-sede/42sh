/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/26 15:20:19 by ade-sede          #+#    #+#             */
/*   Updated: 2017/06/26 15:36:53 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "unistd.h"
#include "env.h"
#include "get_next_line.h"

size_t	put_prompt(t_env *env)
{
	char	*prompt;

	prompt = NULL;
	prompt = env_getenv((const char**)env->environ, "PS1", NULL);
	if (!prompt)
		prompt = "$> ";
	ft_putstr(prompt);
	return (ft_strlen(prompt));
}
