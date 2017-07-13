/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/13 14:51:54 by ade-sede          #+#    #+#             */
/*   Updated: 2017/07/13 14:56:39 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "env.h"
#include "exec.h"
#include <stdio.h>

static int	valid_param_expansion(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] != '(' && str[i + 1] != '{')
		{
			if (str[i + 1] == 0)
				return (-1);
			return (i);
		}
		i++;
	}
	return (-1);
}

static char	*expand_from_env(t_env *env, char *key, int offset)
{
	char	*param;
	char	*ret;

	param = env_getenv((const char **)env->environ, key + offset + 1, NULL);
	if (param)
		ret = ft_strdup(param);
	else
		ret = ft_strnew(0);
	return (ret);
}

void		parameter_expansion(t_env *env, t_token *token)
{
	char	**split;
	char	*param;
	int		offset;
	char	*result;
	size_t	i;

	i = 0;
	if ((offset = valid_param_expansion(token->value)) != -1)
	{
		result = ft_strnew(0);
		split = ft_strsplit_keep(token->value, WHITESPACES);
		while (split[i])
		{
			param = NULL;
			if ((offset = valid_param_expansion(split[i])) != -1)
				split[i] = ft_strchange(split[i], \
						expand_from_env(env, split[i], offset));
			result = ft_strchange(result, ft_strjoin(result, split[i]));
			free(split[i]);
			i++;
		}
		free(split);
		token->value = ft_strchange(token->value, result);
	}
}
